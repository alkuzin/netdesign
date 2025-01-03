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
#include <netdesign/menu.h>


static void on_docs_action(GtkWidget *widget, gpointer data);
static void on_about_action(GtkWidget *widget, gpointer data);

void netd_set_info_menu(void)
{
    auto info_menu = gtk_menu_new();

    auto docs_action  = gtk_menu_item_new_with_label("Documentation");
    auto about_action = gtk_menu_item_new_with_label("About");

    gtk_menu_shell_append(GTK_MENU_SHELL(info_menu), docs_action);
    gtk_menu_shell_append(GTK_MENU_SHELL(info_menu), about_action);

    g_signal_connect(docs_action,  "activate", G_CALLBACK(on_docs_action), nullptr);
    g_signal_connect(about_action, "activate", G_CALLBACK(on_about_action), nullptr);

    auto info_menu_item = gtk_menu_item_new_with_label("Info");
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(info_menu_item), info_menu);
    gtk_menu_shell_append(GTK_MENU_SHELL(app.menu_bar), info_menu_item);
}

static void on_docs_action(GtkWidget *widget, gpointer data)
{
    IGNORE_UNUSED(widget);
    IGNORE_UNUSED(data);

    g_print("Docs action triggered\n");
}

static void on_about_action(GtkWidget *widget, gpointer data)
{
    IGNORE_UNUSED(widget);
    IGNORE_UNUSED(data);

    g_print("About action triggered\n");
}