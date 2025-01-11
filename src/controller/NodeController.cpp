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
#include <NetDesign/NodeController.hpp>
#include <QtWidgets/QMessageBox>
#include <NetDesign/Utils.hpp>


namespace netd {

NodeController::NodeController(NodeView *nodeView) noexcept
{
    m_nodeView = nodeView;

    connect(m_nodeView->m_submitButton, &QPushButton::clicked, [this]() {
        this->saveNodeCount();
    });

    connect(m_nodeView->m_saveButton, &QPushButton::clicked, [this]() {
        this->saveTables();
    });
}

void NodeController::saveNodeCount(void) noexcept
{
    bool ok;
    auto nodeCount = m_nodeView->m_lineEdit->text().toUInt(&ok);

    if (ok) {
        ProjectContext::instance().m_nodes.resize(nodeCount);
        this->updateTables();
    }
    else
        QMessageBox::warning(nullptr, "Input Error", "Please enter a valid number");
}

void NodeController::saveTables(void) noexcept
{
    // save node table
    auto& nodes = ProjectContext::instance().m_nodes;
    nodes.clear();

    auto nodeTable = m_nodeView->m_nodeTable;
    Node node;

    for (std::int32_t i = 0; i < nodeTable->rowCount(); i++) {
        node.m_id   = getItem(nodeTable, i, 0).toUInt();
        node.m_name = getItem(nodeTable, i, 1).toStdString();
        node.m_x    = getItem(nodeTable, i, 2).toUInt();
        node.m_y    = getItem(nodeTable, i, 3).toUInt();

        nodes.push_back(node);
    }

    // save load matrix table
    auto& matrix = ProjectContext::instance().m_loadMatrix;
    matrix.clear();

    for (std::size_t i = 0; i < matrix.size1(); i++) {
        for (std::size_t j = 0; j < matrix.size2(); j++)
            matrix(i, j) = getItem(m_nodeView->m_matrixTable, i, j).toUInt();
    }
}

void NodeController::updateTables(void) noexcept
{
    auto& nodes      = ProjectContext::instance().m_nodes;
    auto nodeCount   = static_cast<std::int32_t>(nodes.size());
    auto nodeTable   = m_nodeView->m_nodeTable;
    auto matrixTable = m_nodeView->m_matrixTable;

    // preventing unintentional table update
    if (nodeTable->rowCount() == nodeCount)
        return;

    // clear all entries, but save headers
    nodeTable->setRowCount(0);

    // update node table
    std::int32_t row {0};

    for (std::int32_t i = 0; i < nodeCount; ++i) {
        row = nodeTable->rowCount();
        nodeTable->insertRow(row);

        // create table items and set them in the table
        nodeTable->setItem(row, 0, new QTableWidgetItem(""));
        nodeTable->setItem(row, 1, new QTableWidgetItem(""));
        nodeTable->setItem(row, 2, new QTableWidgetItem(""));
        nodeTable->setItem(row, 3, new QTableWidgetItem(""));
    }

    if (nodeCount == 0)
        return;

    // clear all entries, but save headers
    matrixTable->setRowCount(0);

    auto& matrix = ProjectContext::instance().m_loadMatrix;
    matrix.clear();
    matrix.resize(nodeCount, nodeCount, false);

    // update load matrix table
    matrixTable->setRowCount(nodeCount);
    matrixTable->setColumnCount(nodeCount);

    for (std::int32_t i = 0; i < nodeCount; i++) {
        for (std::int32_t j = 0; j < nodeCount; j++)
            matrixTable->setItem(i, j, new QTableWidgetItem("0"));
    }
}

} // namespace netd