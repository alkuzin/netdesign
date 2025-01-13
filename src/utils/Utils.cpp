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
#include <NetDesign/Utils.hpp>
#include <filesystem>
#include <print>


namespace netd {

QString getItem(const QTableWidget *table, std::size_t row, std::size_t column) noexcept
{
    auto item = table->item(
        static_cast<std::int32_t>(row),
        static_cast<std::int32_t>(column)
    );

    return item->text();
}

void printProjectContext(void) noexcept
{
    const auto& context = ProjectContext::instance();
    std::println("Node Count: {}\nNodes:", context.m_nodes.size());

    for (const auto& node : context.m_nodes) {
        std::println("node: | id: {}, name: {}, x: {}, y: {} |",
            node.m_id, node.m_name, node.m_x, node.m_y
        );
    }

    std::puts("\nLoad Matrix:");
    for (size_t i = 0; i < context.m_loadMatrix.size1(); i++) {
        std::putchar('|');
        for (size_t j = 0; j < context.m_loadMatrix.size2(); j++)
            std::print(" {:>3}", context.m_loadMatrix(i, j));
        std::puts("   |");
    }
    std::putchar('\n');

    std::puts("\nEdge Table:");
    for (size_t i = 0; i < context.m_edgeTable.size1(); i++) {
        std::putchar('|');
        for (size_t j = 0; j < 3; j++)
            std::print(" {:>3}", context.m_edgeTable(i, j));
        std::puts("   |");
    }
    std::putchar('\n');

    std::puts("\nRouter Table:");
    for (const auto& router : context.m_routers) {
        std::println("router: | id: {}, model: {}, capacity: {}, price: {} |",
            router.m_id, router.m_model, router.m_capacity, router.m_price
        );
    }

    std::puts("\nChannel Table:");
    for (const auto& channel : context.m_channels) {
        std::println("channel: | id: {}, capacity: {}, price: {} |",
            channel.m_id, channel.m_capacity, channel.m_price
        );
    }

    std::println("\nPacket Size: {}", context.m_packetSize);
}

void isExistRename(QString& filename, const std::string_view& suffix) noexcept
{
    auto target = filename.toStdString();
    auto path   = std::filesystem::path(target);

    if (std::filesystem::exists(path)) {
        auto dotPosition = target.find_last_of('.');

        if (dotPosition != std::string::npos)
            filename = QString::fromStdString(target.substr(0, dotPosition) + suffix.data());
    }
}

} // namespace netd