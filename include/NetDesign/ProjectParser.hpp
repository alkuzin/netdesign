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

#ifndef NET_DESIGN_PROJECT_PARSER_HPP
#define NET_DESIGN_PROJECT_PARSER_HPP

#include <fstream>
#include <sstream>
#include <string>


namespace netd {

class ProjectParser {
    std::istringstream m_iss;
    std::ifstream      m_file;
    std::string        m_line;

    private:
        std::uint32_t parseCount(void) noexcept;
        void parseNodes(void) noexcept;
        void parseLoadMatrix(void) noexcept;
        void parseRouters(void) noexcept;
        void parseChannels(void) noexcept;

    public:
        void parse(const std::string_view& filename) noexcept;
};

} // namespace netd

#endif // NET_DESIGN_PROJECT_PARSER_HPP