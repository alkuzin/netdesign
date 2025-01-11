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

#include <NetDesign/NodeView.hpp>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLabel>


namespace netd {

NodeView::NodeView(QWidget *parent) noexcept
{
    m_mainWidget = new QWidget(parent);
    m_mainLayout = new QVBoxLayout(m_mainWidget);

    setNodeCountLayout();
    setTablesLayout();

    m_mainLayout->setAlignment(Qt::AlignTop);
    m_mainLayout->addWidget(m_saveButton);
    m_mainWidget->setLayout(m_mainLayout);
}

void NodeView::setTablesLayout(void) noexcept
{
    m_nodeTable       = new QTableWidget(0, 4, m_mainWidget);
    m_matrixTable     = new QTableWidget(0, 0, m_mainWidget);
    auto tablesLayout = new QHBoxLayout();

    m_nodeTable->setHorizontalHeaderLabels({"ID", "Name", "X", "Y"});
    m_nodeTable->setMaximumSize(425, 500);
    m_matrixTable->setMaximumSize(900, 500);

    m_saveButton = new QPushButton("Save");

    tablesLayout->setAlignment(Qt::AlignLeft);
    tablesLayout->addWidget(m_nodeTable);
    tablesLayout->addWidget(m_matrixTable);

    m_mainLayout->addLayout(tablesLayout);
}

void NodeView::setNodeCountLayout(void) noexcept
{
    auto nodeCountLayout = new QHBoxLayout();
    auto nodeCountLabel  = new QLabel("Node count: ");
    nodeCountLabel->setMaximumWidth(100);

    // handle input
    m_lineEdit = new QLineEdit();
    m_lineEdit->setMaximumWidth(100);

    m_submitButton = new QPushButton("Submit");
    m_submitButton->setMaximumWidth(100);

    nodeCountLayout->addWidget(nodeCountLabel);
    nodeCountLayout->addWidget(m_lineEdit);
    nodeCountLayout->addWidget(m_submitButton);
    nodeCountLayout->setAlignment(Qt::AlignLeft);
    m_mainLayout->addLayout(nodeCountLayout);
}

} // namespace netd