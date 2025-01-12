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

#include <NetDesign/MainWindow.hpp>


namespace netd {

constexpr auto WINDOW_TITLE         {"NetDesign"};
constexpr auto WINDOW_MIN_WIDTH     {1024};
constexpr auto WINDOW_MIN_HEIGHT    {768};
constexpr auto WINDOW_MAX_WIDTH     {1920};
constexpr auto WINDOW_MAX_HEIGHT    {1080};

MainWindow::MainWindow(void) noexcept
{
    // set window properties
    setWindowTitle(WINDOW_TITLE);
    setMinimumSize(WINDOW_MIN_WIDTH, WINDOW_MIN_HEIGHT);
    setMaximumSize(WINDOW_MAX_WIDTH, WINDOW_MAX_HEIGHT);

    // set menu
    m_menuView       = new MenuView(this);
    m_menuController = new MenuController(m_menuView, this);
    setMenuBar(m_menuView->getMenuBar());

    // set tabs
    m_tabView       = new TabView(this);
    m_tabController = new TabController(m_tabView, this);

    setCentralWidget(m_tabView->getTabWidget());
}

void MainWindow::updateContent(void) noexcept
{
    m_tabController->updateContent();
}

MainWindow *mainWindow {nullptr};

} // namespace netd