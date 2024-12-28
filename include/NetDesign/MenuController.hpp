/**
 * NetDesign - simple network design tool.
 * Copyright (C) 2024-2025 Alexander (@alkuzin)
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

#ifndef NETD_MENU_CONTROLLER_HPP
#define NETD_MENU_CONTROLLER_HPP

#include <NetDesign/ProjectController.hpp>


namespace netd {

class MenuController
{
    ProjectController m_projectController;

    public:
        MenuController(void) noexcept = default;
        void onProjectNew(void) noexcept;
        void onProjectOpen(void) noexcept;
        void onProjectSave(void) noexcept;
        void onProjectExit(void) noexcept;
        void onEditLoadFile(void) noexcept;
        void onInfoDocs(void) noexcept;
        void onInfoAbout(void) noexcept;
};

} // namespace netd

#endif // NETD_MENU_CONTROLLER_HPP