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

#include <NetDesign/ProjectContext.hpp>
#include <QtWidgets/QApplication>
#include <QtWidgets/QInputDialog>
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QFileDialog>
#include <NetDesign/Utils.hpp>
#include <NetDesign/Menu.hpp>


namespace netd {
namespace menu {

static QString createFile(void) noexcept;
static QString openFile(void) noexcept;

void onProjectNew(void) noexcept
{
    auto filename = createFile();

    if (filename.isEmpty() || (projectContext.filename.compare(filename.toStdString()) == 0))
        return;

    projectContext.filename = std::move(filename.toStdString());
}

void onProjectOpen(void) noexcept
{
    auto filename = openFile();

    if (filename.isEmpty())
        return;

    projectContext.filename = std::move(filename.toStdString());
    convertToContext(projectContext.filename, projectContext);
}

void onProjectSave(void) noexcept
{
    if (projectContext.filename.empty())
        onProjectNew();

    convertToXML(projectContext.filename, projectContext);
}

void onProjectExit(void) noexcept
{
    QMessageBox::StandardButton reply;

    reply = QMessageBox::question(
        nullptr,
        "Confirm Exit",
        "Are you sure you want to exit?",
        QMessageBox::Yes | QMessageBox::No
    );

    if (reply == QMessageBox::Yes)
        QApplication::quit();
}

static QString createFile(void) noexcept
{
    bool ok;
    QString filename = QInputDialog::getText(
        nullptr,
        "Create New Project",
        "Project Name:",
        QLineEdit::Normal,
        "",
        &ok
    );

    QFileInfo fileinfo(filename);

    // append .xml, if there is no file extension
    if (fileinfo.suffix().isEmpty())
        filename += ".xml";

    isExistRename(filename, "_new.xml");

    if (ok && !filename.isEmpty()) {
        QFile file(filename);

        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QMessageBox::information(
                nullptr,
                "Project Created",
                "Project created successfully: " + filename
            );

            file.close();
        }
        else
            QMessageBox::warning(nullptr, "Error", "Could not create project file.");
    }

    return filename;
}

static QString openFile(void) noexcept
{
    QString filename = QFileDialog::getOpenFileName(
        nullptr,
        "Open File",
        "",
        "XML Files (*.xml);;All Files (*)"
    );

    return filename;
}

} // namespace menu
} // namespace netd