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
#include <NetDesign/NodeSettings.hpp>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <NetDesign/Utils.hpp>


namespace netd {
namespace tab {

QTabWidget *setSettingsTab(void) noexcept
{
    static SettingsTab settings;

    settings.tab        = new QTabWidget();
    settings.mainLayout = new QHBoxLayout(settings.tab);
    settings.list       = new QListWidget(settings.tab);
    settings.content    = new QStackedWidget(settings.tab);

    static NodeSettings nodeSettings(settings);

    // connecting the list widget selection to change the stacked widget
    settings.tab->connect(
        settings.list,
        &QListWidget::currentRowChanged,
        settings.content,
        &QStackedWidget::setCurrentIndex
    );

    // changing font size of list widget entries
    QFont font = settings.list->font();
    font.setPointSize(18);
    settings.list->setFont(font);

    settings.mainLayout->addWidget(settings.list);
    settings.mainLayout->addWidget(settings.content);
    settings.tab->setLayout(settings.mainLayout);

    return settings.tab;
}

} // namespace tab
} // namespace netd