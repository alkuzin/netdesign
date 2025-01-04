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

#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLineEdit>
#include <NetDesign/Tabs.hpp>
#include <QtWidgets/QLabel>


namespace netd {
namespace tab {

struct SettingsTab {
    QTabWidget     *tab;
    QHBoxLayout    *mainLayout;
    QListWidget    *list;
    QStackedWidget *content;
};

static void setNodeSettings(SettingsTab& settings) noexcept;
static void setNodeCount(QWidget *nodeSettings, QVBoxLayout *nodeLayout) noexcept;


QTabWidget *setSettingsTab(void) noexcept
{
    SettingsTab settings;

    settings.tab        = new QTabWidget();
    settings.mainLayout = new QHBoxLayout(settings.tab);
    settings.list       = new QListWidget(settings.tab);
    settings.content    = new QStackedWidget(settings.tab);

    setNodeSettings(settings);

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

static void setNodeSettings(SettingsTab& settings) noexcept
{
    settings.list->addItem("Node");

    auto nodeSettings = new QWidget();
    auto nodeLayout   = new QVBoxLayout(nodeSettings);

    setNodeCount(nodeSettings, nodeLayout);

    settings.content->addWidget(nodeSettings);
}

static void setNodeCount(QWidget *nodeSettings, QVBoxLayout *nodeLayout) noexcept
{
    auto layout = new QHBoxLayout();
    auto label  = new QLabel("Node count: ");

    label->setMaximumWidth(100);
    layout->addWidget(label);

    // handle input
    auto lineEdit = new QLineEdit();
    lineEdit->setMaximumWidth(100);
    layout->addWidget(lineEdit);

    auto submitButton = new QPushButton("Submit");
    submitButton->setMaximumWidth(100);
    layout->addWidget(submitButton);

    // connecting the button's clicked signal
    QObject::connect(submitButton, &QPushButton::clicked, [lineEdit]() {
        bool ok;
        int numberOfNodes = lineEdit->text().toInt(&ok);

        // TODO: add nodes count to ProjectContext
        if (ok)
            QMessageBox::information(nullptr, "Input", "Number of nodes: " + QString::number(numberOfNodes));
        else
            QMessageBox::warning(nullptr, "Input Error", "Please enter a valid number");
    });

    nodeLayout->addLayout(layout);
    nodeLayout->setAlignment(Qt::AlignTop);
    nodeSettings->setLayout(nodeLayout);
}

} // namespace tab
} // namespace netd