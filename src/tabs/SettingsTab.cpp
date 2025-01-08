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
#include <NetDesign/SettingsTab.hpp>


namespace netd {
namespace tab {

SettingsTab::SettingsTab(void) noexcept
{
    mainLayout = new QHBoxLayout(this);
    list       = new QListWidget(this);
    content    = new QStackedWidget(this);

    nodeSettings.set(list, content);
    routerSettings.set(list, content);

    // connecting the list widget selection to change the stacked widget
    connect(list, &QListWidget::currentRowChanged, content, &QStackedWidget::setCurrentIndex);

    // changing font size of list widget entries
    QFont font = list->font();
    font.setPointSize(18);
    list->setFont(font);

    list->setMaximumWidth(550);
    mainLayout->addWidget(list);
    mainLayout->addWidget(content);
    setLayout(mainLayout);
}

void SettingsTab::updateTabs(void) noexcept
{
    nodeSettings.update();
    routerSettings.update();
}

} // namespace tab
} // namespace netd