#include <GLFW/glfw3.h>
#include <unistd.h>
#include "conway.h"

#define SQUARE_SIZE 0.01f
#define SPACING 0.01f

void renderSquare(float x, float y)
{
    glBegin(GL_QUADS);
    glVertex2f(x - SQUARE_SIZE / 2, y - SQUARE_SIZE / 2);
    glVertex2f(x + SQUARE_SIZE / 2, y - SQUARE_SIZE / 2);
    glVertex2f(x + SQUARE_SIZE / 2, y + SQUARE_SIZE / 2);
    glVertex2f(x - SQUARE_SIZE / 2, y + SQUARE_SIZE / 2);
    glEnd();
}

int main()
{
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

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    int x_size = 300;
    int y_size = 300;
    int old_array[x_size * y_size];
    int new_array[x_size * y_size];
    create_world(old_array, x_size, y_size);

    while (!glfwWindowShouldClose(window))
    {
        sleep(1);
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
                    glColor3f(0.0f, 0.0f, 0.0f);
                }
                else
                {
                    glColor3f(1.0f, 0.0f, 1.0f);
                }
                glMatrixMode(GL_MODELVIEW);
                glLoadIdentity();
                glTranslatef(x, y, 0.0f);

                renderSquare(x, y);
            }
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
        update(old_array, new_array, x_size, y_size);

        for (int x = 0; x < (x_size * y_size); ++x)
        {
            old_array[x] = new_array[x];
            new_array[x] = 0;
        }
    }

    glfwTerminate();

    return 0;
}