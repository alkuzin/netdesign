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

#include <NetDesign/ProjectContext.hpp>
#include <NetDesign/ProjectParser.hpp>
#include <QtWidgets/QMessageBox>
#include <NetDesign/Utils.hpp>
#include <print>


namespace netd {

void ProjectParser::parse(const std::string_view& filename) noexcept
{
    file.open(filename.data(), std::ios::in);

    if (!file.is_open()) {
        QMessageBox::warning(nullptr, "Error", "Could not open project file.");
        return;
    }

    // clear project context
    projectContext.loadMatrix.clear();
    projectContext.channels.clear();
    projectContext.routers.clear();
    projectContext.nodes.clear();
    projectContext.packetSize = 0;
    projectContext.filename.clear();

    line.reserve(256);

    while (std::getline(file, line)) {
        if (line.compare("# Nodes") == 0)
            parseNodes();

        if (line.compare("# Load Matrix") == 0)
            parseLoadMatrix();

        if (line.compare("# Routers") == 0)
            parseRouters();

        if (line.compare("# Channels") == 0)
            parseChannels();

        if (line.compare("# Packet Size") == 0)
            projectContext.packetSize = parseCount();
    }

    file.close();
    printProjectContext();
}

std::uint32_t ProjectParser::parseCount(void) noexcept
{
    std::getline(file, line);
    iss.clear();
    iss.str(line);

    std::uint32_t count;
    std::string   str;

    std::getline(iss, str, ',');
    iss >> count;

    return count;
}

void ProjectParser::parseNodes(void) noexcept
{
    auto nodeCount = parseCount();
    if (nodeCount)
        projectContext.nodes.reserve(nodeCount);

    std::getline(file, line); // skip line "id,name,x,y"

    std::uint32_t i {0};
    char delim;
    Node node;

    while (std::getline(file, line) && i < nodeCount && line[0] != '#') {
        iss.clear();
        iss.str(line);

        iss >> node.id >> delim;
        std::getline(iss, node.name, ',');
        iss >> node.x >> delim;
        iss >> node.y >> delim;

        projectContext.nodes.push_back(node);
        i++;
    }
}

void ProjectParser::parseLoadMatrix(void) noexcept
{
    auto matrixCount = parseCount();
    if (matrixCount)
        projectContext.loadMatrix.resize(matrixCount, matrixCount);

    std::uint32_t value;
    char delim;

    for (std::uint32_t i = 0; i < matrixCount; i++) {
        std::getline(file, line);
        iss.clear();
        iss.str(line);

        for (std::uint32_t j = 0; j < matrixCount; j++) {
            iss >> value >> delim;
            projectContext.loadMatrix(i, j) = value;
        }
    }
}

void ProjectParser::parseRouters(void) noexcept
{
    auto routerCount = parseCount();
    if (routerCount)
        projectContext.routers.reserve(routerCount);

    std::getline(file, line); // skip line

    std::uint32_t i {0};
    char   delim;
    Router router;

    while (std::getline(file, line) && i < routerCount && line[0] != '#') {
        iss.clear();
        iss.str(line);

        iss >> router.id >> delim;
        std::getline(iss, router.model, ',');
        iss >> router.capacity >> delim;
        iss >> router.price    >> delim;

        projectContext.routers.push_back(router);
        i++;
    }
}

void ProjectParser::parseChannels(void) noexcept
{
    auto channelCount = parseCount();
    if (channelCount)
        projectContext.channels.reserve(channelCount);

    std::getline(file, line); // skip line

    std::uint32_t i {0};
    char    delim;
    Channel channel;

    while (std::getline(file, line) && i < channelCount && line[0] != '#') {
        iss.clear();
        iss.str(line);

        iss >> channel.id        >> delim;
        iss >> channel.capacity  >> delim;
        iss >> channel.price     >> delim;

        projectContext.channels.push_back(channel);
        i++;
    }
}

} // namespace netd