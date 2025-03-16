#include "main.hpp"

int main() {
    Grapher grapher;

    // init renderer
    int initResult = grapher.Init();
    if (initResult != 0) {
        return initResult;
    }

    // yay infinite loop
    grapher.Loop();

    // bye bye
    glfwTerminate();
    return 0;
}