#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>

GLuint WIDTH = 1280, HEIGHT = 720;

static void glfwErrorCallback(int error, const char* description) {
    std::cout << "GLFW ERROR!\n" << description << "\n";
}
static void glfwResizeCallback(GLFWwindow* window, int width, int height) {
    WIDTH = width, HEIGHT = height;
    glViewport(0, 0, width, height);
}
static void glfwKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

int main() {
    // GLFW error callback
    glfwSetErrorCallback(glfwErrorCallback);

    // Initialise GLFW
    if (!glfwInit()) {
        std::cout << "ERROR! Failed to intialise GLFW\n";
        return -1;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    std::cout << "GLFW Initialised\n";

    // Create window
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Complex Graphing", NULL, NULL);
    if (!window) {
        std::cout << "ERROR! Failed to create window\n";
        glfwTerminate();
        return -1;
    }
    glfwSetKeyCallback(window, glfwKeyCallback);
    glfwMakeContextCurrent(window);
    std::cout << "Window created\n";

    // Initialise GLAD
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cout << "ERROR! Failed to initialise GLAD\n";
        return -1;
    }
    std::cout << "GLAD Initialised\n";

    // some minor config ig
    glfwSetWindowSizeCallback(window, glfwResizeCallback); // Viewport updating (no idea what it does)
    glfwSwapInterval(1); // vsync

    glfwResizeCallback(window, WIDTH, HEIGHT);
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        glClearColor(std::fmod(glfwGetTime(), 1), 0.f, 0.f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
    }

    // bye bye
    glfwTerminate();
    return 0;
}















































// 54.5 whole lines i can see on a 15" 1366x768 display!