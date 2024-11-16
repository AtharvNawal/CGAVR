#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int xc, yc, rx, ry;
float drawSpeed = 0.1f; // Controls the speed of the drawing animation
float drawProgress = 0.0f;

void drawFilledEllipse(int xc, int yc, int rx, int ry, float progress) {
    float dx, dy, d1, d2;
    int x = 0;
    int y = ry;
    int minY = (int)((1.0f - progress) * ry); // Min y-coordinate to draw based on progress

    d1 = (ry * ry) - (rx * rx * ry) + (0.25 * rx * rx);
    dx = 2 * ry * ry * x;
    dy = 2 * rx * rx * y;

    // region 1
    while (dx < dy && y >= minY) {
        for (int i = xc - x; i <= xc + x; i++) {
            glVertex2i(i, yc + y);
            glVertex2i(i, yc - y);
        }

        if (d1 < 0) {
            x++;
            dx = dx + (2 * ry * ry);
            d1 = d1 + dx + (ry * ry);
        } else {
            x++;
            y--;
            dx = dx + (2 * ry * ry);
            dy = dy - (2 * rx * rx);
            d1 = d1 + dx - dy + (ry * ry);
        }
    }

    // region 2
    d2 = ((ry * ry) * ((x + 0.5) * (x + 0.5))) + ((rx * rx) * ((y - 1) * (y - 1))) - (rx * rx * ry * ry);

    while (y >= minY) {
        for (int i = xc - x; i <= xc + x; i++) {
            glVertex2i(i, yc + y);
            glVertex2i(i, yc - y);
        }

        if (d2 > 0) {
            y--;
            dy = dy - (2 * rx * rx);
            d2 = d2 + (rx * rx) - dy;
        } else {
            y--;
            x++;
            dx = dx + (2 * ry * ry);
            dy = dy - (2 * rx * rx);
            d2 = d2 + dx - dy + (rx * rx);
        }
    }
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0.0, 0.0, 0.5); // Set color
    glBegin(GL_POINTS);
    drawFilledEllipse(xc, yc, rx, ry, drawProgress);
    glEnd();

    glFlush();
}

void updateDrawProgress(float deltaTime) {
    drawProgress += drawSpeed * deltaTime;

    if (drawProgress > 1.0f) {
        drawProgress = 1.0f; // Stop animation when the ellipse is fully drawn
    }
}

void init(void) {
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glOrtho(0.0, 1080.0, 0.0, 720.0, -1, 1);
}

int main() {
    if (!glfwInit()) {
        printf("Unable to initialize GLFW library.\n");
        exit(EXIT_FAILURE);
    }

    xc = 540;
    yc = 360;
    rx = 150;  //250
    ry = 70;  //100

    GLFWwindow* win = glfwCreateWindow(1080, 720, "Reverse Animated Ellipse Drawing", NULL, NULL);
    if (!win) {
        printf("Unable to create window.\n");
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(win);
    init();

    glfwSetTime(0.0);

    while (!glfwWindowShouldClose(win)) {
        float time = glfwGetTime();   // Get the current time
        glfwSetTime(0.0);             // Reset the timer for the next frame

        updateDrawProgress(time);     // Update the drawing progress
        display();                    // Render the ellipse based on the current progress

        glfwSwapBuffers(win);
        glfwPollEvents();
    }

    glfwDestroyWindow(win);
    glfwTerminate();
    return 0;
}