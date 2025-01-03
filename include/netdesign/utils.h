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

#ifndef NET_DESIGN_UTILS_H
#define NET_DESIGN_UTILS_H

#include <netdesign/project_context.h>


#define IGNORE_UNUSED(x) ((void)(x))

/**
 * @brief Parse project data file.
 *
 * @param [in] filename - given project data filename.
 * @param [out] context - given project context structure to store data.
 */
void netd_parse_project_file(const char *filename, proj_context_t *context);

/**
 * @brief Print project context content.
 *
 * @param [out] context - given project context structure to print.
 */
void netd_print_project_context(const proj_context_t *context);

#endif // NET_DESIGN_UTILS_H