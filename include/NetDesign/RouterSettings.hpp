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

#ifndef NET_DESIGN_ROUTER_SETTINGS_HPP
#define NET_DESIGN_ROUTER_SETTINGS_HPP

#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <NetDesign/Tabs.hpp>


namespace netd {

class RouterSettings {
    QWidget      *mainWidget;
    QVBoxLayout  *mainLayout;
    QHBoxLayout  *tablesLayout;
    QTableWidget *routerTable;
    QTableWidget *channelTable;

    public:
        RouterSettings(tab::SettingsTab& settings) noexcept;

    private:
        void setTablesLayout(void) noexcept;
        QVBoxLayout *setRouterTableLayout(void) noexcept;
        QVBoxLayout *setChannelTableLayout(void) noexcept;
        void setPacketSize(void) noexcept;
        void saveRouterTable(void) noexcept;
        void saveChannelTable(void) noexcept;
};

} // namespace netd

#endif // NET_DESIGN_ROUTER_SETTINGS_HPP