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
#include <QtWidgets/QApplication>
#include <NetDesign/Utils.hpp>
#include <NetDesign/Menu.hpp>


namespace netd {
namespace menu {

void onProjectNew(void) noexcept
{
    // TODO:
}

void onProjectOpen(void) noexcept
{
    // TODO:
}

void onProjectSave(void) noexcept
{
    if (projectContext.filename.empty())
        onProjectNew();

    convertToXML(projectContext.filename, projectContext);
}

void onProjectExit(void) noexcept
{
    // TODO: ask if user sure to exit and ask him to save project
    QApplication::quit();
}

} // namespace menu
} // namespace netd