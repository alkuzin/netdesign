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

#ifndef NET_DESIGN_NETWORK_GRAPH_HPP
#define NET_DESIGN_NETWORK_GRAPH_HPP

#include <boost/graph/adjacency_list.hpp>
#include <NetDesign/Channel.hpp>
#include <NetDesign/Node.hpp>


namespace netd {

using Graph = boost::adjacency_list<
    boost::vecS,
    boost::vecS,
    boost::undirectedS,
    Node,
    Channel
>;

class NetworkGraph {
    public:
        NetworkGraph(void) noexcept = default;
        void set(void) noexcept;
        void dijkstra(std::uint32_t start) noexcept;

        Graph m_adjList;
};

} // namespace netd

#endif // NET_DESIGN_NETWORK_GRAPH_HPP