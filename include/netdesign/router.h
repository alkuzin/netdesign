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

#ifndef NET_DESIGN_ROUTER_H
#define NET_DESIGN_ROUTER_H

#include <stdint.h>


#define ROUTER_MODEL_SIZE 64

struct router {
    uint32_t id;
    char     model[ROUTER_MODEL_SIZE];
    uint32_t bandwidth; // (KB/sec)
    uint32_t price;
};

typedef struct router router_t;

#endif // NET_DESIGN_ROUTER_H