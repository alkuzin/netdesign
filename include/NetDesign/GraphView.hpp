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

#ifndef NET_DESIGN_GRAPH_VIEW_HPP
#define NET_DESIGN_GRAPH_VIEW_HPP

#include <QtWidgets/QGraphicsScene>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QComboBox>
#include <NetDesign/Node.hpp>
#include <QtWidgets/QLabel>


namespace netd {

class GraphView : public QObject
{
    private:
        QHBoxLayout    *m_mainLayout;
        QVBoxLayout    *m_buttonLayout;
        QVBoxLayout    *m_graphLayout;
        QGraphicsScene *m_scene;
        QLabel         *m_delayLabel;
        QLabel         *m_priceLabel;

        void setGraphLayout(void) noexcept;
        void setButtonLayout(void) noexcept;
        void drawNode(const Node& node) noexcept;
        // void drawEdge(const Node& src, const Node& dest, const Channel& channel) noexcept;
        void clearGraph(void) noexcept;
        void highlightPath(const std::vector<std::size_t>& path, const QColor& color) noexcept;

    public:
        QWidget      *m_tab;
        QRadioButton *m_priceRadioButton;
        QRadioButton *m_capacityRadioButton;
        QComboBox    *m_srcNodeComboBox;
        QComboBox    *m_destNodeComboBox;
        QPushButton  *m_updateButton;

        GraphView(QWidget *parent = nullptr) noexcept;
};

} // namespace netd

#endif // NET_DESIGN_GRAPH_VIEW_HPP