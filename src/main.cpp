// Headers
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cstdlib>
#include <string>
#include <iostream>
using namespace std;

#define WIDTH 800
#define HEIGHT 600

#include <filesystem>
namespace fs = std::filesystem;

static const fs::path project_path = fs::current_path();
static const fs::path resources_path = project_path / "resources";
static const fs::path shaders_path = resources_path / "shaders";

#include <fstream>
#include <sstream>
namespace utils {
    std::string shader_to_string(const std::string &shadername) {
        std::ifstream shader_file(shaders_path / (shadername + ".glsl"));
        std::ostringstream iss;
        iss << shader_file.rdbuf();
        return iss.str();
    }
}

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

int main() {

    GLFWwindow *window;
    if (!glfwInit()) {
        perror("GLFW Initialization Failed, check links");
        exit(EXIT_FAILURE);
    }

    window = glfwCreateWindow(WIDTH, HEIGHT, "Simple example", nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwSetKeyCallback(window, key_callback);
    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK) {
        perror("GLEW Initialization failed");
        exit(EXIT_FAILURE);
    }


    // Create Vertex Array Object
    uint32_t vertex_array;
    glGenVertexArrays(1, &vertex_array);
    glBindVertexArray(vertex_array);

    // Create a Vertex Buffer Object and copy the vertex data to it
    uint32_t vertex_buffer;
    glGenBuffers(1, &vertex_buffer);
//    typedef struct vert_t {
//        color_t color;
//    } Vertex;

    const float vertices[] = {
            -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, // Left
            0.5f, -0.5f, 0.0f, 1.0f, 0.0f, // Right
            0.5f, 0.5f, 0.0f, 0.0f, 1.0f, // Top
            -0.5f, 0.5f, 1.0f, 1.0f, 1.0f, // Top
    };

    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Create an element array
    uint32_t element_array;
    glGenBuffers(1, &element_array);

    const uint32_t elements[] = {0, 1, 2, 2, 3, 0};
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_array);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);

    std::string vs = utils::shader_to_string("TestVertexShader");
    std::string fs = utils::shader_to_string("TestFragmentShader");
    const char *vertex = vs.c_str();
    const char *fragment = fs.c_str();

    // Create and compile the vertex shader
    uint32_t vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertex, nullptr);
    glCompileShader(vertexShader);

    // Create and compile the fragment shader
    uint32_t fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragment, nullptr);
    glCompileShader(fragmentShader);

    // Link the vertex and fragment shader into a shader program
    uint32_t shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glBindFragDataLocation(shaderProgram, 0, "outColor");
    glLinkProgram(shaderProgram);
    glUseProgram(shaderProgram);

    // Specify the layout of the vertex data
    GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
    glEnableVertexAttribArray(posAttrib);
    glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), nullptr);

    GLint colAttrib = glGetAttribLocation(shaderProgram, "color");
    glEnableVertexAttribArray(colAttrib);
    glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void *) (2 * sizeof(GLfloat)));

    while (!glfwWindowShouldClose(window)) {
        // Clear the screen to black
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Draw a rectangle from the 2 triangles using 6 indices
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

        glfwSwapBuffers(window);
        glfwWaitEvents();
    }


    glDeleteProgram(shaderProgram);
    glDeleteShader(fragmentShader);
    glDeleteShader(vertexShader);

    glDeleteBuffers(1, &element_array);
    glDeleteBuffers(1, &vertex_buffer);

    glDeleteVertexArrays(1, &vertex_array);

    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}

