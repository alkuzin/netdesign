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

#ifndef NET_DESIGN_PROJECT_CONTROLLER_HPP
#define NET_DESIGN_PROJECT_CONTROLLER_HPP

#include <NetDesign/ProjectParser.hpp>
#include <string>


namespace netd {

class ProjectController
{
    private:
        ProjectParser m_parser;

    public:
        ProjectController(void) noexcept = default;

        /** @brief New action handler.*/
        void createProject(void) noexcept;

        /** @brief Open action handler.*/
        void openProject(void) noexcept;

        /** @brief Save action handler.*/
        void saveProject(void) noexcept;

        /** @brief Exit action handler.*/
        void exitProject(void) noexcept;
};

} // namespace netd

#endif // NET_DESIGN_PROJECT_CONTROLLER_HPP