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

#include <NetDesign/SettingsView.hpp>


namespace netd {

SettingsView::SettingsView(QWidget *parent) noexcept
{
    m_content    = new QStackedWidget(parent);
    m_mainLayout = new QHBoxLayout();
    m_list       = new QListWidget(parent);
    m_tab        = new QWidget(parent);

    // add node tab
    m_nodeView         = new NodeView(parent);
    m_nodeController   = new NodeController(m_nodeView);

    m_list->addItem("Node & Load Matrix");
    m_content->addWidget(m_nodeView->m_mainWidget);

    // add router tab
    m_routerView       = new RouterView(parent);
    m_routerController = new RouterController(m_routerView);

    m_list->addItem("Routers & Channels");
    m_content->addWidget(m_routerView->m_mainWidget);

    // connect the list widget selection to change the stacked widget
    connect(m_list, &QListWidget::currentRowChanged, m_content, &QStackedWidget::setCurrentIndex);

    // change font size of list widget entries
    QFont font = m_list->font();
    font.setPointSize(18);
    m_list->setFont(font);
    m_list->setMaximumWidth(550);

    m_mainLayout->addWidget(m_list);
    m_mainLayout->addWidget(m_content);
    m_tab->setLayout(m_mainLayout);
}

void SettingsView::updateContent(void) noexcept
{
    m_nodeController->updateContent();
    m_routerController->updateContent();
}

} // namespace netd