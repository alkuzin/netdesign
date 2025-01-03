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

#ifndef NET_DESIGN_APP_H
#define NET_DESIGN_APP_H

#include <netdesign/project_context.h>
#include <gtk/gtk.h>


struct netd_app {
    char proj_filename[FILENAME_MAX];
    proj_context_t context;
    GtkWidget *menu_bar;
    GtkWidget *window;
};

extern struct netd_app app;

void netd_app_init(int32_t *argc, char ***argv);

#endif // NET_DESIGN_APP_H