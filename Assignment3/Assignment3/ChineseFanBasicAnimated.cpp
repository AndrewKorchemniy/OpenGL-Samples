#include "ChineseFanBasic.h"
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <stdio.h>
#include <stdlib.h>

#define GLM_FORCE_RADIANS 

#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective

using namespace glm;

GLuint  vao;
GLuint  vbo[2];
GLuint  ebo;
GLuint v, f;
GLboolean show_line = false;
GLboolean vertex_update = false;
GLboolean quarter_scale = false;
GLboolean multiple_fans = false;
GLboolean rotation_transform = false;
double radDist = 0.6;
double degDist = 60;
float rotation_degree = 0;
float axis_rotation_degree = 0;

mat4 scale_matrix(1.0f);
mat4 trans_matrix(1.0f);
mat4 rotate_matrix(1.0f);
mat4 axis_rotate_matrix(1.0f);
GLuint model_loc(1.0f);
mat4 model_matrix(1.0f);

char* ReadFile(const char* filename);
GLuint initShaders(char* v_shader, char* f_shader);
void init();
void display(void);

/************************************************/

char* ReadFile(const char* filename) {

	FILE* infile;
#ifdef WIN32
	fopen_s(&infile, filename, "rb");
#else
	infile = fopen(filename, "rb");
#endif

	if (!infile) {
		printf("Unable to open file %s\n", filename);
		return NULL;
	}

	fseek(infile, 0, SEEK_END);
	int len = ftell(infile);
	fseek(infile, 0, SEEK_SET);
	char* source = (char*)malloc(len + 1);
	fread(source, 1, len, infile);
	fclose(infile);
	source[len] = 0;
	return (source);

}

/*************************************************************/

GLuint initShaders(const char* v_shader, const char* f_shader) {

	GLuint p = glCreateProgram();

	v = glCreateShader(GL_VERTEX_SHADER);
	f = glCreateShader(GL_FRAGMENT_SHADER);

	const char* vs = ReadFile(v_shader);
	const char* fs = ReadFile(f_shader);

	glShaderSource(v, 1, &vs, NULL);
	glShaderSource(f, 1, &fs, NULL);

	free((char*)vs);
	free((char*)fs);

	glCompileShader(v);

	GLint compiled;

	glGetShaderiv(v, GL_COMPILE_STATUS, &compiled);
	if (!compiled) {
		GLsizei len;
		glGetShaderiv(v, GL_INFO_LOG_LENGTH, &len);
		char* log = (char*)malloc(len + 1);
		glGetShaderInfoLog(v, len, &len, log);
		printf("Vertex Shader compilation failed: %s\n", log);
		free(log);
	}

	glCompileShader(f);
	glGetShaderiv(f, GL_COMPILE_STATUS, &compiled);

	if (!compiled) {

		GLsizei len;
		glGetShaderiv(f, GL_INFO_LOG_LENGTH, &len);
		char* log = (char*)malloc(len + 1);
		glGetShaderInfoLog(f, len, &len, log);
		printf("Vertex Shader compilation failed: %s\n", log);
		free(log);
	}

	glAttachShader(p, v);
	glAttachShader(p, f);
	glLinkProgram(p);
	GLint linked;

	glGetProgramiv(p, GL_LINK_STATUS, &linked);

	if (!linked) {

		GLsizei len;
		glGetProgramiv(p, GL_INFO_LOG_LENGTH, &len);
		char* log = (char*)malloc(len + 1);
		glGetProgramInfoLog(p, len, &len, log);
		printf("Shader linking failed: %s\n", log);
		free(log);
	}

	glUseProgram(p);
	return p;
}



/*******************************************************/
void init() {

	GLuint program = initShaders("ChineseFan.vs", "ChineseFan.fs");

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(2, vbo);  // you need to have two buffer objects if color is added

	// For the 1st attribute - vertex positions

	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);

	// For the 2nd attribute - color

	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(colors), colors);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	// Combined model transformation uniform
	model_loc = glGetUniformLocation(program, "model_matrix");
	model_matrix = axis_rotate_matrix * trans_matrix * scale_matrix;
	glUniformMatrix4fv(model_loc, 1, GL_FALSE, (GLfloat*)&model_matrix[0]);
}
/*******************************************************/
void Keyboard(unsigned char key, int x, int y) {

	switch (key) {

	case 'q':case 'Q':
		exit(EXIT_SUCCESS);
		break;
	case 'w': case 'W':
		show_line = !show_line;
		break;
	case 's': case 'S':
		quarter_scale = !quarter_scale;
		break;
	case 'm': case 'M':
		multiple_fans = !multiple_fans;
		break;
	case 'r': case 'R':
		rotation_transform = !rotation_transform;
		break;
	case 'u': case 'U':
		vertex_update = !vertex_update;
		break;
	}
	glutPostRedisplay();
}

/**********************************************************/

void drawFan(double v1, double v2, double v3) {
	if (show_line)
		glPolygonMode(GL_FRONT, GL_LINE);
	else
		glPolygonMode(GL_FRONT, GL_FILL);

	trans_matrix = translate(mat4(1.0), vec3(v1, v2, v3));
	model_matrix = trans_matrix * axis_rotate_matrix * scale_matrix;
	glUniformMatrix4fv(model_loc, 1, GL_FALSE, (GLfloat*)&model_matrix[0]);

	glDrawArrays(GL_TRIANGLES, 0, 24);
	glDrawArrays(GL_POINTS, 0, 24);
	glPolygonMode(GL_FRONT, GL_LINE);
	glDrawArrays(GL_TRIANGLES, 0, 24);
}

/**********************************************************/

void updateRotation(int n) {
	if (rotation_transform) {
		rotation_degree += 5;
		rotate_matrix = glm::rotate(mat4(1.0f), radians((float)rotation_degree), vec3(0.0, 0.0, 1.0f));
		glutPostRedisplay();
	}
	glutTimerFunc(100, updateRotation, 1);
}

/**********************************************************/

void updateAxisRotation(int n) {
	if (rotation_transform) {
		axis_rotation_degree += 5;
		axis_rotate_matrix = glm::rotate(mat4(1.0f), radians((float)axis_rotation_degree), vec3(0.0, 0.0, 1.0f));
		glutPostRedisplay();
	}
	glutTimerFunc(500, updateAxisRotation, 1);
}

/**********************************************************/

void updateFolding(int n) {
	vertex_update = !vertex_update;
	glutTimerFunc(500, updateFolding, 1);
}

/**********************************************************/

void display(void) {
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	glLineWidth(5.0);
	glBindVertexArray(vao);

	if (quarter_scale) {
        glPointSize(10.0);
		scale_matrix = scale(mat4(1.0f), vec3(.25, .25, 1.0));
	}
	else {
        glPointSize(20.0);
		scale_matrix = scale(mat4(1.0f), vec3(1, 1, 1.0));
	}

	if (vertex_update) {
		glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices_update), vertices_update);
	}
	else {
		glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
	}

	drawFan(0, 0, 0);
	if (quarter_scale && multiple_fans) {
		drawFan(radDist * cos(radians(degDist * 0 + rotation_degree)), radDist * sin(radians(degDist * 0 + rotation_degree)), 0.0);
		drawFan(radDist * cos(radians(degDist * 1 + rotation_degree)), radDist * sin(radians(degDist * 1 + rotation_degree)), 0.0);
		drawFan(radDist * cos(radians(degDist * 2 + rotation_degree)), radDist * sin(radians(degDist * 2 + rotation_degree)), 0.0);
		drawFan(radDist * cos(radians(degDist * 3 + rotation_degree)), radDist * sin(radians(degDist * 3 + rotation_degree)), 0.0);
		drawFan(radDist * cos(radians(degDist * 4 + rotation_degree)), radDist * sin(radians(degDist * 4 + rotation_degree)), 0.0);
		drawFan(radDist * cos(radians(degDist * 5 + rotation_degree)), radDist * sin(radians(degDist * 5 + rotation_degree)), 0.0);
	}
	glFlush();
}

/*******************************************************/

int main(int argc, char** argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA);
	glutInitWindowSize(512, 512);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Chinese fan");

	if (glewInit()) {
		printf("%s\n", "Unable to initialize GLEW ...");
	}

	init();
	printf("%s\n", glGetString(GL_VERSION));
	glutDisplayFunc(display);
	glutKeyboardFunc(Keyboard);
	glutTimerFunc(100, updateRotation, 1);
	glutTimerFunc(500, updateAxisRotation, 1);
	glutTimerFunc(500, updateFolding, 1);
	glutMainLoop();

	return 0;

}

/*******************************************************/