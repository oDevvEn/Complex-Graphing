#include "main.hpp"
#include <string>



void Grapher::Loop() {
    double prevTime = glfwGetTime();
    while (!glfwWindowShouldClose(window)) {
        double newTime = glfwGetTime();
        glfwPollEvents();

        // FPS Counter (in title bar)
        std::string windowTitle = "Complex Graphing - FPS: " + std::to_string(1 / (newTime - prevTime));
        prevTime = newTime;
        glfwSetWindowTitle(window, windowTitle.c_str());

        Draw();

        glClearColor(std::fmod(newTime, 1), 0.f, 0.f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
    }
}