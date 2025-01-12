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

#include <QtWidgets/QGraphicsView>
#include <NetDesign/GraphView.hpp>
#include <QtWidgets/QPushButton>


namespace netd {

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

    m_buttonLayout->addWidget(m_updateButton);
    m_mainLayout->addLayout(m_buttonLayout);
}

} // namespace netd