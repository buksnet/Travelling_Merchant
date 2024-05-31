#pragma once
#define GLFW_INCLUDE_NONE
#define _USE_MATH_DEFINES
#include "graph.h"
#include <list>
#include <math.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#define GLT_IMPLEMENTATION
#include "gltext.h"


class UI
{
	graph* graph_ptr;
	list <GLTtext*> texts;
	GLFWwindow* root;
public:
	UI();
	~UI();
	void link_graph(graph* data);
	void draw();
	void draw_vertex(float x, float y);
	void draw_edge(float x1, float y1, float x2, float y2);
	void put_name(string& name, GLfloat x, GLfloat y);
	void clear_names();
	static void keyCallBack(GLFWwindow* root, int key, int scancode, int action, int mode);
	static void error(int code, const char* desc);
};
