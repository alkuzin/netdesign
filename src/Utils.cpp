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
#include <QtCore/QFile>
#include <QtXml/QtXml>
#include <filesystem>


namespace netd {

void convertToXML(const std::string_view& filename, const ProjectContext& context) noexcept
{
    // preventing overwriting of already existing project file
    std::string target = filename.data();
    auto path = std::filesystem::path(target);

    if (std::filesystem::exists(path)) {
        auto dotPosition = target.find_last_of('.');

        if (dotPosition != std::string::npos)
            target = target.substr(0, dotPosition) + "_copy.xml";
    }

    QFile file(target.c_str());

    if (!file.open(QIODevice::WriteOnly)) {
        QMessageBox::warning(
            nullptr,
            "File Error",
            "Error to open file: " + QString(target.c_str())
        );
        return;
    }

    QXmlStreamWriter xmlWriter(&file);
    xmlWriter.setAutoFormatting(true);
    xmlWriter.writeStartDocument();
    xmlWriter.writeStartElement("ProjectContext");

    // saving loadMatrix
    xmlWriter.writeStartElement("LoadMatrix");
    for (size_t i = 0; i < context.loadMatrix.size1(); ++i) {
        xmlWriter.writeStartElement("Row");
        for (size_t j = 0; j < context.loadMatrix.size2(); ++j) {
            xmlWriter.writeStartElement("Element");
            xmlWriter.writeCharacters(QString::number(context.loadMatrix(i, j)));
            xmlWriter.writeEndElement();
        }
        xmlWriter.writeEndElement();
    }
    xmlWriter.writeEndElement();

    // saving channels
    xmlWriter.writeStartElement("Channels");
    for (const auto& channel : context.channels) {
        xmlWriter.writeStartElement("Channel");
        xmlWriter.writeAttribute("ID", QString::number(channel.id));
        xmlWriter.writeTextElement("Capacity", QString::number(channel.capacity));
        xmlWriter.writeTextElement("Price", QString::number(channel.price));
        xmlWriter.writeEndElement();
    }
    xmlWriter.writeEndElement();

    // saving routers
    xmlWriter.writeStartElement("Routers");
    for (const auto& router : context.routers) {
        xmlWriter.writeStartElement("Router");
        xmlWriter.writeAttribute("ID", QString::number(router.id));
        xmlWriter.writeTextElement("Model", QString::fromStdString(router.model));
        xmlWriter.writeTextElement("Capacity", QString::number(router.capacity));
        xmlWriter.writeTextElement("Price", QString::number(router.price));
        xmlWriter.writeEndElement();
    }
    xmlWriter.writeEndElement();

    // saving nodes
    xmlWriter.writeStartElement("Nodes");
    for (const auto& node : context.nodes) {
        xmlWriter.writeStartElement("Node");
        xmlWriter.writeAttribute("ID", QString::number(node.id));
        xmlWriter.writeTextElement("Name", QString::fromStdString(node.name));
        xmlWriter.writeTextElement("X", QString::number(node.x));
        xmlWriter.writeTextElement("Y", QString::number(node.y));
        xmlWriter.writeEndElement();
    }
    xmlWriter.writeEndElement();

    // saving packet size
    xmlWriter.writeTextElement("PacketSize", QString::number(context.packetSize));
    xmlWriter.writeEndElement();
    xmlWriter.writeEndDocument();

    QFileInfo fileInfo(file);
    QMessageBox::information(
        nullptr,
        "Project",
        "Project saved successfully at " + fileInfo.absoluteFilePath()
    );

    file.close();
}

void convertToContext(const std::string_view& filename, ProjectContext& context) noexcept
{
    IGNORE_UNUSED(filename, context);
}

} // namespace netd