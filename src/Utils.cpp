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

#include <QtWidgets/QMessageBox>
#include <NetDesign/Utils.hpp>
#include <filesystem>
#include <fstream>
#include <print>


namespace netd {

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

QString getItem(const QTableWidget *table, size_t row, size_t column) noexcept
{
    auto item = table->item(
        static_cast<int32_t>(row),
        static_cast<int32_t>(column)
    );

    return item->text();
}

void printProjectContext(void) noexcept
{
    const auto& context = projectContext;
    std::println("Node Count: {}\nNodes:", context.nodes.size());

    for (const auto& node : context.nodes) {
        std::println("node: | id: {}, name: {}, x: {}, y: {} |",
            node.id, node.name, node.x, node.y
        );
    }

    std::puts("\nLoad Matrix:");
    for (size_t i = 0; i < context.loadMatrix.size1(); i++) {
        std::putchar('|');
        for (size_t j = 0; j < context.loadMatrix.size2(); j++)
            std::print(" {:>3}", context.loadMatrix(i, j));
        std::puts("   |");
    }
    std::putchar('\n');

    std::puts("\nRouter Table:");
    for (const auto& router : context.routers) {
        std::println("router: | id: {}, model: {}, capacity: {}, price: {} |",
            router.id, router.model, router.capacity, router.price
        );
    }

    std::puts("\nChannel Table:");
    for (const auto& channel : context.channels) {
        std::println("channel: | id: {}, capacity: {}, price: {} |",
            channel.id, channel.capacity, channel.price
        );
    }

    std::println("\nPacket Size: {}", context.packetSize);
}

void saveProject(const std::string_view& filename) noexcept
{
    std::ofstream fout(filename.data(), std::ios::out);

    if (!fout.is_open()) {
        QMessageBox::warning(nullptr, "Error", "Could not create project file.");
        return;
    }

    const auto& context = projectContext;

    // saving nodes
    fout << "# Nodes\n";
    fout << "count," << context.nodes.size() << "\n";
    fout << "id,name,x,y\n";

    for (const auto& node : context.nodes) {
        fout << node.id << ",";
        fout << node.name << ",";
        fout << node.x << ",";
        fout << node.y << "\n";
    }
    fout << "\n";

    // saving load matrix
    auto matrixCount = context.loadMatrix.size1();

    fout << "# Load Matrix\n";
    fout << "count," << matrixCount << "\n";

    for (std::size_t i = 0; i < matrixCount; i++) {
        for (std::size_t j = 0; j < matrixCount; j++)
            fout << context.loadMatrix(i, j) << ",";
        fout << "\n";
    }
    fout << "\n";

    // saving routers
    fout << "# Routers\n";
    fout << "count," << context.routers.size() << "\n";
    fout << "id,model,capacity,price\n";

    for (const auto& router : context.routers) {
        fout << router.id << ",";
        fout << router.model << ",";
        fout << router.capacity << ",";
        fout << router.price << "\n";
    }
    fout << "\n";

    // saving channels
    fout << "# Channels\n";
    fout << "count," << context.channels.size() << "\n";
    fout << "id,capacity,price\n";

    for (const auto& channel : context.channels) {
        fout << channel.id << ",";
        fout << channel.capacity << ",";
        fout << channel.price << "\n";
    }

    fout << "\n# Packet Size\n";
    fout << "size," << context.packetSize << "\n";
    fout.close();
}

} // namespace netd