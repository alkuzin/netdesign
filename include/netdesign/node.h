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

#ifndef NET_DESIGN_NODE_H
#define NET_DESIGN_NODE_H

#include <stdint.h>


#define NODE_NAME_SIZE 16

struct node {
    char     name[NODE_NAME_SIZE];
    uint32_t id;
    uint32_t x;
    uint32_t y;
};

typedef struct node node_t;

#endif // NET_DESIGN_NODE_H