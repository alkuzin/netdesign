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

#include <netdesign/menu.h>


void netd_set_estimate_menu(void)
{
    auto estimate_menu = gtk_menu_new();

    auto estimate_menu_item = gtk_menu_item_new_with_label("Estimate");
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(estimate_menu_item), estimate_menu);
    gtk_menu_shell_append(GTK_MENU_SHELL(app.menu_bar), estimate_menu_item);
}