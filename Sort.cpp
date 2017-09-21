#include <algorithm>
#include "include/Sort.h"
#include "include/Shapes.h"

bool compactnessLess(Shape *shape1, Shape *shape2)
{
	double compactness1 = shape1->area() / shape1->perimeter();
	double compactness2 = shape2->area() / shape2->perimeter();
	return compactness1 < compactness2;
}

Shape* theLargestArea(const std::list<Shape *> * shapeList){
    Shape *largestShape = nullptr;
    double largestArea = 0;

    for (Shape *shapePoint: *shapeList)
        if(shapePoint->area() >= largestArea){
            largestArea = shapePoint->area();
            largestShape = shapePoint;
        }

    return largestShape;
}

void convertListToVector(std::list<Shape *> * shapeList, std::vector<Shape *> & shapes)
{
	shapes.clear();
	for(Shape *shape : *shapeList)
	{
		shapes.push_back(shape);
	}
}

void convertVectorToList(std::vector<Shape *> & shapes, std::list<Shape *> * shapeList)
{
	shapeList->clear();
	for(Shape *shape : shapes)
	{
		shapeList->push_back(shape);
	}
}

void Sort::sortByIncreasingPerimeter(std::list<Shape *> * shapeList)
{
	Sort::sortByDecreasingPerimeter(shapeList);
	shapeList->reverse();
}

void Sort::sortByDecreasingPerimeter(std::list<Shape *> * shapeList)
{
	std::vector<Shape *> shapes;
	convertListToVector(shapeList, shapes);
	::sortByDecreasingPerimeter(shapes);
	convertVectorToList(shapes, shapeList);
}

void Sort::sortByIncreasingArea(std::list<Shape *> * shapeList)
{
	Shape *largestShape;
	std::list<Shape *> * tmpShapeList = new std::list<Shape *>();

	while(!shapeList->empty())
	{
		largestShape = theLargestArea(shapeList);
		tmpShapeList->push_back(largestShape);
		shapeList->remove(largestShape);
	}

	for(std::list<Shape *>::iterator it = tmpShapeList->begin(); it != tmpShapeList->end(); it++)
	{
		shapeList->push_front(*it);
	}
}

void Sort::sortByDecreasingArea(std::list<Shape *> * shapeList)
{
	Sort::sortByIncreasingArea(shapeList);
	shapeList->reverse();
}
  
void Sort::sortByIncreasingCompactness(std::list<Shape *> * shapeList)
{
	std::vector<Shape *> shapes;
	convertListToVector(shapeList, shapes);
	std::sort(shapes.begin(), shapes.end(), compactnessLess);
	convertVectorToList(shapes, shapeList);
}