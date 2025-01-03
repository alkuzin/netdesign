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
#include <netdesign/menu.h>
#include <netdesign/app.h>
#include <limits.h>


static void on_new_action(GtkWidget *widget, gpointer data);
static void on_open_action(GtkWidget *widget, gpointer data);
static void on_save_action(GtkWidget *widget, gpointer data);
static void on_exit_action(GtkWidget *widget, gpointer data);

void netd_set_project_menu(void)
{
    auto project_menu = gtk_menu_new();

    auto new_action  = gtk_menu_item_new_with_label("New");
    auto open_action = gtk_menu_item_new_with_label("Open");
    auto save_action = gtk_menu_item_new_with_label("Save");
    auto exit_action = gtk_menu_item_new_with_label("Exit");

    gtk_menu_shell_append(GTK_MENU_SHELL(project_menu), new_action);
    gtk_menu_shell_append(GTK_MENU_SHELL(project_menu), open_action);
    gtk_menu_shell_append(GTK_MENU_SHELL(project_menu), save_action);
    gtk_menu_shell_append(GTK_MENU_SHELL(project_menu), exit_action);

    g_signal_connect(new_action,  "activate", G_CALLBACK(on_new_action), nullptr);
    g_signal_connect(open_action, "activate", G_CALLBACK(on_open_action), nullptr);
    g_signal_connect(save_action, "activate", G_CALLBACK(on_save_action), nullptr);
    g_signal_connect(exit_action, "activate", G_CALLBACK(on_exit_action), nullptr);

    auto project_menu_item = gtk_menu_item_new_with_label("Project");
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(project_menu_item), project_menu);
    gtk_menu_shell_append(GTK_MENU_SHELL(app.menu_bar), project_menu_item);
}

static void create_file(char *filename, gpointer data)
{
    auto dialog = gtk_dialog_new_with_buttons(
        "Create New Project File",
        GTK_WINDOW(data),
        GTK_DIALOG_MODAL,
        "_Cancel", GTK_RESPONSE_CANCEL,
        "_Create", GTK_RESPONSE_ACCEPT,
        nullptr
    );

    auto content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));

    auto label = gtk_label_new("Enter project filename:");
    gtk_box_pack_start(GTK_BOX(content_area), label, true, true, 0);

    auto entry = gtk_entry_new();
    gtk_box_pack_start(GTK_BOX(content_area), entry, true, true, 0);

    gtk_widget_show_all(dialog);

    if (gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_ACCEPT) {
        strncpy(filename, gtk_entry_get_text(GTK_ENTRY(entry)), FILENAME_MAX - 1);
        strncat(filename, ".ndproj", FILENAME_MAX);
    }

    gtk_widget_destroy(dialog);
}

static void on_new_action(GtkWidget *widget, gpointer data)
{
    IGNORE_UNUSED(widget); IGNORE_UNUSED(data);
    create_file(app.proj_filename, data);

    FILE *project_file = fopen(app.proj_filename, "wr+");

    if (project_file) {
        printf("File created: %s\n", app.proj_filename);
        fclose(project_file);
    }
    else
        printf("Failed to create file: %s\n", app.proj_filename);
}

static void on_file_selected(GtkFileChooser *file_chooser)
{
    char *filename = gtk_file_chooser_get_filename(file_chooser);

    strncpy(app.proj_filename, filename, FILENAME_MAX - 1);
    netd_parse_project_file(filename, &app.context);

    g_free(filename);
}

static void on_open_action(GtkWidget *widget, gpointer data)
{
    IGNORE_UNUSED(widget);
    g_print("Open action triggered\n");

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
    gtk_file_filter_set_name(filter, "NetDesign project files");
    gtk_file_filter_add_pattern(filter, "*.ndproj");

    gtk_file_chooser_add_filter(GTK_FILE_CHOOSER(dialog), filter);

    // displaying the dialog and waiting for a response
    if (gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_ACCEPT) {
        auto file_chooser = GTK_FILE_CHOOSER(dialog);
        on_file_selected(file_chooser);
    }

    gtk_widget_destroy(dialog);
}

static void on_save_action(GtkWidget *widget, gpointer data)
{
    IGNORE_UNUSED(widget);
    IGNORE_UNUSED(data);

    g_print("Save action triggered\n");
}

static void on_exit_action(GtkWidget *widget, gpointer data)
{
    IGNORE_UNUSED(widget);
    IGNORE_UNUSED(data);

    auto dialog = gtk_message_dialog_new(
        GTK_WINDOW(data),
        GTK_DIALOG_DESTROY_WITH_PARENT,
        GTK_MESSAGE_QUESTION,
        GTK_BUTTONS_YES_NO,
        "Do you really want to exit?"
    );

    gtk_window_set_title(GTK_WINDOW(dialog), "Exit from NetDesign");

    int32_t response = gtk_dialog_run(GTK_DIALOG(dialog));

    // TODO: save on exit
    if (response == GTK_RESPONSE_YES)
        gtk_main_quit();

    gtk_widget_destroy(dialog);
}