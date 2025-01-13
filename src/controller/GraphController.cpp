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

static std::uint32_t calculateDelay(double capacity, double load) noexcept
{
    if ((load / capacity) >= 1.0) {
        QMessageBox::warning(nullptr, "Error", "Infinite delay", QMessageBox::Ok);
        return 0;
    }

    // M/D/1
    double leftPart  = 1 / (2 * capacity);
    double rightPart = load / (capacity * (capacity - load));

    return static_cast<std::uint32_t>((leftPart + rightPart) * 100);
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
{   const auto& context = ProjectContext::instance();
    auto& table         = m_graphView->m_edgeTable;

    // clear table
    table->setRowCount(0);

    // fill the table with combo boxes
    auto rows = static_cast<std::int32_t>(context.m_edgeTable.size1());

    for (std::int32_t row = 0; row < rows; row++)
        insertEdgeTableRow(true);
}

void GraphController::updateContent(void) noexcept
{
    // printProjectContext();
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
    std::uint32_t srcPos {0}, destPos {0};

    // check that comboboxes are set correctly
    bool isSrcEmpty  = (m_graphView->m_srcNodeComboBox->count() == 0);
    bool isDestEmpty = (m_graphView->m_destNodeComboBox->count() == 0);

    if (!isSrcEmpty && !isDestEmpty) {
        srcPos  = static_cast<std::uint32_t>(m_graphView->m_srcNodeComboBox->currentIndex());
        destPos = static_cast<std::uint32_t>(m_graphView->m_destNodeComboBox->currentIndex());
    }

    if (srcPos == destPos) {
        QMessageBox::warning(nullptr, "Error", "Incorrect node positions", QMessageBox::Ok);
        return;
    }

    if (m_weight) {
        auto [distances, predecessors] = m_graph.dijkstra(srcPos, m_weight);

        // output the results
        std::println("Distances from node {}:", srcPos);

        for (std::size_t i = 0; i < distances.size(); ++i)
            std::println("To node {}: {}", i, distances[i]);

        std::uint32_t totalPrice {0}, routeDelay {0}, totalDelay {0};

        if (distances[destPos] == std::numeric_limits<std::int32_t>::max()) {
            QString msg = "Destination " + QString::number(destPos) +
                          " is not reachable from source " + QString::number(srcPos);
            QMessageBox::warning(nullptr, "Warning", msg, QMessageBox::Ok);
            return;
        }

        std::vector<std::size_t> path;

        for (VertexDescriptor v = destPos; v != srcPos; v = predecessors[v]) {
            path.push_back(v);

            // get the edge descriptor between predecessors[v] and v
            auto edgePair = boost::edge(predecessors[v], v, m_graph.m_adjList);
            if (edgePair.second) { // Check if the edge exists
                auto& channel = m_graph.m_adjList[edgePair.first];
                totalPrice += channel.m_price;
            }
        }

        path.push_back(srcPos);
        IGNORE_UNUSED(calculateDelay, routeDelay);

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

        std::println("Capacity: {}", capacity);
        std::println("Load:     {}", load);

        if (capacity == 0) {
            QMessageBox::warning(nullptr, "Error", "Incorrect capacity", QMessageBox::Ok);
            return;
        }

        routeDelay = calculateDelay(
            static_cast<double>(capacity),
            static_cast<double>(load)
        );

        std::println("Total price: {}", totalPrice);
        std::println("Total delay: {}", totalDelay);
        std::println("Route delay: {}", routeDelay);

        // TODO: count average delay for this route
        // TODO: count average delay for whole network
        // TODO: count price of routers
        m_graphView->m_delayLabel->setText("Delay: " + QString::number(totalDelay));
        m_graphView->m_priceLabel->setText("Price: " + QString::number(totalPrice));
    }
}

} // namespace netd