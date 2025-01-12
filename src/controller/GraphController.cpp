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

#include <NetDesign/GraphController.hpp>


namespace netd {

GraphController::GraphController(GraphView *graphView) noexcept
{
    m_graphView = graphView;

    connect(m_graphView->m_priceRadioButton, &QRadioButton::toggled, this, [this]() {
        this->m_weight = &Channel::m_price;
    });

    connect(m_graphView->m_capacityRadioButton, &QRadioButton::toggled, this, [this]() {
        this->m_weight = &Channel::m_capacity;
    });

    connect(m_graphView->m_updateButton, &QPushButton::clicked, [this]() {
        this->updateContent();
    });
}

void GraphController::updateContent(void) noexcept
{
    // TODO:
}

} // namespace netd