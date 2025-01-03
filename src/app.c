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

#include <netdesign/config.h>
#include <netdesign/menu.h>


struct netd_app app;

static void menu_init(void)
{
    app.menu_bar = gtk_menu_bar_new();

    netd_set_project_menu();
    netd_set_edit_menu();
    netd_set_estimate_menu();
    netd_set_info_menu();

    auto vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_box_pack_start(GTK_BOX(vbox), app.menu_bar, false, false, 0);
    gtk_container_add(GTK_CONTAINER(app.window), vbox);
}

void netd_app_init(int32_t *argc, char ***argv)
{
    gtk_init(argc, argv);

    app.window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(app.window), NETD_APP_TITLE);
    gtk_window_set_default_size(
        GTK_WINDOW(app.window),
        NETD_APP_WIDTH,
        NETD_APP_HEIGHT
    );
    g_signal_connect(app.window, "destroy", G_CALLBACK(gtk_main_quit), nullptr);

    menu_init();

    gtk_widget_show_all(app.window);
    gtk_main();
}