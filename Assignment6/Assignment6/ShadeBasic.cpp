#include "ShadeBasic.h"

unsigned int shade_vao;

void createShade()
{
	float corner = 2.5f;
	GLfloat shade_vertices[] = {
		-corner, 0.0, corner, 1.0,
		corner, 0.0, corner, 1.0,
		corner, 0.0, -corner, 1.0,
		-corner, 0.0, -corner, 1.0,
		0.0, 1.0, 0.0, 1.0,
	};

	GLshort shade_normals[] = {
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
	};

	GLushort shade_indices[] = {
		0, 1, 4,
		1, 2, 4,
		2, 3, 4,
		0, 3, 4,
	};

	glGenVertexArrays(1, &shade_vao);
	glBindVertexArray(shade_vao);

	unsigned int handle[3];
	glGenBuffers(3, handle);

	glBindBuffer(GL_ARRAY_BUFFER, handle[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(shade_vertices), shade_vertices, GL_STATIC_DRAW);
	glVertexAttribPointer((GLuint)0, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);  // Vertex position

	glBindBuffer(GL_ARRAY_BUFFER, handle[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(shade_normals), shade_normals, GL_STATIC_DRAW);
	glVertexAttribPointer((GLuint)1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);  // Vertex normal

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, handle[2]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(shade_indices), shade_indices, GL_STATIC_DRAW);

	glBindVertexArray(0);
}

void drawShade() {
	glBindVertexArray(shade_vao);
	glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_SHORT, 0);
}
