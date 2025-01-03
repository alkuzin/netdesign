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

#include <netdesign/utils.h>
#include <stdio.h>


void netd_print_project_context(const proj_context_t *context)
{
    puts(
        "----------------------------------------------\n"
        "-------------Project-Context------------------\n"
        "----------------------------------------------\n"
    );

    printf("Nodes [count: %u]\n", context->nodes_count);

    for (uint32_t i = 0; i < context->nodes_count; i++) {
        printf("id: %2u, name: %-16s, (x: %3u, y: %3u)\n",
            context->nodes[i].id,
            context->nodes[i].name,
            context->nodes[i].x,
            context->nodes[i].y
        );
    }

    printf("\nLoad Matrix [count: %u]\n", context->matrix->size);
    print_load_matrix(context->matrix);

    printf("\nRouters Table [count: %u]\n", context->routers_count);

    for (uint32_t i = 0; i < context->routers_count; i++) {
        printf("id: %2u, model: %-32s, bandwidth: %5u KB/sec, price: %6u RUB\n",
            context->router_table[i].id,
            context->router_table[i].model,
            context->router_table[i].bandwidth,
            context->router_table[i].price
        );
    }

    printf("\nChannels Table [count: %u]\n", context->channels_count);

    for (uint32_t i = 0; i < context->channels_count; i++) {
        printf("id: %2u, bandwidth: %6u KB/sec, price: %6u RUB\n",
            context->channel_table[i].id,
            context->channel_table[i].bandwidth,
            context->channel_table[i].price
        );
    }

    printf("\nPacket size: %u KB\n", context->packet_size);
    puts("----------------------------------------------\n");
}