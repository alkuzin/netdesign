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

#ifndef NET_DESIGN_TABS_HPP
#define NET_DESIGN_TABS_HPP

#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QTabWidget>


namespace netd {
namespace tab {

struct SettingsTab {
    QHBoxLayout    *mainLayout;
    QStackedWidget *content;
    QListWidget    *list;
    QTabWidget     *tab;
};

QTabWidget *setSettingsTab(void) noexcept;
QTabWidget *setGraphTab(void) noexcept;

} // namespace tab
} // namespace netd

#endif // NET_DESIGN_TABS_HPP