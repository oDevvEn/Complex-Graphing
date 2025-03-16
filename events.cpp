#include "main.hpp"



void Grapher::GLFWErrorCallback(int error, const char* description) {
    std::cout << "GLFW ERROR! int:" << error << "\n" << description << "\n";
}



void Grapher::GLFWResizeCallback(GLFWwindow* window, int width, int height) {
    Grapher* grapher = (Grapher*) glfwGetWindowUserPointer(window);
    if (grapher) {
        grapher->WIDTH = width, grapher->HEIGHT = height;
    }
    else {
        std::cout << "ERROR! Window User Pointer undefined\n";
    }

    glViewport(0, 0, width, height);
}



void Grapher::GLFWKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}