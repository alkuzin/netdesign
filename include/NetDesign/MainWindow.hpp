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

#ifndef NETD_MAIN_WINDOW_HPP
#define NETD_MAIN_WINDOW_HPP

#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>


namespace netd {

class MainWindow : public QMainWindow
{
    QMenuBar *m_menuBar;

    private:
        void initMenuBar(void) noexcept;

    public:
        MainWindow(void) noexcept;
};

} // namespace netd

#endif // NETD_MAIN_WINDOW_HPP