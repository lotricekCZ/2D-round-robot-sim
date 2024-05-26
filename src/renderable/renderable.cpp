/**
 * @author Jakub Ramašeuski (xramas01); 2024
 */
#include "renderable.hpp"

uint32_t renderable::ID_incrementor = 0;

renderable::renderable(/* args */)
{
	ID = ID_incrementor++;
	initializeOpenGLFunctions();
}

renderable::~renderable()
{
}

Vect2D renderable::distance(renderable &r)
{
	Segment intersector(this->center(), r.center());
	auto f1 = formula();
	auto f2 = r.formula();
	if (f1.index() == renderable::vehicle && f2.index() == renderable::vehicle)
	{
		if (!std::get<renderable::vehicle>(f2).inside(center()))
			return Vect2D(intersector.intersection(std::get<renderable::vehicle>(f1)).at(0), intersector.intersection(std::get<renderable::vehicle>(f2)).at(0));
	}
	else if (f1.index() == renderable::obstacle && f2.index() == renderable::obstacle)
	{

		for (auto edge1 : std::get<renderable::obstacle>(f1))
		{
			Points2D point1 = intersector.intersection(edge1);
			if (point1.size())
				for (auto edge2 : std::get<renderable::obstacle>(f2))
				{
					Points2D point2 = intersector.intersection(edge1);
					if (point2.size())
						return Vect2D(point1.at(0), point2.at(0));
				}
		}
	}
	else
	{
		std::vector<Segment> obstacle;
		Circle2D vehicle(0.1);
		if (f1.index() == renderable::obstacle)
		{
			obstacle = std::get<renderable::obstacle>(f1);
			vehicle = std::get<renderable::vehicle>(f2);
		}
		else
		{
			obstacle = std::get<renderable::obstacle>(f2);
			vehicle = std::get<renderable::vehicle>(f1);
		}

		for (auto edge : obstacle)
		{
			Points2D point = intersector.intersection(edge);
			if (point.size())
			{
				if (f1.index() == renderable::obstacle)
					return Vect2D(point.at(0), vehicle.center());
				return Vect2D(vehicle.center(), point.at(0));
			}
		}
	}
	return Vect2D(0, 0);
}

Vect2D renderable::distance(Point2D p)
{
	Segment intersector(this->center(), p);
	auto f1 = formula();
	if (f1.index() == renderable::vehicle)
	{
		if (!std::get<renderable::vehicle>(f1).inside(p))
			return Vect2D(p, intersector.intersection(std::get<renderable::vehicle>(f1)).at(0));
	}
	else
	{
		std::vector<Segment> obstacle = std::get<renderable::obstacle>(f1);
		for (auto edge : obstacle)
		{
			Points2D point = intersector.intersection(edge);
			if (point.size())
			{
				return Vect2D(p, point.at(0));
			}
		}
	}
	return Vect2D(0, 0);
}

Points2D renderable::intersection(renderable &r)
{
	auto f1 = formula();
	auto f2 = r.formula();
	if (f1.index() == renderable::vehicle && f2.index() == renderable::vehicle)
	{
		return std::get<renderable::vehicle>(f1).intersection(std::get<renderable::vehicle>(f2));
	}
	else if (f1.index() == renderable::obstacle && f2.index() == renderable::obstacle)
	{
		Points2D ret;
		for (auto edge1 : std::get<renderable::obstacle>(f1))
		{
			for (auto edge2 : std::get<renderable::obstacle>(f2)){
				auto point = edge1.intersection(edge2);
				ret.insert(ret.end(), point.begin(), point.end());
			}
		}
		return ret;
	}
	else
	{
		Points2D ret;
		std::vector<Segment> obstacle;
		Circle2D vehicle(0.1);
		if (f1.index() == renderable::obstacle)
		{
			obstacle = std::get<renderable::obstacle>(f1);
			vehicle = std::get<renderable::vehicle>(f2);
		}
		else
		{
			obstacle = std::get<renderable::obstacle>(f2);
			vehicle = std::get<renderable::vehicle>(f1);
		}

		for (auto edge : obstacle)
		{
			Points2D point = edge.intersection(vehicle);
			ret.insert(ret.end(), point.begin(), point.end());
		}
		return ret;
	}
	return {};
}

void renderable::reset(){
	ID_incrementor = 0;
}