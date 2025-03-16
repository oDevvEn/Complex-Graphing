#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

class Grapher {
	public:
	GLFWwindow* window;
	GLuint WIDTH = 1280, HEIGHT = 720;
	int Init();
	void Draw();
	void Loop();

	private:
	static void GLFWErrorCallback(int error, const char* description);
	static void GLFWResizeCallback(GLFWwindow* window, int width, int height);
	static void GLFWKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
};