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

#ifndef NET_DESIGN_NODE_SETTINGS_HPP
#define NET_DESIGN_NODE_SETTINGS_HPP

#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QListWidget>


namespace netd {

class NodeSettings {
    QWidget      *mainWidget;
    QVBoxLayout  *mainLayout;
    QTableWidget *nodeTable;
    QTableWidget *matrixTable;
    QLineEdit    *lineEdit;

    public:
        NodeSettings(void) noexcept = default;
        void set(QListWidget *list, QStackedWidget *content) noexcept;
        void update(void) noexcept;

    private:
        void setNodeCount(void) noexcept;
        void updateTables(void) noexcept;
        void saveTables(void) noexcept;
};

} // namespace netd

#endif // NET_DESIGN_NODE_SETTINGS_HPP