#include "main.hpp"
#include <fstream>



void Grapher::InitWindow() {
    // GLFW error callback
    glfwSetErrorCallback(GLFWErrorCallback);

    if (!glfwInit()) {
        std::cout << "ERROR! Failed to intialise GLFW\n";
        exit(-1);
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
        exit(-1);
    }
    glfwSetKeyCallback(window, GLFWKeyCallback);
    glfwMakeContextCurrent(window);
    std::cout << "Window created\n";

    // Initialise GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "ERROR! Failed to initialise GLAD\n";
        exit(-1);
    }
    std::cout << "GLAD Initialised\n" << "Using: " << glGetString(GL_RENDERER) << "\n";
    
    // some minor config ig
    glfwSetWindowUserPointer(window, this);
    glfwSetWindowSizeCallback(window, GLFWResizeCallback); // Viewport updating (no idea what it does)
    glfwSetScrollCallback(window, GLFWScrollCallback);
    glfwSetMouseButtonCallback(window, GLFWButtonCallback);
    glfwSwapInterval(1); // vsync
    GLFWResizeCallback(window, WIDTH, HEIGHT);
}



void Grapher::InitStuff() {
    glGenBuffers(1, &ssbo);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, ssbo);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, ssbo);

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, ssbo);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_TRUE, 0, nullptr);
    glEnableVertexAttribArray(0);
}



void Grapher::GenerateShaders() {
    if (glIsProgram(drawProgram)) {
        glDeleteProgram(drawProgram);
    }
    if (glIsProgram(computeProgram)) {
        glDeleteProgram(computeProgram);
    }

    GLuint vertex = CompileShader(GL_VERTEX_SHADER, LoadShader("vertex.vert").c_str());
    GLuint fragment = CompileShader(GL_FRAGMENT_SHADER, LoadShader("fragment.frag").c_str());
    drawProgram = CreateProgram(new GLuint[3]{ vertex, fragment });

    GLuint compute = CompileShader(GL_COMPUTE_SHADER, LoadShader("compute.comp").c_str());
    computeProgram = CreateProgram(new GLuint[2]{ compute });
}



std::string Grapher::LoadShader(std::string path) {
    // Open file
    std::ifstream file(path);
    if (!file.is_open()) {
        std::cout << "ERROR! Failed to open shader path: " << path << "\n";
        exit(-1);
    }

    // Read from file
    std::string shader = "";
    std::string line = "";
    while (!file.eof()) {
        std::getline(file, line);
        shader.append(line + "\n");
    }
    
    // yay shader code obtained!
    file.close();
    return shader;
}



GLuint Grapher::CompileShader(GLenum type, const GLchar* code) {
    // Compile shader
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &code, NULL);
    glCompileShader(shader);

    // Error checking
    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        GLchar infoLog[512];
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cout << "ERROR! Shader compilation failed\n" << infoLog << "\n";
        exit(-1);
    }

    // yay we have a shader
    std::cout << "Compiled shader!\n";
    return shader;
}



GLuint Grapher::CreateProgram(GLuint shaders[]) {
    // Create program
    GLuint program = glCreateProgram();
    int pos = 0;
    do {
        glAttachShader(program, shaders[pos]);
    } while (shaders[++pos] != NULL);
    glLinkProgram(program);

    // Error checking
    GLint success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        GLchar infoLog[512];
        glGetProgramInfoLog(program, 512, NULL, infoLog);
        std::cout << "ERROR! Program creation failed\n" << infoLog << "\n";
        return program;// exit(-1);
    }

    // Delete shaders (apparently useless to us now)
    pos = 0;
    do {
        glDeleteShader(shaders[pos]);
    } while (shaders[++pos] != NULL);

    // yay we have a program!
    std::cout << "Program created!\n";
    return program;
}
