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

#include <netdesign/load_matrix.h>
#include <stdio.h>
#include <glib.h>


load_matrix_t *create_load_matrix(int32_t size)
{
    load_matrix_t *matrix = g_new(load_matrix_t, 1);
    matrix->size = size;

    // allocating memory
    matrix->data = g_new(int32_t*, (gsize)size);

    for (int32_t i = 0; i < size; i++)
        matrix->data[i] = g_new(int32_t, (gsize)size);

    // filling matrix with zeros
    for (int32_t i = 0; i < size; i++) {
        for (int32_t j = 0; j < size; j++)
            matrix->data[i][j] = 0.0;
    }

    return matrix;
}

void free_load_matrix(load_matrix_t *matrix)
{
    for (int i = 0; i < matrix->size; i++)
        g_free(matrix->data[i]);

    g_free(matrix->data);
    g_free(matrix);
}

void load_matrix_set(load_matrix_t *matrix, int32_t from_node, int32_t to_node, int32_t load)
{
    if (from_node < matrix->size && to_node < matrix->size)
        matrix->data[from_node][to_node] = load;
}

int32_t load_matrix_get(const load_matrix_t *matrix, int32_t from_node, int32_t to_node)
{
    if (from_node < matrix->size && to_node < matrix->size)
        return matrix->data[from_node][to_node];

    return -1;
}

void print_load_matrix(const load_matrix_t *matrix)
{
    int32_t end = matrix->size - 1;

    for (int32_t i = 0; i < matrix->size; i++) {
        putchar('|');
        putchar(' ');

        for (int32_t j = 0; j < matrix->size; j++) {
            printf("%5d", matrix->data[i][j]);

            if (j != end) {
                putchar(',');
                putchar(' ');
            }
        }

        puts(" |");
    }
}