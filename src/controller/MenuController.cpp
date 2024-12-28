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

#include <NetDesign/MenuController.hpp>


namespace netd {

void MenuController::onProjectNew(void) noexcept
{
    m_projectController.onNew();
}

void MenuController::onProjectOpen(void) noexcept
{
    m_projectController.onOpen();
}

void MenuController::onProjectSave(void) noexcept
{
    m_projectController.onSave();
}

void MenuController::onProjectExit(void) noexcept
{
    m_projectController.onExit();
}

void MenuController::onEditLoadFile(void) noexcept
{
    m_editController.onLoadFile();
}

void MenuController::onInfoDocs(void) noexcept
{

}

void MenuController::onInfoAbout(void) noexcept
{

}

} // namespace netd