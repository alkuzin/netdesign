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
#include <QtWidgets/QInputDialog>
#include <QtWidgets/QMessageBox>
#include <NetDesign/Utils.hpp>
#include <print>


namespace netd {

static auto& context = ProjectContext::instance();

static std::uint32_t findNodeID(const std::string_view& name) noexcept
{
    auto it = std::find_if(context.m_nodes.begin(), context.m_nodes.end(),
        [&name](const Node& node) {
            return node.m_name.compare(name.data()) == 0;
        });

    if (it != context.m_nodes.end())
        return it.base()->m_id;
    else
        QMessageBox::warning(nullptr, "Error", "Could not find node");

    return 1;
}

static std::uint32_t findChannelID(const std::uint32_t capacity) noexcept
{
    auto it = std::find_if(context.m_channels.begin(), context.m_channels.end(),
        [&capacity](const Channel& channel) {
            return channel.m_capacity == capacity;
        });

    if (it != context.m_channels.end())
        return it.base()->m_id;
    else
        QMessageBox::warning(nullptr, "Error", "Could not find channel");

    return 1;
}

std::uint32_t GraphController::calculateDelay(double capacity, double load) noexcept
{
    if ((load / capacity) >= 1.0)
        return std::numeric_limits<std::uint32_t>::max();

    // M/D/1
    double leftPart  = 1 / (2 * capacity);
    double rightPart = load / (capacity * (capacity - load));

    return static_cast<std::uint32_t>((leftPart + rightPart) * 1000);
}

GraphController::GraphController(GraphView *graphView) noexcept
{
    m_graphView = graphView;
    m_weight    = &Channel::m_price;

    connect(m_graphView->m_priceRadioButton, &QRadioButton::toggled, this, [this]() {
        this->m_weight = &Channel::m_price;
    });

    connect(m_graphView->m_capacityRadioButton, &QRadioButton::toggled, this, [this]() {
        this->m_weight = &Channel::m_capacity;
    });

    connect(m_graphView->m_findRouteButton, &QPushButton::clicked, [this]() {
        this->calculateDelays();

    });

    connect(m_graphView->m_updateButton, &QPushButton::clicked, [this]() {
        this->updateContent();
    });

    // handle edge table buttons
    connect(m_graphView->m_addButton, &QPushButton::clicked, this, [this]() {
        this->insertEdgeTableRow(false);
    });

    connect(m_graphView->m_removeButton, &QPushButton::clicked, this, [this]() {
        auto table = this->m_graphView->m_edgeTable;
        bool ok;

        QString rowStr = QInputDialog::getText(nullptr, "Remove row", "Row:", QLineEdit::Normal, "", &ok);

        if (ok && !rowStr.isEmpty()) {
            std::int32_t row = rowStr.toInt() - 1;

            if (row >= 0 && row < table->rowCount())
                table->removeRow(row);
            else
                QMessageBox::warning(nullptr, "Error", "Incorrect row");
        }
    });

    connect(m_graphView->m_submitButton, &QPushButton::clicked, this, [this]() {
        auto table = this->m_graphView->m_edgeTable;

        context.m_edgeTable.resize(table->rowCount(), 3);

        for (std::int32_t row = 0; row < table->rowCount(); ++row) {
            auto srcComboBox     = qobject_cast<QComboBox*>(table->cellWidget(row, 0));
            auto destComboBox    = qobject_cast<QComboBox*>(table->cellWidget(row, 1));
            auto channelComboBox = qobject_cast<QComboBox*>(table->cellWidget(row, 2));

            if (srcComboBox && destComboBox && channelComboBox) {
                auto srcValue     = srcComboBox->currentText().toStdString();
                auto destValue    = destComboBox->currentText().toStdString();
                auto channelValue = channelComboBox->currentText().toUInt();

                context.m_edgeTable(row, 0) = findNodeID(srcValue) - 1;
                context.m_edgeTable(row, 1) = findNodeID(destValue) - 1;
                context.m_edgeTable(row, 2) = findChannelID(channelValue) - 1;
            }
        }

        QMessageBox::information(nullptr, "Success", "Successfully updated edges & vertices");
    });
}

void GraphController::insertEdgeTableRow(bool flag) noexcept
{
    const auto& context = ProjectContext::instance();
    auto& table         = m_graphView->m_edgeTable;
    auto row            = table->rowCount();
    table->insertRow(row);

    auto srcComboBox  = new QComboBox();
    auto destComboBox = new QComboBox();

    // add source & destination nodes
    for (const auto& node : context.m_nodes) {
        srcComboBox->addItem(QString::fromStdString(node.m_name));
        destComboBox->addItem(QString::fromStdString(node.m_name));
    }

    table->setCellWidget(row, 0, srcComboBox);
    table->setCellWidget(row, 1, destComboBox);

    // add channels
    auto channelComboBox = new QComboBox();

    for (const auto& channel : context.m_channels)
        channelComboBox->addItem(QString::number(channel.m_capacity));

    table->setCellWidget(row, 2, channelComboBox);

    if (flag) {
        srcComboBox->setCurrentIndex(context.m_edgeTable(row, 0));
        destComboBox->setCurrentIndex(context.m_edgeTable(row, 1));
        channelComboBox->setCurrentIndex(context.m_edgeTable(row, 2));
    }
}

void GraphController::updateEdgeTable(void) noexcept
{
    const auto& context = ProjectContext::instance();
    auto& table = m_graphView->m_edgeTable;

    // Clear the edge table
    table->setRowCount(0);

    // Fill the edge table with combo boxes
    auto edgeRows = static_cast<std::int32_t>(context.m_edgeTable.size1());
    for (std::int32_t row = 0; row < edgeRows; row++)
        insertEdgeTableRow(true);

    auto& loadTable = m_graphView->m_loadTable;

    // Clear the load table
    loadTable->setRowCount(0);

    // Fill the load table with combo boxes
    auto nodeRows = static_cast<std::int32_t>(context.m_nodes.size());

    // Initialize loads vector with the size of nodes
    std::vector<std::uint32_t> loads(nodeRows, 0);

    // Calculate loads for each node
    for (std::size_t i = 0; i < static_cast<std::uint32_t>(nodeRows); i++) {
        std::uint32_t load = 0;
        for (std::size_t j = 0; j < context.m_loadMatrix.size2(); j++)
            load += context.m_loadMatrix(i, j);
        loads[i] = load;
    }

    // Populate the load table
    for (std::int32_t row = 0; row < nodeRows; row++) {
        int loadTableRow = loadTable->rowCount(); // Use a different variable for load table row
        loadTable->insertRow(loadTableRow);

        // Set the node name and load in the load table
        loadTable->setItem(loadTableRow, 0, new QTableWidgetItem(QString::fromStdString(context.m_nodes.at(row).m_name)));
        loadTable->setItem(loadTableRow, 1, new QTableWidgetItem(QString::number(loads.at(row))));
    }
}

void GraphController::updateContent(void) noexcept
{
    updateEdgeTable();
    m_graph.m_adjList.clear();
    m_graph.set();
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

    // fill comboboxes
    m_graphView->m_srcNodeComboBox->clear();
    m_graphView->m_destNodeComboBox->clear();

    for (const auto& node : ProjectContext::instance().m_nodes) {
        auto str = QString::fromStdString(node.m_name);
        m_graphView->m_srcNodeComboBox->addItem(str);
        m_graphView->m_destNodeComboBox->addItem(str);
    }
}

void GraphController::calculateDelays(void) noexcept
{
    auto [routeDelay, totalPrice] = calculateRouteDelay();

    if (routeDelay == std::numeric_limits<std::uint32_t>::max())
        m_graphView->m_routeDelayLabel->setText("Route Delay: Infinite Delay");
    else
        m_graphView->m_routeDelayLabel->setText("Route Delay: " + QString::number(routeDelay) + " ms");

    auto totalDelay = calculateTotalDelay();

    m_graphView->m_priceLabel->setText("Price: " + QString::number(totalPrice));
    m_graphView->m_totalDelayLabel->setText("Total Delay: " + QString::number(totalDelay) + " ms");

    std::println("Total price: {}", totalPrice);
    std::println("Route delay: {} ms", routeDelay);
    std::println("Total delay: {} ms", totalDelay);

}

std::tuple<std::uint32_t, std::uint32_t> GraphController::calculateRouteDelay(void) noexcept
{
    std::uint32_t srcPos {0}, destPos {0}, routeDelay {0}, totalPrice {0};

    // check that comboboxes are set correctly
    bool isSrcEmpty  = (m_graphView->m_srcNodeComboBox->count() == 0);
    bool isDestEmpty = (m_graphView->m_destNodeComboBox->count() == 0);

    if (!isSrcEmpty && !isDestEmpty) {
        srcPos  = static_cast<std::uint32_t>(m_graphView->m_srcNodeComboBox->currentIndex());
        destPos = static_cast<std::uint32_t>(m_graphView->m_destNodeComboBox->currentIndex());
    }

    if (srcPos == destPos) {
        QMessageBox::warning(nullptr, "Error", "Incorrect node positions", QMessageBox::Ok);
        return {0, 0};
    }

    if (m_weight) {
        auto [distances, predecessors] = m_graph.dijkstra(srcPos, m_weight);

        // output the results
        std::println("Distances from node {}:", srcPos);

        for (std::size_t i = 0; i < distances.size(); ++i)
            std::println("To node {}: {}", i, distances[i]);

        if (distances[destPos] == std::numeric_limits<std::int32_t>::max()) {
            m_graphView->m_routeDelayLabel->setText("Route Delay: 0 ms");
            m_graphView->m_totalDelayLabel->setText("Total Delay: 0 ms");

            QString msg = "Destination " + QString::number(destPos) +
                          " is not reachable from source " + QString::number(srcPos);
            QMessageBox::warning(nullptr, "Warning", msg, QMessageBox::Ok);

            return {0, 0};
        }

        std::vector<std::size_t> path;

        for (VertexDescriptor v = destPos; v != srcPos; v = predecessors[v]) {
            path.push_back(v);

            // get the edge descriptor between predecessors[v] and v
            auto edgePair = boost::edge(predecessors[v], v, m_graph.m_adjList);

            if (edgePair.second) {
                auto& channel = m_graph.m_adjList[edgePair.first];
                totalPrice += channel.m_price;
            }
        }

        path.push_back(srcPos);

        // reversing the path to get it from src to dest
        std::reverse(path.begin(), path.end());

        // output the path
        std::println("Path from {} to {}: ", srcPos, destPos);
        for (const auto& node : path)
            std::print("{} ->", node + 1);
        std::puts(" x");

        std::uint32_t load {0}, capacity {0};

        for (std::size_t j = 0; j < context.m_loadMatrix.size2(); j++)
            load += context.m_loadMatrix(destPos, j);

        std::size_t lastChannelNode1 {0}, lastChannelNode2 {0};

        lastChannelNode1 = path.back();
        lastChannelNode2 = path.at(path.size() - 2);

        const auto& edgeTable = context.m_edgeTable;

        for (std::size_t i = 0; i < edgeTable.size1(); i++) {
            const auto& node1 = edgeTable(i, 0);
            const auto& node2 = edgeTable(i, 1);

            bool isCondition1 = lastChannelNode1 == node1 && lastChannelNode2 == node2;
            bool isCondition2 = lastChannelNode2 == node1 && lastChannelNode1 == node2;

            if (isCondition1 || isCondition2) {
                capacity = context.m_channels.at(edgeTable(i, 2)).m_capacity;
                break;
            }
        }

        capacity /= context.m_packetSize;   // capacity (packets/sec)
        load     /= context.m_packetSize;   // load (packets/sec)

        std::println("Capacity: {} packets/sec", capacity);
        std::println("Load:     {} packets/sec", load);

        if (capacity == 0) {
            QMessageBox::warning(nullptr, "Error", "Incorrect capacity", QMessageBox::Ok);
            m_graphView->m_routeDelayLabel->setText("Route Delay: 0 ms");
            m_graphView->m_totalDelayLabel->setText("Total Delay: 0 ms");
            return {};
        }

        routeDelay = calculateDelay(static_cast<double>(capacity), static_cast<double>(load));
    }

    return std::tie(routeDelay, totalPrice);
}

std::uint32_t GraphController::calculateTotalDelay(void) noexcept
{
    // Initialize total delay and count of reachable routes
    std::uint32_t totalDelay {0}, routeCount {0};

    auto nodeCount = static_cast<std::uint32_t>(boost::num_vertices(m_graph.m_adjList));

    for (std::uint32_t src = 0; src < nodeCount; ++src) {
        auto [distances, predecessors] = m_graph.dijkstra(src, m_weight);

        for (std::size_t dest = 0; dest < nodeCount; ++dest) {
            if (src != dest && distances[dest] != std::numeric_limits<std::int32_t>::max()) {
                // reconstruct the path from src to dest
                std::vector<std::size_t> path;
                for (VertexDescriptor v = dest; v != src; v = predecessors[v])
                    path.push_back(v);
                path.push_back(src);
                std::reverse(path.begin(), path.end());

                // calculate load and capacity for the last edge in the path
                std::uint32_t load {0}, capacity {0};
                auto lastChannelNode1 = path.back();
                auto lastChannelNode2 = path.at(path.size() - 2);

                const auto& edgeTable = context.m_edgeTable;

                for (std::size_t i = 0; i < edgeTable.size1(); i++) {
                    const auto& node1 = edgeTable(i, 0);
                    const auto& node2 = edgeTable(i, 1);

                    if ((lastChannelNode1 == node1 && lastChannelNode2 == node2) ||
                        (lastChannelNode2 == node1 && lastChannelNode1 == node2)) {
                        capacity = context.m_channels.at(edgeTable(i, 2)).m_capacity;
                        break;
                    }
                }

                // calculate load for the destination node
                for (std::size_t j = 0; j < context.m_loadMatrix.size2(); j++)
                    load += context.m_loadMatrix(dest, j);

                // convert capacity and load to packets/sec
                capacity /= context.m_packetSize;
                load     /= context.m_packetSize;

                // calculate the route delay
                if (capacity > 0) {
                    totalDelay += calculateDelay(static_cast<double>(capacity), static_cast<double>(load));
                    ++routeCount;
                }
            }
        }
    }

    auto averageDelay = (routeCount > 0) ? (totalDelay / routeCount) : 0;
    std::println("Average Network Delay: {} ms", averageDelay);

    return static_cast<std::uint32_t>(averageDelay);
}

} // namespace netd