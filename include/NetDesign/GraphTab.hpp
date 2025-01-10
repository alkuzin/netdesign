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

#ifndef NET_DESIGN_GRAPH_TAB_HPP
#define NET_DESIGN_GRAPH_TAB_HPP

#include <NetDesign/NetworkGraph.hpp>
#include <QtWidgets/QGraphicsScene>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLabel>


namespace netd {
namespace tab {

class GraphTab : public QTabWidget {
    QGraphicsScene *m_scene;
    QVBoxLayout    *m_buttonLayout;
    QVBoxLayout    *m_graphLayout;
    QHBoxLayout    *m_mainLayout;
    NetworkGraph   m_graph;
    std::uint32_t Channel::* m_weight;
    QLabel        *m_delayLabel;
    QLabel        *m_priceLabel;
    QComboBox     *m_srcNodeComboBox;
    QComboBox     *m_destNodeComboBox;

    public:
        GraphTab(void) noexcept;
        void updateTabs(void) noexcept;

    private:
        void setGraphLayout(void) noexcept;
        void setButtonLayout(void) noexcept;
        void drawNode(const Node& node) noexcept;
        void drawEdge(const Node& src, const Node& dest, const Channel& channel) noexcept;
        void clearGraph(void) noexcept;
};

} // namespace tab
} // namespace netd

#endif // NET_DESIGN_GRAPH_TAB_HPP