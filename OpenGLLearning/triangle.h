#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <glad\glad.h>
#include <glm\glm.hpp>

class Triangle
{
public:
	// a-top b-bottom left c-bottom right
	Triangle(glm::vec2 a, glm::vec2 b, glm::vec2 c);
	~Triangle();

	void display(GLenum mode=GL_FILL);
	glm::vec2 getPoint(int num);

private:
	unsigned int VAO;
	unsigned int VBO;

protected:
	glm::vec2 vertices[3];

};

#endif // !TRIANGLE_H
