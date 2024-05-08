/**
 * @author Jakub Ramašeuski (xramas01); 2024
*/

#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QFile>
#include <QString>
#include <QDebug>
#include <QTranslator>
#include <iostream>
#include <fstream> 
#include <sstream> 
#include <filesystem>
#include <memory>
#include "../renderable/renderer.hpp"

#ifndef SERIALIZER_HPP
#define SERIALIZER_HPP

class Serializer
{
private:
    std::filesystem::path file;
public:
    std::shared_ptr<renderer> renderer_ptr;
    Serializer(/* args */);
    ~Serializer();
    void read();
    void save();
};

#endif