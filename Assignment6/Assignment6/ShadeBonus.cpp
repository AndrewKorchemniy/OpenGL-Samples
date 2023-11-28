#include "ShadeBonus.h"

unsigned int shade_vao;
#define GLM_FORCE_RADIANS 

#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective

using namespace glm;

void createShade()
{
	float corner = 2.5f;
	GLfloat shade_vertice_values[] = {
		-corner, 0.0, corner, 1.0, // 0 - 3   (0)
		corner, 0.0, corner, 1.0,  // 4 - 7   (1)
		corner, 0.0, -corner, 1.0, // 8 - 11  (2)
		-corner, 0.0, -corner, 1.0,// 12 - 15 (3)
		0.0, 1.0, 0.0, 1.0,        // 16 - 19 (4)
	};

	GLfloat shade_vertices[] = {
		-corner, 0.0, corner, 1.0, // 0 - 3   (0)
		corner, 0.0, corner, 1.0,  // 4 - 7   (1)
		0.0, 1.0, 0.0, 1.0,        // 16 - 19 (4)

		corner, 0.0, corner, 1.0,  // 4 - 7   (1)
		corner, 0.0, -corner, 1.0, // 8 - 11  (2)
		0.0, 1.0, 0.0, 1.0,        // 16 - 19 (4)

		corner, 0.0, -corner, 1.0, // 8 - 11  (2)
		-corner, 0.0, -corner, 1.0,// 12 - 15 (3)
		0.0, 1.0, 0.0, 1.0,        // 16 - 19 (4)

		-corner, 0.0, corner, 1.0, // 0 - 3   (0)
		-corner, 0.0, -corner, 1.0,// 12 - 15 (3)
		0.0, 1.0, 0.0, 1.0,        // 16 - 19 (4)
	};

	vec3 shade_vertices_vecs[] = {
		vec3(shade_vertice_values[0], shade_vertice_values[1], shade_vertice_values[2]),    // (0)
		vec3(shade_vertice_values[4], shade_vertice_values[5], shade_vertice_values[6]),    // (1)
		vec3(shade_vertice_values[8], shade_vertice_values[9], shade_vertice_values[10]),   // (2)
		vec3(shade_vertice_values[12], shade_vertice_values[13], shade_vertice_values[14]), // (3)
		vec3(shade_vertice_values[16], shade_vertice_values[17], shade_vertice_values[18]), // (4)
	};

	vec3 side1 = normalize(cross(shade_vertices_vecs[4] - shade_vertices_vecs[0], shade_vertices_vecs[4] - shade_vertices_vecs[1]));
	vec3 side2 = normalize(cross(shade_vertices_vecs[4] - shade_vertices_vecs[1], shade_vertices_vecs[4] - shade_vertices_vecs[2]));
	vec3 side3 = normalize(cross(shade_vertices_vecs[4] - shade_vertices_vecs[2], shade_vertices_vecs[4] - shade_vertices_vecs[3]));
	vec3 side4 = normalize(cross(shade_vertices_vecs[4] - shade_vertices_vecs[3], shade_vertices_vecs[4] - shade_vertices_vecs[0]));

	vec3 per_vertex_nomals[] = {
		normalize(side1 + side4), // 0
		normalize(side1 + side2), // 1
		normalize(side2 + side3), // 2
		normalize(side3 + side4), // 3
		normalize(side1 + side2 + side3 + side4), // 4
	};

	GLfloat shade_normals[] = {
		//// side 1
		//side1.x, side1.y, side1.z,
		//side1.x, side1.y, side1.z,
		//side1.x, side1.y, side1.z,
		//// side 2
		//side2.x, side2.y, side2.z,
		//side2.x, side2.y, side2.z,
		//side2.x, side2.y, side2.z,
		//// side 3
		//side3.x, side3.y, side3.z,
		//side3.x, side3.y, side3.z,
		//side3.x, side3.y, side3.z,
		//// side 4
		//side4.x, side4.y, side4.z,
		//side4.x, side4.y, side4.z,
		//side4.x, side4.y, side4.z,
		
		// side 1
		per_vertex_nomals[0].x, per_vertex_nomals[0].y, per_vertex_nomals[0].z,
		per_vertex_nomals[1].x, per_vertex_nomals[1].y, per_vertex_nomals[1].z,
		per_vertex_nomals[4].x, per_vertex_nomals[4].y, per_vertex_nomals[4].z,
		// side 1
		per_vertex_nomals[1].x, per_vertex_nomals[1].y, per_vertex_nomals[1].z,
		per_vertex_nomals[2].x, per_vertex_nomals[2].y, per_vertex_nomals[2].z,
		per_vertex_nomals[4].x, per_vertex_nomals[4].y, per_vertex_nomals[4].z,
		// side 1
		per_vertex_nomals[2].x, per_vertex_nomals[2].y, per_vertex_nomals[2].z,
		per_vertex_nomals[3].x, per_vertex_nomals[3].y, per_vertex_nomals[3].z,
		per_vertex_nomals[4].x, per_vertex_nomals[4].y, per_vertex_nomals[4].z,
		// side 1
		per_vertex_nomals[0].x, per_vertex_nomals[0].y, per_vertex_nomals[0].z,
		per_vertex_nomals[3].x, per_vertex_nomals[3].y, per_vertex_nomals[3].z,
		per_vertex_nomals[4].x, per_vertex_nomals[4].y, per_vertex_nomals[4].z,

	};

	GLushort shade_indices[] = {
		0, 1, 2,
		3, 4, 5,
		6, 7, 8,
		9, 10, 11,
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
