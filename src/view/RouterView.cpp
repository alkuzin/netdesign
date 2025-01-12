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

#include <NetDesign/RouterView.hpp>
#include <QtWidgets/QLabel>


namespace netd {

RouterView::RouterView(QWidget *parent) noexcept
{
    m_mainWidget  = new QWidget(parent);
    m_mainLayout  = new QVBoxLayout(m_mainWidget);
    m_tableLayout = new QHBoxLayout();

    setPacketSizeLayout();
    setRouterTableLayout();
    setChannelTableLayout();

    m_tableLayout->setAlignment(Qt::AlignLeft);
    m_mainLayout->setAlignment(Qt::AlignTop);
    m_mainLayout->addLayout(m_tableLayout);
    m_mainWidget->setLayout(m_mainLayout);
}

void RouterView::setPacketSizeLayout(void) noexcept
{
    auto layout = new QHBoxLayout();
    auto label  = new QLabel("Packet size: ");

    label->setMaximumWidth(100);
    layout->addWidget(label);

    m_lineEdit = new QLineEdit();
    m_lineEdit->setMaximumWidth(100);

    m_submitButton = new QPushButton("Submit");
    m_submitButton->setMaximumWidth(100);

    layout->setAlignment(Qt::AlignLeft);
    layout->addWidget(m_lineEdit);
    layout->addWidget(m_submitButton);

    m_mainLayout->addLayout(layout);
}

void RouterView::setRouterTableLayout(void) noexcept
{
    auto layout   = new QVBoxLayout();
    m_routerTable = new QTableWidget(0, 4, m_mainWidget);
    m_routerTable->setHorizontalHeaderLabels({"ID", "Model", "Capacity", "Price"});
    m_routerTable->setMaximumSize(425, 600);

    auto label = new QLabel("Router Table");
    label->setAlignment(Qt::AlignCenter);

    m_addRouterButton    = new QPushButton("Add");
    m_removeRouterButton = new QPushButton("Remove");
    m_saveRouterButton   = new QPushButton("Save");

    layout->setAlignment(Qt::AlignTop);
    layout->addWidget(label);
    layout->addWidget(m_routerTable);
    layout->addWidget(m_addRouterButton);
    layout->addWidget(m_removeRouterButton);
    layout->addWidget(m_saveRouterButton);

    m_tableLayout->addLayout(layout);
}

void RouterView::setChannelTableLayout(void) noexcept
{
    auto layout    = new QVBoxLayout();
    m_channelTable = new QTableWidget(0, 3, m_mainWidget);
    m_channelTable->setHorizontalHeaderLabels({"ID", "Capacity", "Price"});
    m_channelTable->setMaximumSize(425, 600);

    auto label = new QLabel("Channel Table");
    label->setAlignment(Qt::AlignCenter);

    m_addChannelButton    = new QPushButton("Add");
    m_removeChannelButton = new QPushButton("Remove");
    m_saveChannelButton   = new QPushButton("Save");

    layout->setAlignment(Qt::AlignTop);
    layout->addWidget(label);
    layout->addWidget(m_channelTable);
    layout->addWidget(m_addChannelButton);
    layout->addWidget(m_removeChannelButton);
    layout->addWidget(m_saveChannelButton);

    m_tableLayout->addLayout(layout);
}

} // namespace netd