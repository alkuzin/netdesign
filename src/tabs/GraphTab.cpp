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

#include <QtWidgets/QGraphicsEllipseItem>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QRadioButton>
#include <NetDesign/GraphTab.hpp>
#include <QtWidgets/QPushButton>
#include <NetDesign/Utils.hpp>
#include <filesystem>
#include <algorithm>
#include <print>


namespace netd {
namespace tab {

constexpr auto NODE_RADIUS {16};

GraphTab::GraphTab(void) noexcept
{
    m_mainLayout       = new QHBoxLayout(this);
    m_graphLayout      = new QVBoxLayout();
    m_buttonLayout     = new QVBoxLayout();
    m_weight           = nullptr;
    m_srcNodeComboBox  = new QComboBox();
    m_destNodeComboBox = new QComboBox();

    setGraphLayout();
    setButtonLayout();

    m_mainLayout->addLayout(m_graphLayout);
    m_mainLayout->addLayout(m_buttonLayout);
    setLayout(m_mainLayout);
}

void GraphTab::updateTabs(void) noexcept
{
    printProjectContext();
    m_graph.m_adjList.clear();
    m_graph.set();
    clearGraph();

    std::size_t src {0}, dest {0};

    // draw edges
    for (const auto& edge : boost::make_iterator_range(boost::edges(m_graph.m_adjList))) {
        src  = boost::source(edge, m_graph.m_adjList);
        dest = boost::target(edge, m_graph.m_adjList);

        const auto& channel = m_graph.m_adjList[edge];
        drawEdge(m_graph.m_adjList[src], m_graph.m_adjList[dest], channel);
    }

    // draw nodes
    for (const auto& vertex : boost::make_iterator_range(boost::vertices(m_graph.m_adjList)))
        drawNode(m_graph.m_adjList[vertex]);

    std::uint32_t srcPos {0}, destPos {0};

    srcPos  = static_cast<std::uint32_t>(m_srcNodeComboBox->currentIndex());
    destPos = static_cast<std::uint32_t>(m_destNodeComboBox->currentIndex());

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
            auto& channel = m_graph.m_adjList[boost::edge(predecessors[v], v, m_graph.m_adjList).first];
            totalPrice += channel.price;
            totalDelay += calculateDelay(channel.capacity, projectContext.loadMatrix(predecessors[v], v));
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

        // TODO: count average delay
        // TODO: count price of routers
        m_delayLabel->setText("Delay: " + QString::number(totalDelay));
        m_priceLabel->setText("Price: " + QString::number(totalPrice));
    }

    // fill comboboxes
    m_srcNodeComboBox->clear();
    m_destNodeComboBox->clear();

    for (const auto& node : projectContext.nodes) {
        auto str = QString::fromStdString(node.name);
        m_srcNodeComboBox->addItem(str);
        m_destNodeComboBox->addItem(str);
    }

}

void GraphTab::setGraphLayout(void) noexcept
{
    // setup graphics scene
    m_scene = new QGraphicsScene();
    m_scene->setSceneRect(0, 0, 1024, 768);

    auto view = new QGraphicsView(m_scene);

    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setRenderHint(QPainter::Antialiasing);

    // invert y-axis
    QTransform transform;
    transform.translate(0, m_scene->sceneRect().height());
    transform.scale(1, -1);
    view->setTransform(transform);

    m_mainLayout->addWidget(view);
}

void GraphTab::drawNode(const Node& node) noexcept
{
    auto currentPath    = std::filesystem::current_path();
    auto routerIconPath = QString(currentPath.c_str()) + "/res/router64x64.png";

    // loading the image
    QPixmap pixmap(routerIconPath);

    // rotate by 180 degrees
    QTransform transform;
    transform.rotate(180);
    auto rotatedPixmap = pixmap.transformed(transform, Qt::SmoothTransformation);

    auto rotatedPixmapItem = new QGraphicsPixmapItem(rotatedPixmap);
    rotatedPixmapItem->setPos(node.x - (NODE_RADIUS), node.y - (NODE_RADIUS));

    // setting the tooltip for the pixmap item
    auto tip = QString("Node ID: %1\nName: %2\nPosition: (%3, %4)")
        .arg(node.id).arg(QString::fromStdString(node.name)).arg(node.x).arg(node.y);
    rotatedPixmapItem->setToolTip(tip);

    // setting the tooltip style
    setStyleSheet(
        "QToolTip {"
        "color: black;"
        "background-color: white;"
        "border: 2px solid black;"
        "padding: 5px;"
        "}"
    );

    m_scene->addItem(rotatedPixmapItem);
}

void GraphTab::drawEdge(const Node& src, const Node& dest, const Channel& channel) noexcept
{
    QLineF line(src.x, src.y, dest.x, dest.y);

    auto lineItem = new QGraphicsLineItem(line);
    lineItem->setPen(QPen(Qt::gray));

    auto tip = QString("Channel ID: %1\nCapacity: %2\nPrice: %3")
        .arg(channel.id).arg(channel.capacity).arg(channel.price);

    lineItem->setToolTip(tip);
    m_scene->addItem(lineItem);
}

void GraphTab::clearGraph(void) noexcept
{
    m_scene->clear();
}

void GraphTab::setButtonLayout(void) noexcept
{
    m_delayLabel = new QLabel("Delay: ");
    m_priceLabel = new QLabel("Price: ");

    m_buttonLayout->addWidget(m_delayLabel);
    m_buttonLayout->addWidget(m_priceLabel);

    // TODO: add combobox to select src and dest nodes for dijkstra()

    auto priceRadioButton    = new QRadioButton("Price", this);
    auto capacityRadioButton = new QRadioButton("Capacity", this);

    connect(priceRadioButton, &QRadioButton::toggled, this, [this]() {
        this->m_weight = &Channel::price;
    });

    connect(capacityRadioButton, &QRadioButton::toggled, this, [this]() {
        this->m_weight = &Channel::capacity;
    });

    m_buttonLayout->addWidget(priceRadioButton);
    m_buttonLayout->addWidget(capacityRadioButton);

    m_buttonLayout->addWidget(m_srcNodeComboBox);
    m_buttonLayout->addWidget(m_destNodeComboBox);
    m_buttonLayout->setAlignment(Qt::AlignTop);

    // adding Update button
    auto updateButton = new QPushButton("Update");

    QObject::connect(updateButton, &QPushButton::clicked, [this]() {
        this->updateTabs();
    });

    m_buttonLayout->addWidget(updateButton);
}

} // namespace tab
} // namespace netd