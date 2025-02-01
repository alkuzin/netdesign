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

#include <NetDesign/MenuView.hpp>


namespace netd {

MenuView::MenuView(QWidget *parent) noexcept
{
    m_menu = new QMenuBar(parent);
    createMenus();
}

void MenuView::createMenus(void) noexcept
{
    // "Project" menu
    auto projectMenu = m_menu->addMenu("Project");
    auto newAction   = projectMenu->addAction("New");
    auto openAction  = projectMenu->addAction("Open");
    auto saveAction  = projectMenu->addAction("Save");
    auto exitAction  = projectMenu->addAction("Exit");

    m_actions = {newAction, openAction, saveAction, exitAction};
}

QList<QAction*>& MenuView::getActions(void) noexcept
{
    return m_actions;
}

QMenuBar *MenuView::getMenuBar(void) noexcept
{
    return m_menu;
}

} // namespace netd