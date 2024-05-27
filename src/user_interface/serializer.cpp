/**
 * @author Jakub Ramašeuski (xramas01); 2024
 */

#include "serializer.hpp"

Serializer::Serializer(/* args */) : file("test.json")
{
}

Serializer::~Serializer()
{
}

void Serializer::read()
{
	QByteArray ba;
	QString data;
	if (file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		ba = file.readAll();
		file.close();
	}
	QJsonDocument doc = QJsonDocument::fromJson(ba);
	QJsonArray jsonArray = doc.array();
	for (auto v : jsonArray)
	{
		QJsonObject element = v.toObject();
		std::string type = element["type"].toString().toStdString();
		if (type == "obstacle")
		{
			renderer_ptr->add(std::make_shared<obstacle>());
		}
		else if (type == "vehicle")
		{
			renderer_ptr->add(std::make_shared<vehicle>());
		}
		else if (type == "bot")
		{
			renderer_ptr->add(std::make_shared<bot>());
			renderer_ptr->minds.push_back(std::make_shared<ai>());
			renderer_ptr->minds.back()->attach(renderer_ptr->objects.back());
		}
		else if (type == "player")
		{
			renderer_ptr->add(std::make_shared<player>());
		}
		else
		{
		}
		renderer_ptr->objects.back()->rotate((element["rotation"]).toDouble() / (360.0f));
		renderer_ptr->objects.back()->place((element["coordinates"].toArray()[0]).toDouble(), (element["coordinates"].toArray()[1]).toDouble());
	}
}

void Serializer::save()
{
	QJsonArray save_array;
	for (auto object : renderer_ptr->objects)
	{
		auto coordinates = object->center().point();
		QJsonArray result;
		std::copy(coordinates.begin(), coordinates.end(), std::back_inserter(result));
		auto data = QJsonObject(
			{qMakePair(QString("type"), QJsonValue(object->info().c_str())),
			 qMakePair(QString("coordinates"), QJsonArray(result)),
			 qMakePair(QString("rotation"), QJsonValue(object->rotation() * 360.0f))});

		save_array.push_back(QJsonValue(data));
	}
	QJsonDocument document(save_array);
	QByteArray bytes = document.toJson(QJsonDocument::Indented);
	file.open(QIODevice::WriteOnly);
	file.write(bytes);
	file.close();
}

void Serializer::select(std::string path){
	file.setFileName(QString::fromStdString(path));
}