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
#include <print>


namespace netd {

void NetworkGraph::set(void) noexcept
{
    auto& channels = projectContext.channels;
    auto& nodes    = projectContext.nodes;

    // add nodes
    for (const auto& node : nodes)
        boost::add_vertex(node, m_adjList);

    // TODO: comboBox for selecting specific channels to use
    // add channels
    for (std::size_t i = 0; i < nodes.size(); i++)
        for (std::size_t j = i + 1; j < nodes.size(); j++)
            boost::add_edge(i, j, channels.at(0), m_adjList);
}

void NetworkGraph::dijkstra(std::uint32_t start) noexcept
{
    auto verticeCount = boost::num_vertices(m_adjList);
    auto initValue    = std::numeric_limits<std::int32_t>::max();

    std::vector<std::int32_t> distances(verticeCount, initValue);

    // storing predecessors for path reconstruction
    using VertexDescriptor = boost::graph_traits<Graph>::vertex_descriptor;
    std::vector<VertexDescriptor> predecessors(verticeCount);
    distances[start] = 0;

    // TODO: lineEdit or check box to select
    // what to use as weightMap: price or 1/capacity

    // creating the edge weight map using the price from the Channel structure
    auto weightMap = get(&Channel::price, m_adjList);

    // running Dijkstra's algorithm
    auto property = boost::distance_map(&distances[0])
                    .predecessor_map(&predecessors[0])
                    .weight_map(weightMap);

    boost::dijkstra_shortest_paths(m_adjList, start, property);

    // output the results
    std::println("Distances from node {}:", start);

    for (std::size_t i = 0; i < distances.size(); ++i)
        std::println("To node {}: {}", i, distances[i]);

    // output the paths
    std::puts("Paths:");
    for (std::size_t i = 0; i < distances.size(); ++i) {
        if (distances[i] < std::numeric_limits<int>::max()) {
            std::println("Path to {}: ", i);
            for (std::size_t v = i; v != start; v = predecessors[v])
                std::print("{} <- ", v);
            std::println("{}", start);
        }
    }
}

} // namespace netd