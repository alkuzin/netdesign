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

#include <NetDesign/ProjectContext.hpp>
#include <NetDesign/RouterSettings.hpp>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QMessageBox>
#include <NetDesign/Channel.hpp>
#include <NetDesign/Router.hpp>
#include <QtWidgets/QLineEdit>
#include <NetDesign/Utils.hpp>
#include <QtWidgets/QLabel>
#include <print>


namespace netd {

void RouterSettings::set(QListWidget *list, QStackedWidget *content) noexcept
{
    list->addItem("Routers & Channels");
    mainWidget = new QWidget();
    mainLayout = new QVBoxLayout(mainWidget);

    setTablesLayout();
    content->addWidget(mainWidget);
}

QVBoxLayout *RouterSettings::setRouterTableLayout(void) noexcept
{
    auto routerTableLayout = new QVBoxLayout();
    routerTable  = new QTableWidget(0, 4, mainWidget);
    routerTable->setHorizontalHeaderLabels({"ID", "Model", "Capacity", "Price"});
    routerTable->setMaximumSize(425, 600);

    auto routerTableLabel = new QLabel("Router Table");
    routerTableLabel->setAlignment(Qt::AlignCenter);

    auto addRouterTableButton = new QPushButton("Add");
    QObject::connect(addRouterTableButton, &QPushButton::clicked, [this]() {
        this->insertRouter();
    });

    auto removeRouterTableButton = new QPushButton("Remove");
    QObject::connect(removeRouterTableButton, &QPushButton::clicked, [this]() {
        auto& table        = this->routerTable;
        auto selectedItems = table->selectedItems();

        if (!selectedItems.isEmpty()) {
            auto row = selectedItems.first()->row();
            table->removeRow(row);
        }
    });

    auto saveRouterTableButton = new QPushButton("Save");
    QObject::connect(saveRouterTableButton, &QPushButton::clicked, [this]() {
        this->saveRouterTable();
    });

    routerTableLayout->addWidget(routerTableLabel);
    routerTableLayout->addWidget(routerTable);
    routerTableLayout->addWidget(addRouterTableButton);
    routerTableLayout->addWidget(removeRouterTableButton);
    routerTableLayout->addWidget(saveRouterTableButton);
    routerTableLayout->setAlignment(Qt::AlignTop);

    return routerTableLayout;
}

QVBoxLayout *RouterSettings::setChannelTableLayout(void) noexcept
{
    auto channelTableLayout = new QVBoxLayout();
    channelTable = new QTableWidget(0, 3, mainWidget);
    channelTable->setHorizontalHeaderLabels({"ID", "Capacity", "Price"});
    channelTable->setMaximumSize(425, 600);

    auto channelTableLabel = new QLabel("Channel Table");
    channelTableLabel->setAlignment(Qt::AlignCenter);

    auto addChannelTableButton = new QPushButton("Add");
    QObject::connect(addChannelTableButton, &QPushButton::clicked, [this]() {
        this->insertChannel();
    });

    auto removeChannelTableButton = new QPushButton("Remove");
    QObject::connect(removeChannelTableButton, &QPushButton::clicked, [this]() {
        auto& table        = this->channelTable;
        auto selectedItems = table->selectedItems();

        if (!selectedItems.isEmpty()) {
            auto row = selectedItems.first()->row();
            table->removeRow(row);
        }
    });

    auto saveChannelTableButton = new QPushButton("Save");
    QObject::connect(saveChannelTableButton, &QPushButton::clicked, [this]() {
        this->saveChannelTable();
    });

    channelTableLayout->addWidget(channelTableLabel);
    channelTableLayout->addWidget(channelTable);
    channelTableLayout->addWidget(addChannelTableButton);
    channelTableLayout->addWidget(removeChannelTableButton);
    channelTableLayout->addWidget(saveChannelTableButton);
    channelTableLayout->setAlignment(Qt::AlignTop);

    return channelTableLayout;
}

void RouterSettings::setTablesLayout(void) noexcept
{
    tablesLayout = new QHBoxLayout(mainWidget);

    setPacketSize();

    tablesLayout->addLayout(setRouterTableLayout());
    tablesLayout->addLayout(setChannelTableLayout());
    tablesLayout->setAlignment(Qt::AlignTop);
    mainLayout->addLayout(tablesLayout);
}

void RouterSettings::setPacketSize(void) noexcept
{
    auto layout = new QHBoxLayout();
    auto label  = new QLabel("Packet size: ");

    label->setMaximumWidth(100);
    layout->addWidget(label);

    // handle input
    lineEdit = new QLineEdit();
    lineEdit->setMaximumWidth(100);
    layout->addWidget(lineEdit);

    auto submitButton = new QPushButton("Submit");
    submitButton->setMaximumWidth(100);
    layout->addWidget(submitButton);

    // connecting the button's clicked signal
    QObject::connect(submitButton, &QPushButton::clicked, [this]() {
        bool ok;
        uint32_t packetSize = this->lineEdit->text().toUInt(&ok);

        if (ok)
            projectContext.packetSize = packetSize;
        else
            QMessageBox::warning(nullptr, "Input Error", "Please enter a valid number");
    });

    layout->setAlignment(Qt::AlignLeft);

    mainLayout->addLayout(layout);
    mainLayout->setAlignment(Qt::AlignTop);
    mainWidget->setLayout(mainLayout);
}

void RouterSettings::saveRouterTable(void) noexcept
{
    auto& routers = projectContext.routers;
    routers.clear();

    Router router;

    for (int32_t i = 0; i < routerTable->rowCount(); i++) {
        router.id       = getItem(routerTable, i, 0).toUInt();
        router.model    = getItem(routerTable, i, 1).toStdString();
        router.capacity = getItem(routerTable, i, 2).toUInt();
        router.price    = getItem(routerTable, i, 3).toUInt();

        routers.push_back(router);
    }
}

void RouterSettings::saveChannelTable(void) noexcept
{
    auto& channels = projectContext.channels;
    channels.clear();

    Channel channel;

    for (int32_t i = 0; i < channelTable->rowCount(); i++) {
        channel.id       = getItem(channelTable, i, 0).toUInt();
        channel.capacity = getItem(channelTable, i, 1).toUInt();
        channel.price    = getItem(channelTable, i, 2).toUInt();

        channels.push_back(channel);
    }
}

void RouterSettings::update(void) noexcept
{
    auto& routers     = projectContext.routers;
    auto routerCount = static_cast<std::int32_t>(routers.size());

    routerTable->setRowCount(routerCount);

    Router *router = nullptr;

    for (std::int32_t i = 0; i < routerCount; i++) {
        router = &routers.at(i);
        routerTable->setItem(i, 0, new QTableWidgetItem(QString::number(router->id)));
        routerTable->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(router->model)));
        routerTable->setItem(i, 2, new QTableWidgetItem(QString::number(router->capacity)));
        routerTable->setItem(i, 3, new QTableWidgetItem(QString::number(router->price)));
    }

    auto& channels    = projectContext.channels;
    auto channelCount = static_cast<std::int32_t>(channels.size());

    channelTable->setRowCount(channelCount);

    Channel *channel = nullptr;

    for (std::int32_t i = 0; i < channelCount; i++) {
        channel = &channels.at(i);
        channelTable->setItem(i, 0, new QTableWidgetItem(QString::number(channel->id)));
        channelTable->setItem(i, 1, new QTableWidgetItem(QString::number(channel->capacity)));
        channelTable->setItem(i, 2, new QTableWidgetItem(QString::number(channel->price)));
    }

    lineEdit->setText(QString::number(projectContext.packetSize));
}

void RouterSettings::insertRouter(void) noexcept
{
    auto& table = this->routerTable;
    auto row    = table->rowCount();

    table->insertRow(row);
    table->setItem(row, 0, new QTableWidgetItem(""));
    table->setItem(row, 1, new QTableWidgetItem(""));
    table->setItem(row, 2, new QTableWidgetItem(""));
    table->setItem(row, 3, new QTableWidgetItem(""));
}

void RouterSettings::insertChannel(void) noexcept
{
    auto& table = this->channelTable;
    auto row    = table->rowCount();

    table->insertRow(row);
    table->setItem(row, 0, new QTableWidgetItem(""));
    table->setItem(row, 1, new QTableWidgetItem(""));
    table->setItem(row, 2, new QTableWidgetItem(""));
}

} // namespace netd