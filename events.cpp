#include "main.hpp"



void Grapher::GLFWErrorCallback(int error, const char* description) {
    std::cout << "GLFW ERROR! int:" << error << "\n" << description << "\n";
    exit(-1);
}



void Grapher::GLFWResizeCallback(GLFWwindow* window, int width, int height) {
    Grapher* grapher = (Grapher*) glfwGetWindowUserPointer(window);
    if (grapher) {
        grapher->WIDTH = width, grapher->HEIGHT = height;
    }
    else {
        std::cout << "ERROR! Window User Pointer undefined\n";
        exit(-1);
    }

    glViewport(0, 0, width, height);
}


void Grapher::GLFWScrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
    Grapher* grapher = (Grapher*)glfwGetWindowUserPointer(window);
    if (!grapher) {
        std::cout << "ERROR! Window User Pointer undefined\n";
        exit(-1);
    }

    grapher->Zoom(yoffset);
}

void Grapher::GLFWButtonCallback(GLFWwindow* window, int button, int action, int mods) {
    Grapher* grapher = (Grapher*)glfwGetWindowUserPointer(window);
    if (!grapher) {
        std::cout << "ERROR! Window User Pointer undefined\n";
        exit(-1);
    }

    if (button == GLFW_MOUSE_BUTTON_LEFT) {
        grapher->mousePressed = action == GLFW_PRESS;
        glfwGetCursorPos(window, &grapher->mousePos[0], &grapher->mousePos[1]);
        grapher->mousePos[0] = grapher->mousePos[0] * 2.0 / grapher->WIDTH - 1.0;
        grapher->mousePos[1] = -grapher->mousePos[1] * 2.0 / grapher->HEIGHT + 1.0;
    }
}



void Grapher::GLFWKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    Grapher* grapher = (Grapher*)glfwGetWindowUserPointer(window);
    if (!grapher) {
        std::cout << "ERROR! Window User Pointer undefined\n";
        exit(-1);
    }

    if (action == GLFW_PRESS) {
        switch (key) {
            // bug: this for some reason causes program to close when escape key pressed
            case GLFW_KEY_ESCAPE:
                glfwSetWindowShouldClose(window, GLFW_TRUE);
                break;
            
            // Data modification
            case GLFW_KEY_W:
                grapher->UpdateSize(grapher->dataPoints * 4);
                break;
            case GLFW_KEY_S:
                grapher->UpdateSize(grapher->dataPoints / 4);
                break;

            case GLFW_KEY_Q:
                grapher->UpdateAccuracy(grapher->accuracy * 2.0f);
                break;
            case GLFW_KEY_A:
                grapher->UpdateAccuracy(grapher->accuracy / 2.0f);
                break;

            case GLFW_KEY_D:
                grapher->offset[0] = 0;
                grapher->offset[1] = 0;
                grapher->zoom = 1;
                break;
        
            // Shader stuff
            case GLFW_KEY_E:
                grapher->Compute();
                break;
            case GLFW_KEY_R:
                grapher->GenerateShaders();
                break;
        }
    }
}