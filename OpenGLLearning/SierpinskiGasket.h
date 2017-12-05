#ifndef SIERPINSKIGASKET_H
#define SIERPINSKIGASKET_H

#include "triangle.h"
class SierpinskiGasket
{
public:
	SierpinskiGasket(Triangle &base);
	~SierpinskiGasket();

	void display();
private:
	static const unsigned int numPoints = 5000;
	glm::vec2 points[numPoints];
	unsigned int VAO;
	unsigned int VBO;
};

#endif // !SIERPINSKIGASKET_H

