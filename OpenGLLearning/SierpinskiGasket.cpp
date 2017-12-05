#include "SierpinskiGasket.h"
#include <time.h>

SierpinskiGasket::SierpinskiGasket(Triangle & base)
{
	glm::vec2 vertices[] = {
		base.getPoint(0),
		base.getPoint(1),
		base.getPoint(2)
	};
	points[0] = glm::vec2(-vertices[1]) / glm::vec2(4.0f, 2.0f);

	srand((unsigned int)time(NULL));

	for (int i = 1; i < numPoints; ++i)
	{
		int j = rand() % 3;
		points[i] = ( points[i - 1] + vertices[j] ) / 2.0f;
	}

	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

SierpinskiGasket::~SierpinskiGasket()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}

void SierpinskiGasket::display()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, numPoints);
	glBindVertexArray(0);
}
