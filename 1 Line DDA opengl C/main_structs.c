// #include <GL/glut.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int xs, ys, x2, y2, thickness;

void drawThickLine(float xs, float ys, float x2, float y2, int thickness) {
    // DDA Algorithm
    float dx = x2 - xs;
    float dy = y2 - ys;
    float steps = fabs(dx) > fabs(dy) ? fabs(dx) : fabs(dy);

    float xIncrement = dx / steps;
    float yIncrement = dy / steps;

    float x, y;
    glBegin(GL_POINTS);
    for (int i = -thickness / 2; i <= thickness / 2; i++) {
        x = xs + i * (dy / sqrt(dx * dx + dy * dy));  // Offset perpendicular to the line
        y = ys - i * (dx / sqrt(dx * dx + dy * dy));  // Offset perpendicular to the line
        float xTmp = x, yTmp = y;

        for (int j = 0; j <= steps; j++) {
            glVertex2i(xTmp, yTmp);
            xTmp += xIncrement;
            yTmp += yIncrement;
        }
    }
    glEnd();
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    drawThickLine(xs, ys, x2, y2, thickness);
    glFlush();  // Execute OpenGL commands
}

void init(void) {
    glClearColor(1.0, 1.0, 1.0, 0.0);  // Background to white
    glColor3f(0.0, 0.0, 0.0);          // Drawing color to black
    glOrtho(0.0, 1080.0, 0.0, 720.0, -1, 1000);
}

int main() {
    if (!glfwInit()) {    // Initialize GLFW library
        printf("Unable to init glfw library.");
        exit(1);
    }

    xs = 0; ys = 0;
    x2 = 360; y2 = 240;
    thickness = 10;  // Thickness of the line

    GLFWwindow* win = glfwCreateWindow(1080, 720, "Thick DDA Line", 0, 0);
    glfwMakeContextCurrent(win);
    init();   // Set up the OpenGL environment

    while (!glfwWindowShouldClose(win)) {
        glfwPollEvents();
        display();
        glfwSwapBuffers(win);
    }

    glfwDestroyWindow(win);
    glfwTerminate();
    return 0;
}