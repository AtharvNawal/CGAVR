#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

float xc, yc; // Circle center
float radius = 50.0f; // Radius of the circle
float slope = 0.5f; // Slope of the ramp (rise/run)
float speed = 2.0f; // Speed of the circle
float vx, vy; // Velocity components

void drawCircle(float xc, float yc, float radius) {
    int num_segments = 100;
    float theta = 2.0f * 3.1415926f / (float)num_segments;
    float c = cosf(theta);
    float s = sinf(theta);
    float t;

    float x = radius;
    float y = 0;

    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < num_segments; i++) {
        glVertex2f(x + xc, y + yc);

        // Apply the rotation matrix
        t = x;
        x = c * x - s * y;
        y = s * t + c * y;
    }
    glEnd();
}

void drawFixedRamp(float xStart, float yStart, float length, float slope) {
    float line_x1 = xStart;
    float line_y1 = yStart;
    float line_x2 = xStart + length;
    float line_y2 = yStart + slope * length;

    glBegin(GL_LINES);
    glVertex2f(line_x1, line_y1);
    glVertex2f(line_x2, line_y2);
    glEnd();
}

void updatePosition() {
    xc += vx; // Update x position
    yc += vy; // Update y position
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw the fixed ramp
    drawFixedRamp(100.0f, 600.0f, 800.0f, slope);

    // Draw the sliding circle
    drawCircle(xc, yc, radius);

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

    GLFWwindow* win = glfwCreateWindow(1080, 720, "Sliding Circle on a Fixed Ramp", NULL, NULL);
    if (!win) {
        printf("Unable to create window.\n");
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(win);
    init();

    // Initial position of the circle
    xc = 100.0f;
    yc = 600.0f;

    // Calculate the velocity components based on the slope
    float angle = atan(slope);
    vx = speed * cos(angle);
    vy = -speed * sin(angle);

    while (!glfwWindowShouldClose(win)) {
        glfwPollEvents();
        updatePosition();
        display();
        glfwSwapBuffers(win);

        // Stop the circle when it reaches the end of the ramp
        if (xc > 900.0f || yc - radius <= 0) {
            break;
        }
    }

    glfwDestroyWindow(win);
    glfwTerminate();
    return 0;
}