#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "utils.h"
#include "conway.h"

#define SQUARE_SIZE 0.01f
#define SPACING 0.01f

GLuint shaderProgram;
GLuint VBO, VAO;

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void renderSquare(float x, float y, int active)
{
    // Use the shader program
    glUseProgram(shaderProgram);

    // Bind VAO
    glBindVertexArray(VAO);

    // Set the position attribute
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    // Set the position of the square
    float modelMatrix[16];
    mat4_identity(modelMatrix);
    mat4_translate_in_place(modelMatrix, x, y, 0.0f);

    // Get the location of the model matrix uniform from the shader
    GLint modelLoc = glGetUniformLocation(shaderProgram, "model");

    // Pass the model matrix to the shader
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, modelMatrix);

    float color[4]; // Declare the array

    if (active == 1)
    {
        color[0] = 0.0f; 
        color[1] = 0.6f; 
        color[2] = 0.0f;
        color[3] = 1.0f;
    }
    else
    {
        color[0] = 0.0f; 
        color[1] = 0.0f;
        color[2] = 0.0f; 
        color[3] = 1.0f;
    }

    // Set the color uniform in the shader
    GLint colorLoc = glGetUniformLocation(shaderProgram, "color");
    glUniform4fv(colorLoc, 1, color); // Pass the color as a vec4

    // Draw the square
    glDrawArrays(GL_QUADS, 0, 4);
}

int main()
{
    // Vertex data for a square
    float squareVertices[] = {
        -0.5f, -0.5f, // Bottom-left
        0.5f, -0.5f,  // Bottom-right
        0.5f, 0.5f,   // Top-right
        -0.5f, 0.5f   // Top-left
    };

    if (!glfwInit())
    {
        return -1;
    }

    GLFWwindow *window = glfwCreateWindow(800, 600, "Conway's Game of Life", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    // Initialize GLEW
    if (glewInit() != GLEW_OK)
    {
        fprintf(stderr, "Failed to initialize GLEW\n");
        return -1;
    }
    // Load Shader Files
    const char *fragmentShaderSource = loadFile("frag_shader.glsl");
    const char *vertexShaderSource = loadFile("vert_shader.glsl");
    // Create vertex shader
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    // Create fragment shader
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    // Create shader program
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glUseProgram(shaderProgram);

    // Cleanup shader sources
    free((void *)fragmentShaderSource);
    free((void *)vertexShaderSource);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    // Create VAO and VBO
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    // Bind VAO
    glBindVertexArray(VAO);

    // Bind VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(squareVertices), squareVertices, GL_STATIC_DRAW);

    int x_size = 300;
    int y_size = 300;
    int old_array[x_size * y_size];
    int new_array[x_size * y_size];
    create_world(old_array, x_size, y_size);
    double last_draw = 0;

    while (!glfwWindowShouldClose(window))
    {
        double seconds = glfwGetTime();

        glClear(GL_COLOR_BUFFER_BIT);
        int centerRow = x_size / 2;
        int centerCol = y_size / 2;

        for (int row = 0; row < x_size; ++row)
        {
            for (int col = 0; col < y_size; ++col)
            {
                float x = (col - centerCol) * SPACING;
                float y = (centerRow - row) * SPACING;
                if (get_value(old_array, row, col, y_size) == 0)
                {

                    renderSquare(x, y, 0);
                }
                else
                {

                    renderSquare(x, y, 1);
                }
            }
        }

        glfwSwapBuffers(window);
        glfwPollEvents();

        if ((seconds - last_draw) > 0.5l)
        {
            update(old_array, new_array, x_size, y_size);
            for (int x = 0; x < (x_size * y_size); ++x)
            {
                old_array[x] = new_array[x];
                new_array[x] = 0;
            }

            last_draw = seconds;
        }
        glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    }

    glfwTerminate();

    return 0;
}
