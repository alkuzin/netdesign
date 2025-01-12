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

#ifndef NET_DESIGN_SETTINGS_VIEW_HPP
#define NET_DESIGN_SETTINGS_VIEW_HPP

#include <NetDesign/RouterController.hpp>
#include <NetDesign/NodeController.hpp>
#include <QtWidgets/QStackedWidget>
#include <NetDesign/RouterView.hpp>
#include <NetDesign/NodeView.hpp>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QTabWidget>


namespace netd {

class SettingsView : public QObject
{
    private:
        RouterController *m_routerController;
        NodeController   *m_nodeController;
        RouterView       *m_routerView;
        NodeView         *m_nodeView;
        QHBoxLayout      *m_mainLayout;
        QStackedWidget   *m_content;
        QListWidget      *m_list;

    public:
        QWidget *m_tab;

        SettingsView(QWidget *parent = nullptr) noexcept;
        void updateContent(void) noexcept;
};

} // namespace netd

#endif // NET_DESIGN_SETTINGS_VIEW_HPP
