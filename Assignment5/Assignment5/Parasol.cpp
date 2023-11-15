#include "Parasol.h"
#define GLM_FORCE_RADIANS 
#include <glm/gtc/matrix_transform.hpp> 
#include <iostream>

using namespace std;
using namespace glm;

unsigned int parasol_vao;

void createParasol()
{
	float radius = 2.0f;
	GLfloat parasol_vertices[] = {
		0, 0.5, 0, 1.0,
		radius * cos(radians(0.0f)), 0.0, radius * sin(radians(0.0f)), 1.0,
		radius * cos(radians(60.0f)), 0.0, radius * sin(radians(60.0f)), 1.0,

		0, 0.5, 0, 1.0,
		radius* cos(radians(60.0f)), 0.0, radius* sin(radians(60.0f)), 1.0,
		radius * cos(radians(120.0f)), 0.0f, radius * sin(radians(120.0f)), 1.0,

		0, 0.5, 0, 1.0,
		radius* cos(radians(120.0f)), 0.0f, radius* sin(radians(120.0f)), 1.0,
		radius * cos(radians(180.0f)), 0.0f, radius * sin(radians(180.0f)), 1.0,

		0, 0.5, 0, 1.0,
		radius* cos(radians(180.0f)), 0.0f, radius* sin(radians(180.0f)), 1.0,
		radius * cos(radians(240.0f)), 0.0f, radius * sin(radians(240.0f)), 1.0,

		0, 0.5, 0, 1.0,
		radius* cos(radians(240.0f)), 0.0f, radius* sin(radians(240.0f)), 1.0,
		radius * cos(radians(300.0f)), 0.0f, radius * sin(radians(300.0f)), 1.0,

		0, 0.5, 0, 1.0,
		radius* cos(radians(300.0f)), 0.0f, radius* sin(radians(300.0f)), 1.0,
		radius* cos(radians(0.0f)), 0.0, radius* sin(radians(0.0f)), 1.0,
	};

	GLfloat parasol_colors[][4] = {
		{ 1.0, 0.0, 1.0, 1.0 }, // triangle 1
		{ 1.0, 0.0, 1.0, 1.0 },
		{ 1.0, 0.0, 1.0, 1.0 },
		{ 1.0, 0.0, 0.0, 1.0 }, // triangle 6
		{ 1.0, 0.0, 0.0, 1.0 },
		{ 1.0, 0.0, 0.0, 1.0 },
		{ 1.0, 1.0, 0.0, 1.0 }, // triangle 5
		{ 1.0, 1.0, 0.0, 1.0 },
		{ 1.0, 1.0, 0.0, 1.0 },
		{ 0.0, 1.0, 0.0, 1.0 }, // triangle 4
		{ 0.0, 1.0, 0.0, 1.0 },
		{ 0.0, 1.0, 0.0, 1.0 },
		{ 0.0, 0.0, 1.0, 1.0 }, // triangle 3
		{ 0.0, 0.0, 1.0, 1.0 },
		{ 0.0, 0.0, 1.0, 1.0 },
		{ 0.0, 1.0, 1.0, 1.0 }, // triangle 2
		{ 0.0, 1.0, 1.0, 1.0 },
		{ 0.0, 1.0, 1.0, 1.0 },
	};

	glGenVertexArrays(1, &parasol_vao);
	glBindVertexArray(parasol_vao);

	unsigned int handle[2];
	glGenBuffers(2, handle);

	glBindBuffer(GL_ARRAY_BUFFER, handle[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(parasol_vertices), parasol_vertices, GL_STATIC_DRAW);
	glVertexAttribPointer((GLuint)0, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, handle[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(parasol_colors), parasol_colors, GL_STATIC_DRAW);
	glVertexAttribPointer((GLuint)1, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);
}

void drawParasol() {
	glBindVertexArray(parasol_vao);
	glDrawArrays(GL_TRIANGLES, 0, 18);
}
