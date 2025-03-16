#include "main.hpp"



void Grapher::UpdateSize(GLuint newSize) {
    dataPoints = newSize;
    std::cout << "Points: " << dataPoints << "\n";
}
void Grapher::UpdateAccuracy(GLfloat newAccuracy) {
    accuracy = newAccuracy;
    std::cout << "Accuracy: " << accuracy << "\n";
}
void Grapher::Zoom(GLfloat offset) { // this works somehow so dont touch it
    glfwGetCursorPos(window, &mousePos[0], &mousePos[1]);
    mousePos[0] = mousePos[0] *2.0 / WIDTH - 1.0;
    mousePos[1] = -mousePos[1] * 2.0 / HEIGHT + 1.0;

    if (offset > 0) {
        zoom *= 2;
        this->offset[0] -= mousePos[0] / zoom;
        this->offset[1] -= mousePos[1] / zoom;
    }
    else {
        zoom /= 2;
        this->offset[0] += mousePos[0] / zoom / 2.0f;
        this->offset[1] += mousePos[1] / zoom / 2.0f;
    }
}



void Grapher::Compute() {
    std::cout << "Computing\n";
    glUseProgram(computeProgram);
    glUniform1f(glGetUniformLocation(computeProgram, "accuracy"), accuracy);
    glUniform1i(glGetUniformLocation(computeProgram, "size"), sqrt(dataPoints));
    glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(GLfloat) * 4 * dataPoints, nullptr, GL_DYNAMIC_DRAW);

    glDispatchCompute(sqrt(dataPoints), sqrt(dataPoints), 1);
    glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);
    drawingPoints = dataPoints;
    std::cout << "Computed!\n";
}



void Grapher::Draw() {
    glUseProgram(drawProgram);
    glUniform1f(glGetUniformLocation(drawProgram, "zoom"), zoom);
    glUniform2f(glGetUniformLocation(drawProgram, "offset"), offset[0], offset[1]);

    glBindVertexArray(vao);
    glDrawArrays(GL_POINTS, 0, drawingPoints);
}



void Grapher::Loop() {
    glClearColor(0.f, 0.f, 0.f, 1.f);
    double prevTime = glfwGetTime();
    while (!glfwWindowShouldClose(window)) {
        double newTime = glfwGetTime();
        glfwPollEvents();

        // Mouse Movement
        if (mousePressed) {
            double mouseX, mouseY;
            glfwGetCursorPos(window, &mouseX, &mouseY);
            mouseX = mouseX * 2.0 / WIDTH - 1.0;
            mouseY = -mouseY * 2.0 / HEIGHT + 1.0;
            offset[0] += (mouseX - mousePos[0]) / zoom;
            offset[1] += (mouseY - mousePos[1]) / zoom;
            mousePos[0] = mouseX;
            mousePos[1] = mouseY;
        }

        // FPS Counter (in title bar)
        std::string windowTitle = "Complex Graphing - FPS: " + std::to_string(1 / (newTime - prevTime));
        prevTime = newTime;
        glfwSetWindowTitle(window, windowTitle.c_str());

        glClear(GL_COLOR_BUFFER_BIT);
        Draw();

        glfwSwapBuffers(window);
    }
}