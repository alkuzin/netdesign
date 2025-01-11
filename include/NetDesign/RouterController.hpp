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

#ifndef NET_DESIGN_ROUTER_CONTROLLER_HPP
#define NET_DESIGN_ROUTER_CONTROLLER_HPP

#include <NetDesign/RouterView.hpp>


namespace netd {

class RouterController : public QObject
{
    RouterView *m_routerView;

    public:
        RouterController(RouterView *routerView) noexcept;
        void updateContent(void) noexcept;

    private:
        void savePacketSize(void) noexcept;
        void setRouterTable(void) noexcept;
        void setChannelTable(void) noexcept;
        void removeTableRow(QTableWidget *table) noexcept;
};

} // namespace netd

#endif // NET_DESIGN_ROUTER_CONTROLLER_HPP