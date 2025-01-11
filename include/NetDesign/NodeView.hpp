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

#ifndef NET_DESIGN_NODE_VIEW_HPP
#define NET_DESIGN_NODE_VIEW_HPP

#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QLineEdit>


namespace netd {

class NodeView : public QObject
{
    private:
        QVBoxLayout  *m_mainLayout;

        void setTablesLayout(void) noexcept;
        void setNodeCountLayout(void) noexcept;

    public:
        QWidget      *m_mainWidget;
        QTableWidget *m_nodeTable;
        QTableWidget *m_matrixTable;
        QPushButton  *m_submitButton;
        QPushButton  *m_saveButton;
        QLineEdit    *m_lineEdit;

        NodeView(QWidget *parent = nullptr) noexcept;
};

} // namespace netd

#endif // NET_DESIGN_NODE_VIEW_HPP
