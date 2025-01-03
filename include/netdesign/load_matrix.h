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

#ifndef NET_DESIGN_LOAD_MATRIX_H
#define NET_DESIGN_LOAD_MATRIX_H

#include <stdint.h>


// load matix (size x size)
struct load_matrix {
    int32_t **data;
    int32_t size;
};

typedef struct load_matrix load_matrix_t;

/**
 * @brief Create a load matrix object.
 *
 * @param [in] size - given size of matrix.
 * @return new object pointer.
 */
load_matrix_t *create_load_matrix(int32_t size);

/**
 * @brief Free a load matrix object.
 *
 * @param [in] matrix - given matrix object to free.
 */
void free_load_matrix(load_matrix_t *matrix);

/**
 * @brief Set load matrix value.
 *
 * @param [in] matrix - given load matrix.
 * @param [in] from_node - given source node index.
 * @param [in] to_node - given destination node index.
 * @param [in] load - given load to set.
 */
void load_matrix_set(load_matrix_t *matrix, int32_t from_node, int32_t to_node, int32_t load);

/**
 * @brief Get load matrix value.
 *
 * @param matrix - given load matrix.
 * @param [in] from_node - given source node index.
 * @param [in] to_node - given destination node index.
 * @return matrix load.
 */
int32_t load_matrix_get(const load_matrix_t *matrix, int32_t from_node, int32_t to_node);

/**
 * @brief Display load matrix on the screen.
 *
 * @param matrix - given load matrix to display.
 */
void print_load_matrix(const load_matrix_t *matrix);

#endif // NET_DESIGN_LOAD_MATRIX_H