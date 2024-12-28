/**
 * NetDesign - simple network design tool.
 * Copyright (C) 2024-2025 Alexander (@alkuzin)
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

#include <NetDesign/MenuController.hpp>
#include <NetDesign/MainWindow.hpp>
#include <NetDesign/Utils.hpp>


namespace netd {

constexpr auto WINDOW_TITLE         {"NetDesign"};
constexpr auto WINDOW_MIN_WIDTH     {1024};
constexpr auto WINDOW_MIN_HEIGHT    {768};
constexpr auto WINDOW_MAX_WIDTH     {1920};
constexpr auto WINDOW_MAX_HEIGHT    {1080};


MainWindow::MainWindow(void) noexcept
{
    setWindowTitle(WINDOW_TITLE);
    setMinimumSize(WINDOW_MIN_WIDTH, WINDOW_MIN_HEIGHT);
    setMaximumSize(WINDOW_MAX_WIDTH, WINDOW_MAX_HEIGHT);

    m_menuBar = menuBar();

    initMenuBar();
    show();
}

void MainWindow::initMenuBar(void) noexcept
{
    MenuController menuController;

    // "Project" menu
    QMenu *projectMenu  = m_menuBar->addMenu("Project");
    QAction *newAction  = projectMenu->addAction("New");
    QAction *openAction = projectMenu->addAction("Open");
    QAction *saveAction = projectMenu->addAction("Save");
    QAction *exitAction = projectMenu->addAction("Exit");

    connect(newAction, &QAction::triggered, this, [&menuController]() {
        menuController.onProjectNew();
    });

    connect(openAction, &QAction::triggered, this, [&menuController]() {
        menuController.onProjectOpen();
    });

    connect(saveAction, &QAction::triggered, this, [&menuController]() {
        menuController.onProjectSave();
    });

    connect(exitAction, &QAction::triggered, this, [&menuController]() {
        menuController.onProjectExit();
    });

    // "Edit" menu
    QMenu *editMenu         = m_menuBar->addMenu("Edit");
    QAction *loadFileAction = editMenu->addAction("Load file");

    connect(loadFileAction, &QAction::triggered, this, [&menuController]() {
        menuController.onEditLoadFile();
    });

    // "Estimate" menu
    QMenu *estimateMenu = m_menuBar->addMenu("Estimate");
    IGNORE_UNUSED(estimateMenu);

    // "Info" menu
    QMenu *infoMenu      = m_menuBar->addMenu("Info");
    QAction *docsAction  = infoMenu->addAction("Documentation");
    QAction *aboutAction = infoMenu->addAction("About");

    connect(docsAction, &QAction::triggered, this, [&menuController]() {
        menuController.onInfoDocs();
    });

    connect(aboutAction, &QAction::triggered, this, [&menuController]() {
        menuController.onInfoAbout();
    });
}

} // namespace netd