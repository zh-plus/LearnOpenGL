//
// Created by 10578 on 2021/4/27.
//

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "fmt/core.h"

#include <iostream>

using namespace std;

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

template<size_t N1, size_t N2>
unsigned int get_triangle_VAO(const float (&vertices)[N1], const unsigned int (&indices)[N2]);

GLFWwindow *init_window();

unsigned int init_shaders(unsigned int R, unsigned int G, unsigned int B);

void processInput(GLFWwindow *window);

void framebuffer_size_callback(GLFWwindow *window, int width, int height);

void check_shader_status(unsigned int shader_id, unsigned int gl_status_id = GL_COMPILE_STATUS);

int main() {
    GLFWwindow *window = init_window();
    unsigned int shaderProgram_BYAKUROKU = init_shaders(168, 216, 185);
    unsigned int shaderProgram_WASURENAGUSA = init_shaders(125, 185, 222);

    // left triangle
    float vertices1[]{
            -0.5f, -0.5f, 0.0f, // bottom left
            -0.5f, 0.5f, 0.0f,  // top left
            0.3f, -0.5f, 0.0f  // bottom right
    };
    // right triangle
    float vertices2[]{
            0.5f, 0.5f, 0.0f,   // top right
            0.5f, -0.5f, 0.0f,  // bottom right
            -0.3f, 0.5f, 0.0f   // bottom right
    };

    unsigned int indices1[]{
            0, 1, 2,
    };
    unsigned int indices2[]{
            0, 1, 2
    };

    unsigned int triangle1_VAO = get_triangle_VAO(vertices1, indices1);
    unsigned int triangle2_VAO = get_triangle_VAO(vertices2, indices2);

    while (!glfwWindowShouldClose(window)) {
        processInput(window);

        glClearColor(105.0 / 255, 176.0 / 255, 172.0 / 255, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Set WileFrame mode
//        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

        glUseProgram(shaderProgram_BYAKUROKU);
        glBindVertexArray(triangle1_VAO);
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);

        glUseProgram(shaderProgram_WASURENAGUSA);
        glBindVertexArray(triangle2_VAO);
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

unsigned int init_shaders(unsigned int R, unsigned int G, unsigned int B) {
    // Create vertex shader
    const char *vertexShaderSource = R"(
        #version 460 core
        layout (location = 0) in vec3 aPos;
        void main(){
           gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
        }
)";
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);
    check_shader_status(vertexShader);

    // Create fragment shader
    const string fragmentShaderSourceStr = fmt::format(R"(
        #version 460 core
        out vec4 FragColor;
        void main(){{
           FragColor = vec4({}f, {}f, {}f, 1.0f);
        }}
)", R / 255.0, G / 255.0, B / 255.0);
    const char *fragmentShaderSource = fragmentShaderSourceStr.c_str();

    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);
    check_shader_status(fragmentShader);

    // Create shader program to link shaders together
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    check_shader_status(shaderProgram, GL_LINK_STATUS);

    // Delete the shaders after linking
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    return shaderProgram;
}

GLFWwindow *init_window() {
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    // Core profile mode should use triangle1_VAO(non-optionally)
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    // glfw window creation
    // --------------------
    GLFWwindow *window = glfwCreateWindow(800, 600, "LearnOpenGL", nullptr, nullptr);
    if (!window) {
        cout << "Failed to create GLFW window" << endl;
        glfwTerminate();
        exit(-1);
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------

    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
        cout << "Failed to initialize GLAD" << endl;
        exit(-1);
    }

    return window;
}

template<size_t N1, size_t N2>
unsigned int get_triangle_VAO(const float (&vertices)[N1], const unsigned int (&indices)[N2]) {
    // Using Vertex Array Object (triangle_VAO).
    unsigned int triangle_VAO;
    glGenVertexArrays(1, &triangle_VAO);
    glBindVertexArray(triangle_VAO);

    // Create vertex buffer object and bind it to GL_ARRAY_BUFFER,
    // whose usage is to configure the currently bound buffer --- Vertex Buffer Object (VBO).
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Create Element Array Buffer (one of Element Buffer Object [EBO])
    unsigned int EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Link vertex attributes and Enable vertex attribute array
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *) nullptr);
    glEnableVertexAttribArray(0);

    // Unbind triangle_VAO
    glBindVertexArray(0);

    return triangle_VAO;
}

void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

//
// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

void check_shader_status(unsigned int shader_id, unsigned int gl_status_id) {
    // Check if shader compilation success
    int success;
    char infoLog[512];
    glGetShaderiv(shader_id, gl_status_id, &success);
    if (!success) {
        glad_glGetShaderInfoLog(shader_id, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        exit(-1);
    }
}