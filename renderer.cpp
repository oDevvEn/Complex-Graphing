#include "main.hpp"



int Grapher::Init() {
    // GLFW error callback
    glfwSetErrorCallback(GLFWErrorCallback);

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
    window = glfwCreateWindow(WIDTH, HEIGHT, "Complex Graphing", NULL, NULL);
    if (!window) {
        std::cout << "ERROR! Failed to create window\n";
        glfwTerminate();
        return -1;
    }
    glfwSetKeyCallback(window, GLFWKeyCallback);
    glfwMakeContextCurrent(window);
    std::cout << "Window created\n";

    // Initialise GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "ERROR! Failed to initialise GLAD\n";
        return -1;
    }
    std::cout << "GLAD Initialised\n" << "Using: " << glGetString(GL_RENDERER) << "\n";

    // some minor config ig
    glfwSetWindowUserPointer(window, this);
    glfwSetWindowSizeCallback(window, GLFWResizeCallback); // Viewport updating (no idea what it does)
    glfwSwapInterval(1); // vsync
    GLFWResizeCallback(window, WIDTH, HEIGHT);

    // Successful!
    return 0;
}



void Grapher::Draw() {

}