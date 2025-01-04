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

#ifndef NET_DESIGN_UTILS_HPP
#define NET_DESIGN_UTILS_HPP

#include <NetDesign/ProjectContext.hpp>
#include <QtXml/QDomDocument>
#include <string>


namespace netd {

template<typename... Args>
void IGNORE_UNUSED(Args&&...) { /* do nothing */ }

void convertToXML(const std::string_view& filename, const ProjectContext& context) noexcept;
void convertToContext(const std::string_view& filename, ProjectContext& context) noexcept;

// TODO: implement function that checks is value in specific range

} // namespace netd

#endif // NET_DESIGN_UTILS_HPP