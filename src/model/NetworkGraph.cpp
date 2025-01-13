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

#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <NetDesign/ProjectContext.hpp>
#include <NetDesign/NetworkGraph.hpp>
#include <NetDesign/Utils.hpp>
#include <print>


namespace netd {

void NetworkGraph::set(void) noexcept
{
    auto& projectContext = ProjectContext::instance();
    auto& edgeTable      = projectContext.m_edgeTable;
    auto& channels       = projectContext.m_channels;
    auto& nodes          = projectContext.m_nodes;

    // add nodes
    for (const auto& node : nodes)
        boost::add_vertex(node, m_adjList);

    // add channels
    for (std::size_t i = 0; i < edgeTable.size1(); i++) {
        auto srcNodeID  = edgeTable(i, 0);
        auto destNodeID = edgeTable(i, 1);
        auto channelID  = edgeTable(i, 2);

        boost::add_edge(srcNodeID, destNodeID, channels.at(channelID), m_adjList);
    }
}

std::tuple<Distances, VertexDescriptors> NetworkGraph::dijkstra(std::uint32_t src, ChannelMemberPtr weight) noexcept
{
    auto verticeCount = boost::num_vertices(m_adjList);
    auto initValue    = std::numeric_limits<std::int32_t>::max();

    Distances distances(verticeCount, initValue);

    // store predecessors for path reconstruction
    VertexDescriptors predecessors(verticeCount);
    distances[src] = 0;

    // create the edge weight map using the price from the Channel structure
    auto weightMap = get(weight, m_adjList);

    // run Dijkstra's algorithm
    auto property = boost::distance_map(&distances[0])
                    .predecessor_map(&predecessors[0])
                    .weight_map(weightMap);

    boost::dijkstra_shortest_paths(m_adjList, src, property);

    return std::tie(distances, predecessors);
}

} // namespace netd