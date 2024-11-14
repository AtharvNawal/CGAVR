#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>

int xs, ys, x2, y2, thickness;

void drawThickLine(int xs, int ys, int x2, int y2, int thickness) {
    int dx = abs(x2 - xs), dy = abs(y2 - ys);
    int sx = (xs < x2) ? 1 : -1;   // determines direction
    int sy = (ys < y2) ? 1 : -1;
    int err = dx - dy;

    for (int i = -thickness / 2; i <= thickness / 2; i++) {
        int xOffset = (dy == 0) ? 0 : i;
        int yOffset = (dx == 0) ? 0 : i;

        int xStart = xs + yOffset;
        int yStart = ys - xOffset;
        int xEnd = x2 + yOffset;
        int yEnd = y2 - xOffset;

        int x = xStart;
        int y = yStart;
        int errLine = err;

        glBegin(GL_POINTS);
        while (1) {
            glVertex2i(x, y);
            if (x == xEnd && y == yEnd) break;
            int e2 = 2 * errLine;
            if (e2 > -dy) {
                errLine -= dy;
                x += sx;
            }
            if (e2 < dx) {
                errLine += dx;
                y += sy;
            }
        }
        glEnd();
    }
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    drawThickLine(xs, ys, x2, y2, thickness);
    glFlush();
}

void init(void) {
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glColor3f(0.0, 0.0, 0.0);
    glOrtho(0.0, 1080.0, 0.0, 720.0, -1, 1000);
}

int main() {
    if (!glfwInit()) {
        printf("Unable to initialize GLFW library.\n");
        exit(EXIT_FAILURE);
    }

    xs = 100; ys = 100;  // Starting point of the line
    x2 = 600; y2 = 500;  // Ending point of the line
    thickness = 10;      // Thickness of the line

    GLFWwindow* win = glfwCreateWindow(1080, 720, "Thick Bresenham's Line Algorithm", NULL, NULL);
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