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

#include <NetDesign/MenuController.hpp>


namespace netd {

MenuController::MenuController(MenuView *menuView, QWidget *parent) noexcept
{
    auto actions = menuView->getActions();

    parent->connect(actions[0], &QAction::triggered, this, &MenuController::onProjectNew);
    parent->connect(actions[1], &QAction::triggered, this, &MenuController::onProjectOpen);
    parent->connect(actions[2], &QAction::triggered, this, &MenuController::onProjectSave);
    parent->connect(actions[3], &QAction::triggered, this, &MenuController::onProjectExit);
    parent->connect(actions[4], &QAction::triggered, this, &MenuController::onInfoDocs);
    parent->connect(actions[5], &QAction::triggered, this, &MenuController::onInfoAbout);
}

void MenuController::onProjectNew(void) noexcept
{
    m_projectController.createProject();
}

void MenuController::onProjectOpen(void) noexcept
{
    m_projectController.openProject();
}

void MenuController::onProjectSave(void) noexcept
{
    m_projectController.saveProject();
}

void MenuController::onProjectExit(void) noexcept
{
    m_projectController.exitProject();
}

void MenuController::onInfoDocs(void) noexcept
{
    m_infoController.showDocumentation();
}

void MenuController::onInfoAbout(void) noexcept
{
    m_infoController.showAppInfo();
}

} // namespace netd