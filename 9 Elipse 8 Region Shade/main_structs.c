#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>  // For usleep

int xc, yc, rx, ry;

void drawThickPixel(int x, int y, int thickness) {
    for (int i = -thickness; i <= thickness; i++) {
        for (int j = -thickness; j <= thickness; j++) {
            glVertex2i(x + i, y + j);
        }
    }
}

void drawEllipse(int xc, int yc, int rx, int ry, int thickness) {
    float dx, dy, d1, d2, x, y;
    x = 0;
    y = ry;

    // Initial decision parameter of region 1
    d1 = (ry * ry) - (rx * rx * ry) + (0.25 * rx * rx);
    dx = 2 * ry * ry * x;
    dy = 2 * rx * rx * y;

    glBegin(GL_POINTS);

    // For region 1
    while (dx < dy) {
        glColor3f(1.0, 0.0, 0.0);  //Red
        drawThickPixel(xc + x, yc + y, thickness);
        usleep(3000);
        glColor3f(0.0, 1.0, 0.0);  //Green
        drawThickPixel(xc - x, yc + y, thickness);
        usleep(3000);
        glColor3f(0.0, 0.0, 1.0);  //Blue
        drawThickPixel(xc + x, yc - y, thickness);
        usleep(3000);
        glColor3f(1.0, 1.0, 0.0);  //Yellow
        drawThickPixel(xc - x, yc - y, thickness);
        usleep(3000);

        // Updating decision parameter based on algorithm
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

    // Decision parameter of region 2
    d2 = ((ry * ry) * ((x + 0.5) * (x + 0.5))) + ((rx * rx) * ((y - 1) * (y - 1))) - (rx * rx * ry * ry);

    // For region 2
    while (y >= 0) {
        glColor3f(1.0, 0.0, 1.0);  //R+B= Magenta
        drawThickPixel(xc + x, yc + y, thickness);
        usleep(3000);
        glColor3f(1.0, 1.0, 1.0);  //Whte
        drawThickPixel(xc - x, yc + y, thickness);
        usleep(3000);
        glColor3f(0.0, 1.0, 1.0);  //Cyan
        drawThickPixel(xc + x, yc - y, thickness);
        usleep(3000);
        glColor3f(1.0, 0.5, 0.0);  //Orange
        drawThickPixel(xc - x, yc - y, thickness);
        usleep(3000);

        // Updating decision parameter based on algorithm
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

    glEnd();
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    int thickness = 2; // You can change this to make the ellipse thicker or thinner
    drawEllipse(xc, yc, rx, ry, thickness);
    glFlush();
}

void init(void) {
    glClearColor(0.0, 0.0, 0.0, 0.0);   //glClearColor(1.0, 1.0, 1.0, 0.0); - white
    glColor3f(0.0, 0.0, 0.0);
    glOrtho(0.0, 1080.0, 0.0, 720.0, -1, 1);
}

int main() {
    if (!glfwInit()) {
        printf("Unable to initialize GLFW library.\n");
        exit(EXIT_FAILURE);
    }

    xc = 540;
    yc = 360;
    rx = 150;
    ry = 100;

    GLFWwindow* win = glfwCreateWindow(1080, 720, "Midpoint Ellipse Algorithm", NULL, NULL);
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