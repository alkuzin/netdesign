/**
 * NetDesign - simple network design tool.
 * Copyright (C) 2025 Alexander (@alkuzin)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <NetDesign/GraphController.hpp>
#include <NetDesign/ProjectContext.hpp>
#include <NetDesign/Utils.hpp>
#include <print>


namespace netd {

GraphController::GraphController(GraphView *graphView) noexcept
{
    m_graphView = graphView;

    connect(m_graphView->m_priceRadioButton, &QRadioButton::toggled, this, [this]() {
        this->m_weight = &Channel::m_price;
    });

    connect(m_graphView->m_capacityRadioButton, &QRadioButton::toggled, this, [this]() {
        this->m_weight = &Channel::m_capacity;
    });

    connect(m_graphView->m_updateButton, &QPushButton::clicked, [this]() {
        this->updateContent();
    });
}

void GraphController::updateContent(void) noexcept
{
    printProjectContext();
    m_graph.m_adjList.clear();
    m_graph.set();
    // m_edgeItems.clear();
    m_graphView->clearGraph();

    std::size_t src {0}, dest {0};

    // draw edges
    for (const auto& edge : boost::make_iterator_range(boost::edges(m_graph.m_adjList))) {
        src  = boost::source(edge, m_graph.m_adjList);
        dest = boost::target(edge, m_graph.m_adjList);

        const auto& channel = m_graph.m_adjList[edge];
        m_graphView->drawEdge(m_graph.m_adjList[src], m_graph.m_adjList[dest], channel);
    }

    // draw nodes
    for (const auto& vertex : boost::make_iterator_range(boost::vertices(m_graph.m_adjList)))
        m_graphView->drawNode(m_graph.m_adjList[vertex]);

    std::uint32_t srcPos {0}, destPos {0};

    srcPos  = static_cast<std::uint32_t>(m_graphView->m_srcNodeComboBox->currentIndex());
    destPos = static_cast<std::uint32_t>(m_graphView->m_destNodeComboBox->currentIndex());

    if (m_weight) {
        auto [distances, predecessors] = m_graph.dijkstra(srcPos, m_weight);

        // output the results
        std::println("Distances from node {}:", src);

        for (std::size_t i = 0; i < distances.size(); ++i)
            std::println("To node {}: {}", i, distances[i]);

        std::uint32_t totalPrice {0};
        double totalDelay {0.0};

        if (distances[destPos] == std::numeric_limits<std::int32_t>::max()) {
            std::println("Destination {} is not reachable from source {}", destPos, srcPos);
            // TODO: add warning message box
        }

        std::vector<std::size_t> path;

        for (VertexDescriptor v = destPos; v != srcPos; v = predecessors[v]) {
            path.push_back(v);

            // get the edge descriptor between predecessors[v] and v
            auto edgePair = boost::edge(predecessors[v], v, m_graph.m_adjList);
            if (edgePair.second) { // Check if the edge exists
                auto& channel = m_graph.m_adjList[edgePair.first];
                totalPrice += channel.m_price;
                // TODO:
                // totalDelay += calculateDelay(channel.capacity, projectContext.loadMatrix(predecessors[v], v));
            }
        }
        path.push_back(srcPos);

        // reversing the path to get it from src to dest
        std::reverse(path.begin(), path.end());

        // output the path
        std::println("Path from {} to {}: ", srcPos, destPos);
        for (const auto& node : path)
            std::print("{} ", node);
        std::putchar('\n');

        std::println("Total price: {}\nTotal delay: {}", totalPrice, totalDelay);
        // m_graphView->highlightPath(predecessors, Qt::red);

        // TODO: count average delay for this route
        // TODO: count average delay for whole network
        // TODO: count price of routers
        m_graphView->m_delayLabel->setText("Delay: " + QString::number(totalDelay));
        m_graphView->m_priceLabel->setText("Price: " + QString::number(totalPrice));
    }

    // fill comboboxes
    m_graphView->m_srcNodeComboBox->clear();
    m_graphView->m_destNodeComboBox->clear();

    for (const auto& node : ProjectContext::instance().m_nodes) {
        auto str = QString::fromStdString(node.m_name);
        m_graphView->m_srcNodeComboBox->addItem(str);
        m_graphView->m_destNodeComboBox->addItem(str);
    }
}

} // namespace netd