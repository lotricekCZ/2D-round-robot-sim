/**
 * @author Jakub Ramašeuski (xramas01); 2024
 */

#include "serializer.hpp"

serializer::serializer(/* args */) : file("test.json")
{
}

serializer::~serializer()
{
}

void serializer::read()
{
    std::ifstream handler(file);
    std::stringstream buffer;
    buffer << handler.rdbuf();
    handler.close();
    QJsonDocument doc = QJsonDocument::fromJson(QByteArray::fromStdString(buffer.str()));
    QJsonArray jsonArray = doc.array();
    for (auto v : jsonArray)
    {
        QJsonObject element = v.toObject();
        std::cout << (element["type"]).toString().toStdString() << std::endl;
        std::cout << (element["rotation"]).toInt() << std::endl;
        std::cout << (element["coordinates"].toArray()[0]).toDouble() << std::endl;
        std::cout << (element["coordinates"].toArray()[1]).toDouble() << std::endl;
    }
}