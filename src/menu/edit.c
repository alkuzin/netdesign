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


static void on_load_file_action(GtkWidget *widget, gpointer data);

void netd_set_edit_menu(void)
{
    auto edit_menu = gtk_menu_new();

    auto load_file_action = gtk_menu_item_new_with_label("Load file");
    gtk_menu_shell_append(GTK_MENU_SHELL(edit_menu), load_file_action);
    g_signal_connect(load_file_action,  "activate", G_CALLBACK(on_load_file_action), nullptr);

    auto edit_menu_item = gtk_menu_item_new_with_label("Edit");
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(edit_menu_item), edit_menu);
    gtk_menu_shell_append(GTK_MENU_SHELL(app.menu_bar), edit_menu_item);
}

static void on_load_file_action(GtkWidget *widget, gpointer data)
{
    IGNORE_UNUSED(widget);
    g_print("Load file action triggered\n");

    // creating a file chooser dialog
    auto dialog = gtk_file_chooser_dialog_new(
        "Open File",
        GTK_WINDOW(data),
        GTK_FILE_CHOOSER_ACTION_OPEN,
        "_Cancel", GTK_RESPONSE_CANCEL,
        "_Open", GTK_RESPONSE_ACCEPT,
        nullptr
    );

    // creating a file filter for specific file extensions
    auto filter = gtk_file_filter_new();
    gtk_file_filter_set_name(filter, "CSV files");
    gtk_file_filter_add_pattern(filter, "*.csv");

    gtk_file_chooser_add_filter(GTK_FILE_CHOOSER(dialog), filter);

    // displaying the dialog and waiting for a response
    if (gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_ACCEPT) {
        auto file_chooser = GTK_FILE_CHOOSER(dialog);
        char *filename    = gtk_file_chooser_get_filename(file_chooser);

        printf("Selected file: %s\n", filename);
        // TODO: handle file

        g_free(filename);
    }

    gtk_widget_destroy(dialog);
}