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

#include <NetDesign/RouterController.hpp>
#include <NetDesign/ProjectContext.hpp>
#include <QtWidgets/QMessageBox>
#include <NetDesign/Utils.hpp>


namespace netd {

RouterController::RouterController(RouterView *routerView) noexcept
{
    m_routerView = routerView;

    // handle packet size submit button click
    connect(m_routerView->m_submitButton, &QPushButton::clicked, [this]() {
        this->savePacketSize();
    });

    // TODO: add message box on save
    setRouterTable();
    setChannelTable();
}

void RouterController::savePacketSize(void) noexcept
{
    bool ok;
    auto packetSize = this->m_routerView->m_lineEdit->text().toUInt(&ok);

    if (ok) {
        ProjectContext::instance().m_packetSize = packetSize;
        QMessageBox::information(nullptr, "Success", "Successfully saved packet size");
    }
    else
        QMessageBox::warning(nullptr, "Input Error", "Please enter a valid number");
}

void RouterController::removeTableRow(QTableWidget *table) noexcept
{
    auto selectedItems = table->selectedItems();

    if (!selectedItems.isEmpty()) {
        auto row = selectedItems.first()->row();
        table->removeRow(row);
    }
}

void RouterController::setRouterTable(void) noexcept
{
    // handle router table add button click
    connect(m_routerView->m_addRouterButton, &QPushButton::clicked, [this]() {
        auto& table = this->m_routerView->m_routerTable;
        auto row    = table->rowCount();

        table->insertRow(row);
        table->setItem(row, 0, new QTableWidgetItem(""));
        table->setItem(row, 1, new QTableWidgetItem(""));
        table->setItem(row, 2, new QTableWidgetItem(""));
        table->setItem(row, 3, new QTableWidgetItem(""));
    });

    // handle router table remove button click
    connect(m_routerView->m_removeRouterButton, &QPushButton::clicked, [this]() {
        this->removeTableRow(this->m_routerView->m_routerTable);
    });

    // handle router table save button click
    connect(m_routerView->m_saveRouterButton, &QPushButton::clicked, [this]() {
        auto& routers    = ProjectContext::instance().m_routers;
        auto routerTable = this->m_routerView->m_routerTable;
        routers.clear();

        Router router;

        for (std::int32_t i = 0; i < routerTable->rowCount(); i++) {
            router.m_id       = getItem(routerTable, i, 0).toUInt();
            router.m_model    = getItem(routerTable, i, 1).toStdString();
            router.m_capacity = getItem(routerTable, i, 2).toUInt();
            router.m_price    = getItem(routerTable, i, 3).toUInt();

            routers.push_back(router);
        }

        QMessageBox::information(nullptr, "Success", "Successfully saved router table");
    });
}

void RouterController::setChannelTable(void) noexcept
{
    // handle channel table add button click
    connect(m_routerView->m_addChannelButton, &QPushButton::clicked, [this]() {
        auto& table = this->m_routerView->m_channelTable;
        auto row    = table->rowCount();

        table->insertRow(row);
        table->setItem(row, 0, new QTableWidgetItem(""));
        table->setItem(row, 1, new QTableWidgetItem(""));
        table->setItem(row, 2, new QTableWidgetItem(""));
    });

    // handle channel table remove button click
    connect(m_routerView->m_removeChannelButton, &QPushButton::clicked, [this]() {
        this->removeTableRow(this->m_routerView->m_channelTable);
    });

    // handle channel table save button click
    connect(m_routerView->m_saveChannelButton, &QPushButton::clicked, [this]() {
        auto& channels    = ProjectContext::instance().m_channels;
        auto channelTable = this->m_routerView->m_channelTable;
        channels.clear();

        Channel channel;

        for (std::int32_t i = 0; i < channelTable->rowCount(); i++) {
            channel.m_id       = getItem(channelTable, i, 0).toUInt();
            channel.m_capacity = getItem(channelTable, i, 1).toUInt();
            channel.m_price    = getItem(channelTable, i, 2).toUInt();

            channels.push_back(channel);
        }

        QMessageBox::information(nullptr, "Success", "Successfully saved channel table");
    });
}

void RouterController::updateContent(void) noexcept
{
    // update router table
    auto& routers     = ProjectContext::instance().m_routers;
    auto& routerTable = this->m_routerView->m_routerTable;

    routerTable->setRowCount(static_cast<std::int32_t>(routers.size()));

    std::int32_t i {0};

    for (const auto& router: routers) {
        routerTable->setItem(i, 0, new QTableWidgetItem(QString::number(router.m_id)));
        routerTable->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(router.m_model)));
        routerTable->setItem(i, 2, new QTableWidgetItem(QString::number(router.m_capacity)));
        routerTable->setItem(i, 3, new QTableWidgetItem(QString::number(router.m_price)));
        i++;
    }

    // update channel table
    auto& channels     = ProjectContext::instance().m_channels;
    auto& channelTable = this->m_routerView->m_channelTable;

    channelTable->setRowCount(static_cast<std::int32_t>(channels.size()));
    i = 0;

    for (const auto& channel : channels) {
        channelTable->setItem(i, 0, new QTableWidgetItem(QString::number(channel.m_id)));
        channelTable->setItem(i, 1, new QTableWidgetItem(QString::number(channel.m_capacity)));
        channelTable->setItem(i, 2, new QTableWidgetItem(QString::number(channel.m_price)));
        i++;
    }

    auto packetSize = QString::number(ProjectContext::instance().m_packetSize);
    m_routerView->m_lineEdit->setText(packetSize);
}

} // namespace netd