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

#include <QtWidgets/QGraphicsPixmapItem>
#include <QtWidgets/QGraphicsView>
#include <NetDesign/GraphView.hpp>
#include <QtWidgets/QPushButton>
#include <filesystem>


namespace netd {

constexpr auto NODE_RADIUS {16};


GraphView::GraphView(QWidget *parent) noexcept
{
    m_mainLayout = new QHBoxLayout(parent);
    m_tab        = new QWidget(parent);

    setGraphLayout();
    setButtonLayout();

    m_tab->setLayout(m_mainLayout);
}

void GraphView::setGraphLayout(void) noexcept
{
    m_graphLayout = new QVBoxLayout();

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

    m_graphLayout->addWidget(view);
    m_mainLayout->addLayout(m_graphLayout);
}

void GraphView::setEdgeTable(void) noexcept
{
    m_edgeTable = new QTableWidget(0, 3, m_tab);
    m_edgeTable->setHorizontalHeaderLabels({"Source Node", "Destination Node", "Channel"});
    m_edgeTable->setMaximumWidth(315);
}

void GraphView::setButtonLayout(void) noexcept
{
    m_buttonLayout     = new QVBoxLayout();
    m_srcNodeComboBox  = new QComboBox();
    m_destNodeComboBox = new QComboBox();
    m_delayLabel       = new QLabel("Delay: ");
    m_priceLabel       = new QLabel("Price: ");

    m_buttonLayout->addWidget(m_delayLabel);
    m_buttonLayout->addWidget(m_priceLabel);

    m_priceRadioButton    = new QRadioButton("Price", m_tab);
    m_capacityRadioButton = new QRadioButton("Capacity", m_tab);

    m_buttonLayout->addWidget(m_priceRadioButton);
    m_buttonLayout->addWidget(m_capacityRadioButton);
    m_buttonLayout->addWidget(m_srcNodeComboBox);
    m_buttonLayout->addWidget(m_destNodeComboBox);
    m_buttonLayout->setAlignment(Qt::AlignTop);

    m_updateButton = new QPushButton("Update");

    // connect nodes
    setEdgeTable();
    m_addButton    = new QPushButton("Add");
    m_removeButton = new QPushButton("Remove");
    m_submitButton = new QPushButton("Submit");

    m_buttonLayout->addWidget(m_updateButton);
    m_buttonLayout->addWidget(m_edgeTable);
    m_buttonLayout->addWidget(m_addButton);
    m_buttonLayout->addWidget(m_removeButton);
    m_buttonLayout->addWidget(m_submitButton);
    m_mainLayout->addLayout(m_buttonLayout);
}

void GraphView::drawNode(const Node& node) noexcept
{
    auto currentPath    = std::filesystem::current_path();
    auto routerIconPath = QString(currentPath.c_str()) + "/res/router64x64.png";

    // loade the image
    QPixmap pixmap(routerIconPath);

    // rotate by 180 degrees
    QTransform transform;
    transform.rotate(180);
    auto rotatedPixmap = pixmap.transformed(transform, Qt::SmoothTransformation);

    auto rotatedPixmapItem = new QGraphicsPixmapItem(rotatedPixmap);
    rotatedPixmapItem->setPos(node.m_x - (NODE_RADIUS), node.m_y - (NODE_RADIUS));

    // set the tooltip for the pixmap item
    auto tip = QString("Node ID: %1\nName: %2\nPosition: (%3, %4)")
        .arg(node.m_id).arg(QString::fromStdString(node.m_name)).arg(node.m_x).arg(node.m_y);
    rotatedPixmapItem->setToolTip(tip);

    // set the tooltip style
    m_tab->setStyleSheet(
        "QToolTip {"
        "color: black;"
        "background-color: white;"
        "border: 2px solid black;"
        "padding: 5px;"
        "}"
    );

    m_scene->addItem(rotatedPixmapItem);
}

void GraphView::drawEdge(const Node& src, const Node& dest, const Channel& channel) noexcept
{
    QLineF line(src.m_x, src.m_y, dest.m_x, dest.m_y);

    auto lineItem = new QGraphicsLineItem(line);
    lineItem->setPen(QPen(Qt::gray, 3));

    auto tip = QString("Channel ID: %1\nCapacity: %2\nPrice: %3")
        .arg(channel.m_id).arg(channel.m_capacity).arg(channel.m_price);

    lineItem->setToolTip(tip);
    m_scene->addItem(lineItem);
}

void GraphView::clearGraph(void) noexcept
{
    m_scene->clear();
}

} // namespace netd