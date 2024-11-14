#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>

int x1, y1, x2, y2;

void drawLine(int x1, int y1, int x2, int y2) {
    int dx = x2 - x1;
    int dy = y2 - y1;
    int d = dy - (dx / 2);
    int x = x1, y = y1;

    glBegin(GL_POINTS);
    glVertex2i(x, y);

    while (x < x2) {
        x++;
        if (d < 0) {
            d = d + dy;
        } else {
            y++;
            d = d + (dy - dx);
        }
        glVertex2i(x, y);
    }
    glEnd();
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    drawLine(x1, y1, x2, y2);
    glFlush();
}

void init(void) {
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glPointSize(2.0);
    glColor3f(0.0, 0.0, 0.0);
    glOrtho(0.0, 1080.0, 0.0, 720.0, -1, 1);
}

int main() {
    if (!glfwInit()) {
        printf("Unable to initialize GLFW library.\n");
        exit(EXIT_FAILURE);
    }

    // Define the start and end points of the line
    x1 = 100; y1 = 100;
    x2 = 500; y2 = 300;

    GLFWwindow* win = glfwCreateWindow(1080, 720, "Midpoint Line Algorithm", NULL, NULL);
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