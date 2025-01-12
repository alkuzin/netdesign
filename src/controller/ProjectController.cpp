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

#include <NetDesign/ProjectController.hpp>
#include <NetDesign/ProjectContext.hpp>
#include <NetDesign/MainWindow.hpp>
#include <QtWidgets/QApplication>
#include <QtWidgets/QInputDialog>
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QFileDialog>
#include <NetDesign/Utils.hpp>


namespace netd {

static QString createFile(void) noexcept;
static QString openFile(void) noexcept;

static auto& projectContext = ProjectContext::instance();


void ProjectController::createProject(void) noexcept
{
    auto filename = createFile();

    if (filename.isEmpty() || (projectContext.m_filename.compare(filename.toStdString()) == 0))
        return;

    projectContext.m_filename = std::move(filename.toStdString());
}

void ProjectController::openProject(void) noexcept
{
    auto filename = openFile();

    if (filename.isEmpty())
        return;

    projectContext.m_filename = std::move(filename.toStdString());

    m_parser.parse(projectContext.m_filename);
    mainWindow->updateContent();
}

void ProjectController::saveProject(void) noexcept
{
    const auto& context  = projectContext;
    const auto& filename = context.m_filename;

    if (filename.empty())
        createProject();

    std::ofstream fout(filename.data(), std::ios::out);

    if (!fout.is_open()) {
        QMessageBox::warning(nullptr, "Error", "Could not create project file.");
        return;
    }

    // saving nodes
    fout << "# Nodes\n";
    fout << "count," << context.m_nodes.size() << "\n";
    fout << "id,name,x,y\n";

    for (const auto& node : context.m_nodes) {
        fout << node.m_id << ",";
        fout << node.m_name << ",";
        fout << node.m_x << ",";
        fout << node.m_y << "\n";
    }
    fout << "\n";

    // saving load matrix
    auto matrixCount = context.m_loadMatrix.size1();

    fout << "# Load Matrix\n";
    fout << "count," << matrixCount << "\n";

    for (std::size_t i = 0; i < matrixCount; i++) {
        for (std::size_t j = 0; j < matrixCount; j++)
            fout << context.m_loadMatrix(i, j) << ",";
        fout << "\n";
    }
    fout << "\n";

    // saving routers
    fout << "# Routers\n";
    fout << "count," << context.m_routers.size() << "\n";
    fout << "id,model,capacity,price\n";

    for (const auto& router : context.m_routers) {
        fout << router.m_id << ",";
        fout << router.m_model << ",";
        fout << router.m_capacity << ",";
        fout << router.m_price << "\n";
    }
    fout << "\n";

    // saving channels
    fout << "# Channels\n";
    fout << "count," << context.m_channels.size() << "\n";
    fout << "id,capacity,price\n";

    for (const auto& channel : context.m_channels) {
        fout << channel.m_id << ",";
        fout << channel.m_capacity << ",";
        fout << channel.m_price << "\n";
    }

    fout << "\n# Packet Size\n";
    fout << "size," << context.m_packetSize << "\n";
    fout.close();
}

void ProjectController::exitProject(void) noexcept
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

    // append .ndproj, if there is no file extension
    if (fileinfo.suffix().isEmpty())
        filename += ".ndproj";

    isExistRename(filename, "_new.ndproj");

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
        "NetDesign Project Files (*.ndproj);;All Files (*)"
    );

    return filename;
}

} // namespace netd