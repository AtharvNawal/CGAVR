#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>

int xc, yc, radius, thickness;

void drawThickCircle(int xc, int yc, int radius, int thickness) {
    for (int t = 0; t < thickness; t++) {
        int x = radius - t;  // Decrease the radius for each thickness level
        int y = 0;
        int dp = 1 - x;

        glBegin(GL_POINTS);
        while (x >= y) {
            // Plot the points in each octant
            glVertex2i(xc + x, yc + y);
            glVertex2i(xc - x, yc + y);
            glVertex2i(xc + x, yc - y);
            glVertex2i(xc - x, yc - y);
            glVertex2i(xc + y, yc + x);
            glVertex2i(xc - y, yc + x);
            glVertex2i(xc + y, yc - x);
            glVertex2i(xc - y, yc - x);

            y++;
            if (dp < 0) {
                dp += 2 * y + 1;
            } else {
                x--;
                dp += 2 * (y - x + 1);
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
    thickness = 10; // Thickness of the circle

    GLFWwindow* win = glfwCreateWindow(1080, 720, "Thick Midpoint Circle Algorithm", NULL, NULL);
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