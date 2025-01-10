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

#ifndef NET_DESIGN_MENU_CONTROLLER_HPP
#define NET_DESIGN_MENU_CONTROLLER_HPP

#include <NetDesign/ProjectController.hpp>
#include <NetDesign/InfoController.hpp>
#include <NetDesign/MenuView.hpp>


namespace netd {

class MenuController : public QObject
{
    ProjectController m_projectController;
    InfoController    m_infoController;

    public:
        MenuController(void) noexcept = default;
        MenuController(MenuView *menuView, QWidget *parent = nullptr) noexcept;

        /** @brief "Project" New action handler.*/
        void onProjectNew(void) noexcept;

        /** @brief "Project" Open action handler.*/
        void onProjectOpen(void) noexcept;

        /** @brief "Project" Save action handler.*/
        void onProjectSave(void) noexcept;

        /** @brief "Project" Exit action handler.*/
        void onProjectExit(void) noexcept;

        /** @brief "Info" Documentation action handler.*/
        void onInfoDocs(void) noexcept;

        /** @brief "Info" About action handler.*/
        void onInfoAbout(void) noexcept;
};

} // namespace netd

#endif // NET_DESIGN_MENU_CONTROLLER_HPP