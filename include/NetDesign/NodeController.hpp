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

#ifndef NET_DESIGN_NODE_CONTROLLER_HPP
#define NET_DESIGN_NODE_CONTROLLER_HPP

#include <NetDesign/NodeView.hpp>


namespace netd {

class NodeController : public QObject
{
    NodeView *m_nodeView;

    public:
        NodeController(NodeView *nodeView) noexcept;

    private:
        void saveNodeCount(void) noexcept;
        void saveTables(void) noexcept;
        void updateTables(void) noexcept;
};

} // namespace netd

#endif // NET_DESIGN_NODE_CONTROLLER_HPP