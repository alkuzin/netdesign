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
    auto& loadMatrix     = projectContext.m_loadMatrix;
    auto& channels       = projectContext.m_channels;
    auto& nodes          = projectContext.m_nodes;

    // add nodes
    for (const auto& node : nodes)
        boost::add_vertex(node, m_adjList);

    // TODO: comboBox for selecting specific channels to use
    // add channels
    for (std::size_t i = 0; i < nodes.size(); i++) {
        for (std::size_t j = i + 1; j < nodes.size(); j++) {
            if (loadMatrix(i, j) > 0 && loadMatrix(j, i) > 0) {
                auto channel       = channels.at(i);
                channel.m_capacity = loadMatrix(i, j);
                boost::add_edge(i, j, channel, m_adjList);
            }
        }
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