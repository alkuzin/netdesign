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

#ifndef NET_DESIGN_TAB_CONTROLLER_HPP
#define NET_DESIGN_TAB_CONTROLLER_HPP

#include <NetDesign/SettingsView.hpp>
#include <NetDesign/GraphView.hpp>
#include <NetDesign/TabView.hpp>


namespace netd {

class TabController
{
    SettingsView *m_settingsView;
    GraphView    *m_graphView;
    TabView      *m_tabView;

    public:
        TabController(TabView *tabView, QWidget *parent = nullptr) noexcept;
        void addTab(QWidget *tab, const QString& title) noexcept;
};

} // namespace netd

#endif // NET_DESIGN_TAB_CONTROLLER_HPP