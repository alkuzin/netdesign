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

#ifndef NET_DESIGN_PROJECT_CONTEXT_H
#define NET_DESIGN_PROJECT_CONTEXT_H

#include <netdesign/load_matrix.h>
#include <netdesign/channel.h>
#include <netdesign/router.h>
#include <netdesign/node.h>


struct project_context {
    node_t         *nodes;
    load_matrix_t  *matrix;
    router_t       *router_table;
    channel_t      *channel_table;
    uint32_t        nodes_count;
    uint32_t        routers_count;
    uint32_t        channels_count;
    uint32_t        packet_size;
};

typedef struct project_context proj_context_t;

#endif // NET_DESIGN_PROJECT_CONTEXT_H