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

#ifndef NET_DESIGN_GRAPH_CONTROLLER_HPP
#define NET_DESIGN_GRAPH_CONTROLLER_HPP

#include <NetDesign/NetworkGraph.hpp>
#include <NetDesign/GraphView.hpp>


namespace netd {

class GraphController : public QObject
{
    private:
        GraphView        *m_graphView;
        ChannelMemberPtr m_weight;
        NetworkGraph     m_graph;

        void updateEdgeTable(void) noexcept;
        void insertEdgeTableRow(bool flag) noexcept;
        void calculateDelays(void) noexcept;
        std::tuple<std::uint32_t, std::uint32_t> calculateRouteDelay(void) noexcept;
        std::uint32_t calculateDelay(double capacity, double load) noexcept;
        std::uint32_t calculateTotalDelay(void) noexcept;


    public:
        GraphController(GraphView *graphView) noexcept;
        void updateContent(void) noexcept;
};

} // namespace netd

#endif // NET_DESIGN_GRAPH_CONTROLLER_HPP