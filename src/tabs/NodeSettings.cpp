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
#include <NetDesign/NodeSettings.hpp>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QLabel>
#include <print>


namespace netd {

NodeSettings::NodeSettings(tab::SettingsTab& settings) noexcept
{
    settings.list->addItem("Node");

    mainWidget = new QWidget();
    mainLayout = new QVBoxLayout(mainWidget);
    table      = new QTableWidget(0, 4, mainWidget);

    table->setHorizontalHeaderLabels({"ID", "Name", "X", "Y"});
    table->setMaximumWidth(420);

    setNodeCount();

    auto saveButton = new QPushButton("Save");
    QObject::connect(saveButton, &QPushButton::clicked, [this]() {
        this->saveTable();
    });

    mainLayout->addWidget(table);
    mainLayout->addWidget(saveButton);
    settings.content->addWidget(mainWidget);
}

void NodeSettings::setNodeCount(void) noexcept
{
    auto layout = new QHBoxLayout();
    auto label  = new QLabel("Node count: ");

    label->setMaximumWidth(100);
    layout->addWidget(label);

    // handle input
    auto lineEdit = new QLineEdit();
    lineEdit->setMaximumWidth(100);
    layout->addWidget(lineEdit);

    auto submitButton = new QPushButton("Submit");
    submitButton->setMaximumWidth(100);
    layout->addWidget(submitButton);

    // connecting the button's clicked signal
    QObject::connect(submitButton, &QPushButton::clicked, [this, lineEdit]() {
        bool ok;
        uint32_t nodeCount = lineEdit->text().toUInt(&ok);

        if (ok) {
            projectContext.nodes.resize(nodeCount);
            this->updateTable();
        }
        else
            QMessageBox::warning(nullptr, "Input Error", "Please enter a valid number");
    });

    mainLayout->addLayout(layout);
    mainLayout->setAlignment(Qt::AlignTop);
    mainWidget->setLayout(mainLayout);
}

void NodeSettings::updateTable(void) noexcept
{
    auto& nodes       = projectContext.nodes;
    int32_t nodeCount = static_cast<int32_t>(nodes.size());

    // preventing unintentional table update
    if (table->rowCount() == nodeCount)
        return;

    int32_t row = 0;

    // clear all entries, but save headers
    table->setRowCount(0);

    for (int32_t i = 0; i < nodeCount; ++i) {
        row = table->rowCount();
        table->insertRow(row);

        // creating table items and setting them in the table
        this->table->setItem(row, 0, new QTableWidgetItem("0"));
        this->table->setItem(row, 1, new QTableWidgetItem("-"));
        this->table->setItem(row, 2, new QTableWidgetItem("0"));
        this->table->setItem(row, 3, new QTableWidgetItem("0"));
    }
}

static inline QString getItem(const QTableWidget *table, std::int32_t row, std::int32_t column) noexcept
{
    auto item = table->item(row, column);
    return item->text();
}

void NodeSettings::saveTable(void) noexcept
{
    auto& nodes = projectContext.nodes;
    nodes.clear();

    Node node;

    for (int32_t i = 0; i < table->rowCount(); i++) {
        node.id   = getItem(table, i, 0).toInt();
        node.name = getItem(table, i, 1).toStdString();
        node.x    = getItem(table, i, 2).toUInt();
        node.y    = getItem(table, i, 3).toUInt();

        nodes.push_back(node);
    }

    for (const auto& node : nodes) {
        std::println("[log] nodes: [ id: \'{}\', name: \'{}\', x: \'{}\', y: \'{}\' ]",
            node.id, node.name, node.x, node.y
        );
    }
}

} // namespace netd