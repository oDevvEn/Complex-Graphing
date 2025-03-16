#pragma once



#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>



class Grapher {
public:
	// Renderer
	GLFWwindow* window = NULL;
	GLuint WIDTH = 720, HEIGHT = 720;
	GLuint drawProgram, computeProgram;
	GLuint ssbo, vao;

	void InitWindow();
	void InitStuff();
	void GenerateShaders();
	std::string LoadShader(std::string path);
	GLuint CompileShader(GLenum type, const GLchar* code);
	GLuint CreateProgram(GLuint shaders[]);



	// Loop
	GLuint dataPoints = 64, drawingPoints = 64;
	GLfloat accuracy = 1.0f, zoom = 1.0f;
	GLfloat offset[2] = { 0.0f, 0.0f };
	double mousePos[2] = { 0.0f, 0.0f };
	bool mousePressed = false;
	void UpdateSize(GLuint newSize);
	void UpdateAccuracy(GLfloat newAccuracy);
	void Zoom(GLfloat offset);
	void Compute();
	void Draw();
	void Loop();



private:
	// Events
	static void GLFWErrorCallback(int error, const char* description);
	static void GLFWResizeCallback(GLFWwindow* window, int width, int height);
	static void GLFWScrollCallback(GLFWwindow* window, double xoffset, double yoffset);
	static void GLFWKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void GLFWButtonCallback(GLFWwindow* window, int button, int actions, int mods);
};