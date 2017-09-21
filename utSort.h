#ifndef EXP_H
#define EXP_H
#include "include/Shapes.h"
#include "include/Media.h"
#include "include/Sort.h"

Shape *createTriangle()
{
	vertex v1, v2, v3;
	v1.x = 0; v1.y = 0;
	v2.x = 3; v2.y = 0;
	v3.x = 0; v3.y = 4;
	return new Triangle(v1, v2, v3, "triangle");
}

std::list<Shape *> *createShapeList()
{
	Shape *rectangle = new Rectangle(0, 0, 1, 1, "rectangle"); // perimeter: 4, area: 1, compactness: 0.25
	Shape *circle = new Circle(0, 0, 1, "circle"); // perimeter: 2 * M_PI, area: M_PI, compactness: 0.5
	Shape *triangle = createTriangle(); // perimeter: 12, area: 6, compactness: 0.5

	std::list<Shape *> *shapeList = new std::list<Shape *>();
	shapeList->push_back(rectangle);
	shapeList->push_back(circle);
	shapeList->push_back(triangle);
	return shapeList;
}

TEST (Sort, sortByIncreasingPerimeter) {
	std::list<Shape *> *shapeList = createShapeList();
	Sort::sortByIncreasingPerimeter(shapeList);

	//test
	Shape *shape = shapeList->front();
	ASSERT_EQ("rectangle", shape->getShapeName());
	shapeList->pop_front();

	shape = shapeList->front();
	ASSERT_EQ("circle", shape->getShapeName());
	shapeList->pop_front();

	shape = shapeList->front();
	ASSERT_EQ("triangle", shape->getShapeName());
	shapeList->pop_front();
}

TEST (Sort, sortByDecreasingPerimeter) {
	std::list<Shape *> *shapeList = createShapeList();
	Sort::sortByDecreasingPerimeter(shapeList);

	//test
	Shape *shape = shapeList->front();
	ASSERT_EQ("triangle", shape->getShapeName());
	shapeList->pop_front();

	shape = shapeList->front();
	ASSERT_EQ("circle", shape->getShapeName());
	shapeList->pop_front();

	shape = shapeList->front();
	ASSERT_EQ("rectangle", shape->getShapeName());
	shapeList->pop_front();
}

TEST (Sort, sortByIncreasingArea) {
	std::list<Shape *> *shapeList = createShapeList();
	Sort::sortByIncreasingArea(shapeList);

	//test
	Shape *shape = shapeList->front();
	ASSERT_EQ("rectangle", shape->getShapeName());
	shapeList->pop_front();

	shape = shapeList->front();
	ASSERT_EQ("circle", shape->getShapeName());
	shapeList->pop_front();

	shape = shapeList->front();
	ASSERT_EQ("triangle", shape->getShapeName());
	shapeList->pop_front();
}

TEST (Sort, sortByDecreasingArea) {
	std::list<Shape *> *shapeList = createShapeList();
	Sort::sortByDecreasingArea(shapeList);

	//test
	Shape *shape = shapeList->front();
	ASSERT_EQ("triangle", shape->getShapeName());
	shapeList->pop_front();

	shape = shapeList->front();
	ASSERT_EQ("circle", shape->getShapeName());
	shapeList->pop_front();

	shape = shapeList->front();
	ASSERT_EQ("rectangle", shape->getShapeName());
	shapeList->pop_front();
}

TEST (Sort, sortByIncreasingCompactness) {
	std::list<Shape *> *shapeList = createShapeList();
	Sort::sortByIncreasingCompactness(shapeList);

	//test
	Shape *shape = shapeList->front();
	ASSERT_EQ("rectangle", shape->getShapeName());
	shapeList->pop_front();

	shape = shapeList->front();
	ASSERT_EQ("circle", shape->getShapeName());
	shapeList->pop_front();

	shape = shapeList->front();
	ASSERT_EQ("triangle", shape->getShapeName());
	shapeList->pop_front();
}

#endif
