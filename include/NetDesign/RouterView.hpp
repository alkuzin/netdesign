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

#ifndef NET_DESIGN_ROUTER_VIEW_HPP
#define NET_DESIGN_ROUTER_VIEW_HPP

#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLineEdit>


namespace netd {

class RouterView : public QObject
{
    private:
        QVBoxLayout  *m_mainLayout;
        QHBoxLayout  *m_tableLayout;

        void setPacketSizeLayout(void) noexcept;
        void setRouterTableLayout(void) noexcept;
        void setChannelTableLayout(void) noexcept;

    public:
        QWidget      *m_mainWidget;
        QTableWidget *m_routerTable;
        QTableWidget *m_channelTable;
        QLineEdit    *m_lineEdit;
        QPushButton  *m_submitButton;

        QPushButton  *m_saveRouterButton;
        QPushButton  *m_addRouterButton;
        QPushButton  *m_removeRouterButton;

        QPushButton  *m_saveChannelButton;
        QPushButton  *m_addChannelButton;
        QPushButton  *m_removeChannelButton;

        RouterView(QWidget *parent = nullptr) noexcept;
};

} // namespace netd

#endif // NET_DESIGN_ROUTER_VIEW_HPP