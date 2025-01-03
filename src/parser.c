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

#include <netdesign/parser.h>
#include <netdesign/utils.h>
#include <stdlib.h>
#include <stdio.h>
#include <glib.h>

#define LINE_SIZE 256

static void parse_nodes(FILE *file, char *line, proj_context_t *context);
static void parse_load_matrix(FILE *file, char *line, proj_context_t *context);
static void parse_routers(FILE *file, char *line, proj_context_t *context);
static void parse_channels(FILE *file, char *line, proj_context_t *context);
static void parse_packet_size(FILE *file, char *line, proj_context_t *context);


void netd_parse_project_file(const char *filename, proj_context_t *context)
{
    FILE *file = fopen(filename, "r");

    if (!file) {
        // TODO: implement error function
        perror("netdesign: error to open file\n");
        exit(EXIT_FAILURE);
    }

    char line[LINE_SIZE];

    while (fgets(line, LINE_SIZE, file)) {
        if (strncmp(line, "# Nodes", 7) == 0)
            parse_nodes(file, line, context);

        if (strncmp(line, "# Load Matrix", 13) == 0)
            parse_load_matrix(file, line, context);

        if (strncmp(line, "# Routers", 9) == 0)
            parse_routers(file, line, context);

        if (strncmp(line, "# Channels", 10) == 0)
            parse_channels(file, line, context);

        if (strncmp(line, "# Packet Size", 13) == 0)
            parse_packet_size(file, line, context);
    }

    netd_print_project_context(context);
    fclose(file);
}

static void parse_nodes(FILE *file, char *line, proj_context_t *context)
{
    fscanf(file, "count,%u", &context->nodes_count);
    fgets(line, LINE_SIZE, file); // skip line

    // parsing header line
    fgets(line, LINE_SIZE, file);
    context->nodes = g_new(node_t, (gsize)context->nodes_count);

    // TODO: free project context data on exit

    uint32_t i   = 0;
    node_t *node = nullptr;

    while (fgets(line, LINE_SIZE, file) && i < context->nodes_count && line[0] != '#') {
        node = &context->nodes[i];
        sscanf(line, "%u,%15[^,],%u,%u", &node->id, node->name, &node->x, &node->y);
        i++;
    }
}

static void parse_load_matrix(FILE *file, char *line, proj_context_t *context)
{
    int32_t count = 0;
    fscanf(file, "count,%d", &count);

    context->matrix = create_load_matrix(count);
    fgets(line, LINE_SIZE, file); // skip line

    char *token = nullptr;

    for (int32_t i = 0; i < count; i++) {
        fgets(line, LINE_SIZE, file);
        token = strtok(line, ",");

        for (int32_t j = 0; j < count; j++) {
            if (token != nullptr) {
                load_matrix_set(context->matrix, i, j, atoi(token));
                token = strtok(nullptr, ",");
            }
        }
    }
}

static void parse_routers(FILE *file, char *line, proj_context_t *context)
{
    fscanf(file, "count,%u", &context->routers_count);
    fgets(line, LINE_SIZE, file); // skip line

    context->router_table = g_new(router_t, (gsize)context->routers_count);

    router_t *router = nullptr;
    uint32_t i = 0;

    // parsing header line
    fgets(line, LINE_SIZE, file);
    while (fgets(line, LINE_SIZE, file) && i < context->routers_count && line[0] != '#') {
        router = &context->router_table[i];
        sscanf(line, "%u,%63[^,],%u,%u", &router->id, router->model, &router->bandwidth, &router->price);
        i++;
    }
}

static void parse_channels(FILE *file, char *line, proj_context_t *context)
{
    fgets(line, LINE_SIZE, file); // skip line
    sscanf(line, "count,%u", &context->channels_count);
    fgets(line, LINE_SIZE, file); // parsing header line

    context->channel_table = g_new(channel_t, (gsize)context->routers_count);

    channel_t *channel = nullptr;
    uint32_t i = 0;

    while (fgets(line, LINE_SIZE, file) && i < context->channels_count && line[0] != '#') {
        channel = &context->channel_table[i];
        sscanf(line, "%u,%u,%u", &channel->id, &channel->bandwidth, &channel->price);
        i++;
    }
}

static void parse_packet_size(FILE *file, char *line, proj_context_t *context)
{
    fgets(line, LINE_SIZE, file);
    sscanf(line, "packet_size,%u", &context->packet_size);
}