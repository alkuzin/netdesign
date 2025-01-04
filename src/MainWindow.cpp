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

#include <NetDesign/MainWindow.hpp>
#include <NetDesign/Utils.hpp>
#include <NetDesign/Menu.hpp>


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

    m_menuBar   = menuBar();
    m_tabWidget = new QTabWidget(this);
    setCentralWidget(m_tabWidget);

    initMenuBar();
    initTabs();
    show();
}

void MainWindow::initMenuBar(void) noexcept
{
    // "Project" menu
    auto projectMenu = m_menuBar->addMenu("Project");
    auto newAction   = projectMenu->addAction("New");
    auto openAction  = projectMenu->addAction("Open");
    auto saveAction  = projectMenu->addAction("Save");
    auto exitAction  = projectMenu->addAction("Exit");

    connect(newAction,  &QAction::triggered, this, &menu::onProjectNew);
    connect(openAction, &QAction::triggered, this, &menu::onProjectOpen);
    connect(saveAction, &QAction::triggered, this, &menu::onProjectSave);
    connect(exitAction, &QAction::triggered, this, &menu::onProjectExit);

    // "Edit" menu
    auto editMenu       = m_menuBar->addMenu("Edit");
    auto loadFileAction = editMenu->addAction("Load file");

    connect(loadFileAction, &QAction::triggered, this, &menu::onEditLoadFile);

    // "Estimate" menu
    auto estimateMenu = m_menuBar->addMenu("Estimate");
    IGNORE_UNUSED(estimateMenu);

    // "Info" menu
    auto infoMenu    = m_menuBar->addMenu("Info");
    auto docsAction  = infoMenu->addAction("Documentation");
    auto aboutAction = infoMenu->addAction("About");

    connect(docsAction,  &QAction::triggered, this, &menu::onInfoDocs);
    connect(aboutAction, &QAction::triggered, this, menu::onInfoAbout);
}

void MainWindow::initTabs(void) noexcept
{
    // TODO:
    // NodeTabView *nodeTabView = new NodeTabView(m_projectContext);
    // m_tabWidget->addTab(nodeTabView, "Node");
}

} // namespace netd