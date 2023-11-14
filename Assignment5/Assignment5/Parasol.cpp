#include "Parasol.h"
#define GLM_FORCE_RADIANS 
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp> 

using namespace glm;

unsigned int parasol_vao;

void createParasol()
{
	float radius = 2.0f;
	//GLfloat parasol_vertices[] = {
	//	0, 0.5, 0, // O
	//	radius * cos(radians(0.0f)), 0.0f, radius * sin(radians(0.0f)), // A
	//	radius * cos(radians(60.0f)), 0.0f, radius * sin(radians(60.0f)), // B
	//	radius * cos(radians(120.0f)), 0.0f, radius * sin(radians(120.0f)), // C
	//	radius * cos(radians(180.0f)), 0.0f, radius * sin(radians(180.0f)), // D
	//	radius * cos(radians(240.0f)), 0.0f, radius * sin(radians(240.0f)), // E
	//	radius * cos(radians(300.0f)), 0.0f, radius * sin(radians(300.0f)), // F
	//};
	GLfloat parasol_vertices[] = {
		0, 0.5f, 0, // O
		radius * cos(radians(0.0f)), radius * sin(radians(0.0f)), 0.0f, // A
		radius * cos(radians(60.0f)), radius * sin(radians(60.0f)), 0.0f, // B
		radius * cos(radians(120.0f)), radius * sin(radians(120.0f)), 0.0f, // C
		radius * cos(radians(180.0f)), radius * sin(radians(180.0f)), 0.0f, // D
		radius * cos(radians(240.0f)), radius * sin(radians(240.0f)), 0.0f, // E
		radius * cos(radians(300.0f)), radius * sin(radians(300.0f)), 0.0f, // F
	};

	GLfloat parasol_colors[] = {
		1.0, 0.0, 1.0, 1.0, // t1
		1.0, 0.0, 1.0, 1.0,
		1.0, 0.0, 1.0, 1.0,
		0.0, 1.0, 1.0, 1.0, // t2
		0.0, 1.0, 1.0, 1.0,
		0.0, 1.0, 1.0, 1.0,
		0.0, 0.0, 1.0, 1.0, // t3
		0.0, 0.0, 1.0, 1.0,
		0.0, 0.0, 1.0, 1.0,
		0.0, 1.0, 0.0, 1.0, // t4
		0.0, 1.0, 0.0, 1.0,
		0.0, 1.0, 0.0, 1.0,
		1.0, 1.0, 0.0, 1.0, // t5
		1.0, 1.0, 0.0, 1.0,
		1.0, 1.0, 0.0, 1.0,
		1.0, 0.0, 0.0, 1.0, // t6
		1.0, 0.0, 0.0, 1.0,
		1.0, 0.0, 0.0, 1.0,
	};

	GLushort parasol_indices[] = {
		0, 1, 2,
		0, 2, 3,
		0, 3, 4,
		0, 4, 5,
		0, 5, 6,
		0, 1, 6,
	};

	glGenVertexArrays(1, &parasol_vao);
	glBindVertexArray(parasol_vao);

	unsigned int handle[3];
	glGenBuffers(3, handle);

	glBindBuffer(GL_ARRAY_BUFFER, handle[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(parasol_vertices), parasol_vertices, GL_STATIC_DRAW);
	glVertexAttribPointer((GLuint)0, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);  // Vertex position

	glBindBuffer(GL_ARRAY_BUFFER, handle[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(parasol_colors), parasol_colors, GL_STATIC_DRAW);
	glVertexAttribPointer((GLuint)1, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);  // Vertex normal

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, handle[2]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(parasol_indices), parasol_indices, GL_STATIC_DRAW);

	glBindVertexArray(0);

}

void drawParasol() {
	glBindVertexArray(parasol_vao);
	glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_SHORT, 0);
}
