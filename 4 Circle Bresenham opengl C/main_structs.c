#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>

int xc, yc, radius, thickness;

void drawThickCircle(int xc, int yc, int radius, int thickness) {
    for (int t = 0; t < thickness; t++) {
        int x = 0;
        int y = radius + t;  // Increase radius for each thickness level
        int d = 3 - 2 * (radius + t);

        glBegin(GL_POINTS);
        while (y >= x) {
            // Plot the points in each octant
            glVertex2i(xc + x, yc + y);
            glVertex2i(xc - x, yc + y);
            glVertex2i(xc + x, yc - y);
            glVertex2i(xc - x, yc - y);
            glVertex2i(xc + y, yc + x);
            glVertex2i(xc - y, yc + x);
            glVertex2i(xc + y, yc - x);
            glVertex2i(xc - y, yc - x);
            x++;
            if (d <= 0) {
                d = d + 4 * x + 6;
            } else {
                d = d + 4 * (x - y) + 10;
                y--;
            }
        }
        glEnd();
    }
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    drawThickCircle(xc, yc, radius, thickness);
    glFlush();
}

void init(void) {
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glColor3f(0.0, 0.0, 0.0);
    glOrtho(0.0, 1080.0, 0.0, 720.0, -1, 1);
}

int main() {
    if (!glfwInit()) {
        printf("Unable to initialize GLFW library.\n");
        exit(EXIT_FAILURE);
    }

    xc = 540; yc = 360; // Center of the screen
    radius = 250; // Radius
    thickness = 5; // Thickness of the circle

    GLFWwindow* win = glfwCreateWindow(1080, 720, "Thick Circle with Bresenham Algorithm", NULL, NULL);
    if (!win) {
        printf("Unable to create window.\n");
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(win);
    init();

    while (!glfwWindowShouldClose(win)) {
        glfwPollEvents();
        display();
        glfwSwapBuffers(win);
    }

    glfwDestroyWindow(win);
    glfwTerminate();
    return 0;
}