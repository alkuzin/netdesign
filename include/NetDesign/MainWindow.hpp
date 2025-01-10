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

#ifndef NET_DESIGN_MAIN_WINDOW_HPP
#define NET_DESIGN_MAIN_WINDOW_HPP

#include <NetDesign/SettingsTab.hpp>
#include <NetDesign/GraphTab.hpp>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>


namespace netd {

class MainWindow : public QMainWindow {
    QTabWidget       *m_tabWidget;
    QMenuBar         *m_menuBar;
    tab::SettingsTab *m_settingsTab;
    tab::GraphTab    *m_graphTab;

    private:
        MainWindow(void) noexcept;
        void initMenuBar(void) noexcept;
        void initTabs(void) noexcept;

    protected:
        void keyPressEvent(QKeyEvent *event) noexcept override;

    public:
        static MainWindow *getInstance(void) noexcept {
            static MainWindow instance;
            return &instance;
        }

        void updateTabs(void) noexcept;
};

} // namespace netd

#endif // NET_DESIGN_MAIN_WINDOW_HPP