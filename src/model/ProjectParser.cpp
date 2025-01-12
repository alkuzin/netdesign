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
#include <NetDesign/MainWindow.hpp>
#include <QtWidgets/QMessageBox>
#include <NetDesign/Utils.hpp>
#include <print>


namespace netd {

static auto& projectContext = ProjectContext::instance();

void ProjectParser::parse(const std::string_view& filename) noexcept
{
    m_file.open(filename.data(), std::ios::in);

    if (!m_file.is_open()) {
        QMessageBox::warning(nullptr, "Error", "Could not open project file.");
        return;
    }

    // clear project context
    projectContext.m_loadMatrix.clear();
    projectContext.m_channels.clear();
    projectContext.m_routers.clear();
    projectContext.m_nodes.clear();
    projectContext.m_packetSize = 0;
    projectContext.m_filename.clear();

    m_line.reserve(256);

    while (std::getline(m_file, m_line)) {
        if (m_line.compare("# Nodes") == 0)
            parseNodes();

        if (m_line.compare("# Load Matrix") == 0)
            parseLoadMatrix();

        if (m_line.compare("# Routers") == 0)
            parseRouters();

        if (m_line.compare("# Channels") == 0)
            parseChannels();

        if (m_line.compare("# Packet Size") == 0)
            projectContext.m_packetSize = parseCount();
    }

    m_file.close();

    printProjectContext();

    // TODO:
    // MainWindow::getInstance()->updateTabs();
}

std::uint32_t ProjectParser::parseCount(void) noexcept
{
    std::getline(m_file, m_line);
    m_iss.clear();
    m_iss.str(m_line);

    std::uint32_t count;
    std::string   str;

    std::getline(m_iss, str, ',');
    m_iss >> count;

    return count;
}

void ProjectParser::parseNodes(void) noexcept
{
    auto nodeCount = parseCount();
    if (nodeCount)
        projectContext.m_nodes.reserve(nodeCount);

    std::getline(m_file, m_line); // skip line "id,name,x,y"

    std::uint32_t i {0};
    char delim;
    Node node;

    while (std::getline(m_file, m_line) && i < nodeCount && m_line[0] != '#') {
        m_iss.clear();
        m_iss.str(m_line);

        m_iss >> node.m_id >> delim;
        std::getline(m_iss, node.m_name, ',');
        m_iss >> node.m_x >> delim;
        m_iss >> node.m_y >> delim;

        projectContext.m_nodes.push_back(node);
        i++;
    }
}

void ProjectParser::parseLoadMatrix(void) noexcept
{
    auto matrixCount = parseCount();
    if (matrixCount)
        projectContext.m_loadMatrix.resize(matrixCount, matrixCount);

    std::uint32_t value;
    char delim;

    for (std::uint32_t i = 0; i < matrixCount; i++) {
        std::getline(m_file, m_line);
        m_iss.clear();
        m_iss.str(m_line);

        for (std::uint32_t j = 0; j < matrixCount; j++) {
            m_iss >> value >> delim;
            projectContext.m_loadMatrix(i, j) = value;
        }
    }
}

void ProjectParser::parseRouters(void) noexcept
{
    auto routerCount = parseCount();
    if (routerCount)
        projectContext.m_routers.reserve(routerCount);

    std::getline(m_file, m_line); // skip line

    std::uint32_t i {0};
    char   delim;
    Router router;

    while (std::getline(m_file, m_line) && i < routerCount && m_line[0] != '#') {
        m_iss.clear();
        m_iss.str(m_line);

        m_iss >> router.m_id >> delim;
        std::getline(m_iss, router.m_model, ',');
        m_iss >> router.m_capacity >> delim;
        m_iss >> router.m_price    >> delim;

        projectContext.m_routers.push_back(router);
        i++;
    }
}

void ProjectParser::parseChannels(void) noexcept
{
    auto channelCount = parseCount();
    if (channelCount)
        projectContext.m_channels.reserve(channelCount);

    std::getline(m_file, m_line); // skip line

    std::uint32_t i {0};
    char    delim;
    Channel channel;

    while (std::getline(m_file, m_line) && i < channelCount && m_line[0] != '#') {
        m_iss.clear();
        m_iss.str(m_line);

        m_iss >> channel.m_id       >> delim;
        m_iss >> channel.m_capacity >> delim;
        m_iss >> channel.m_price    >> delim;

        projectContext.m_channels.push_back(channel);
        i++;
    }
}

} // namespace netd