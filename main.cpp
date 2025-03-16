#include "main.hpp"

int main() {
    // init renderer
    Grapher grapher;
    grapher.InitWindow();
    grapher.InitStuff();

    // rtx on
    grapher.GenerateShaders();

    // the rtx data
    grapher.UpdateSize(grapher.drawingPoints);
    grapher.Compute();

    // yay infinite loop
    grapher.Loop();

    // bye bye
    glfwTerminate();
    return 0;
}