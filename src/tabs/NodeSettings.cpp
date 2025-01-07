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
#include <NetDesign/Utils.hpp>
#include <QtWidgets/QLabel>


namespace netd {

NodeSettings::NodeSettings(tab::SettingsTab& settings) noexcept
{
    settings.list->addItem("Node & Load Matrix");

    mainWidget        = new QWidget();
    mainLayout        = new QVBoxLayout(mainWidget);
    nodeTable         = new QTableWidget(0, 4, mainWidget);
    matrixTable       = new QTableWidget(0, 0, mainWidget);
    auto tablesLayout = new QHBoxLayout();

    nodeTable->setHorizontalHeaderLabels({"ID", "Name", "X", "Y"});
    nodeTable->setMaximumSize(425, 500);
    matrixTable->setMaximumSize(900, 500);

    setNodeCount();

    auto saveButton = new QPushButton("Save");
    QObject::connect(saveButton, &QPushButton::clicked, [this]() {
        this->saveTables();
    });

    tablesLayout->addWidget(nodeTable);
    tablesLayout->addWidget(matrixTable);
    tablesLayout->setAlignment(Qt::AlignLeft);
    mainLayout->addLayout(tablesLayout);

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
            this->updateTables();
        }
        else
            QMessageBox::warning(nullptr, "Input Error", "Please enter a valid number");
    });

    layout->setAlignment(Qt::AlignLeft);
    mainLayout->addLayout(layout);
    mainLayout->setAlignment(Qt::AlignTop);
    mainWidget->setLayout(mainLayout);
}

void NodeSettings::updateTables(void) noexcept
{
    auto& nodes       = projectContext.nodes;
    int32_t nodeCount = static_cast<int32_t>(nodes.size());

    // preventing unintentional table update
    if (nodeTable->rowCount() == nodeCount)
        return;

    int32_t row = 0;

    // clear all entries, but save headers
    nodeTable->setRowCount(0);
    matrixTable->setRowCount(0);

    for (int32_t i = 0; i < nodeCount; ++i) {
        row = nodeTable->rowCount();
        nodeTable->insertRow(row);

        // creating table items and setting them in the table
        nodeTable->setItem(row, 0, new QTableWidgetItem("0"));
        nodeTable->setItem(row, 1, new QTableWidgetItem("-"));
        nodeTable->setItem(row, 2, new QTableWidgetItem("0"));
        nodeTable->setItem(row, 3, new QTableWidgetItem("0"));
    }

    if (nodeCount == 0)
        return;

    auto& matrix = projectContext.loadMatrix;
    matrix.clear();
    matrix.resize(nodeCount, nodeCount, false);

    matrixTable->setRowCount(nodeCount);
    matrixTable->setColumnCount(nodeCount);

    for (int32_t i = 0; i < nodeCount; i++) {
        for (int32_t j = 0; j < nodeCount; j++)
            matrixTable->setItem(i, j, new QTableWidgetItem("0"));
    }
}

void NodeSettings::saveTables(void) noexcept
{
    auto& nodes = projectContext.nodes;
    nodes.clear();

    Node node;

    for (int32_t i = 0; i < nodeTable->rowCount(); i++) {
        node.id   = getItem(nodeTable, i, 0).toUInt();
        node.name = getItem(nodeTable, i, 1).toStdString();
        node.x    = getItem(nodeTable, i, 2).toUInt();
        node.y    = getItem(nodeTable, i, 3).toUInt();

        nodes.push_back(node);
    }

    auto& matrix = projectContext.loadMatrix;

    for (size_t i = 0; i < matrix.size1(); i++) {
        for (size_t j = 0; j < matrix.size2(); j++)
            matrix(i, j) = getItem(matrixTable, i, j).toUInt();
    }
}

} // namespace netd