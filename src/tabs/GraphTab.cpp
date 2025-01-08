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
#include <NetDesign/GraphTab.hpp>
#include <print>


namespace netd {
namespace tab {

constexpr auto NODE_RADIUS {16};

GraphTab::GraphTab(void) noexcept
{
    m_mainLayout   = new QHBoxLayout(this);
    m_graphLayout  = new QVBoxLayout(this);
    m_buttonLayout = new QVBoxLayout(this);

    setGraphLayout();
    setButtonLayout();

    m_mainLayout->addLayout(m_graphLayout);
    m_mainLayout->addLayout(m_buttonLayout);
    setLayout(m_mainLayout);
}

void GraphTab::updateTabs(void) noexcept
{
    m_graph.m_adjList.clear();
    m_graph.set();

    clearGraph();

    for (const auto& vertex : boost::make_iterator_range(boost::vertices(m_graph.m_adjList))) {
        std::println("Vertex ID: {}, Name: ", vertex, m_graph.m_adjList[vertex].name);
        drawNode(m_graph.m_adjList[vertex]);
    }

    m_graph.dijkstra(0);
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
    auto ellipse = new QGraphicsEllipseItem(
        node.x - NODE_RADIUS,
        node.y - NODE_RADIUS,
        NODE_RADIUS << 1,
        NODE_RADIUS << 1
    );

    ellipse->setBrush(Qt::blue);
    ellipse->setPen(QPen(Qt::black));
    m_scene->addItem(ellipse);
}

void GraphTab::clearGraph(void) noexcept
{
    m_scene->clear();
}

void GraphTab::setButtonLayout(void) noexcept
{
    // TODO:
}

} // namespace tab
} // namespace netd