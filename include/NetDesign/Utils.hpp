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
#include <QtWidgets/QTableWidget>
#include <QtCore/QString>
#include <string>


namespace netd {

template<typename... Args>
void IGNORE_UNUSED(Args&&...) { /* do nothing */ }

constexpr double calculateDelay(std::uint32_t capacity, std::uint32_t load) noexcept
{
    return std::pow((capacity - load), 0.5);
}

void saveProject(const std::string_view& filename) noexcept;

QString getItem(const QTableWidget *table, size_t row, size_t column) noexcept;

void isExistRename(QString& filename, const std::string_view& suffix) noexcept;

void printProjectContext(void) noexcept;

} // namespace netd

#endif // NET_DESIGN_UTILS_HPP