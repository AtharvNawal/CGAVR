#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int pntX1, pntY1, r;

void plot(int x, int y) {
    glBegin(GL_POINTS);
    glVertex2i(x + pntX1, y + pntY1);
    glEnd();
}

void myInit(void) {
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glColor3f(0.0f, 0.0f, 0.0f);
    glPointSize(4.0);
    glLoadIdentity();
    glOrtho(0.0, 640.0, 0.0, 480.0, -1.0, 1.0);  // Changed from gluOrtho2D to glOrtho
}

void midPointCircleAlgotwo(int i) {
    int x = 0;
    int y = r;
    float decision = 5.0 / 4.0 - r;  // Fixed floating-point division
    plot(x, y);

    while (y > x) {
        if (decision < 0) {
            x++;
            decision += 2 * x + 1;
        } else {
            y--;
            x++;
            decision += 2 * (x - y) + 1;
        }

        plot(x, -y);
        plot(-x, -y);
        plot(y, -x);
        plot(-y, -x);
    }
}

void midPointCircleAlgo(int i) {
    int x = 0;
    int y = r;
    float decision = 5.0 / 4.0 - r;  // Fixed floating-point division
    plot(x, y);

    while (y > x) {
        if (decision < 0) {
            x++;
            decision += 2 * x + 1;
        } else {
            y--;
            x++;
            decision += 2 * (x - y) + 1;
        }

        plot(x, y);
        plot(-x, y);
        plot(y, x);
        plot(-y, x);
    }
}

void myDisplay(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 0.0, 0.0);
    glPointSize(1.0);

    for (int i = 0; i < 4; i++) {
        if (i % 2 == 0) {
            pntX1 += r + r;
            midPointCircleAlgo(i);
        } else {
            pntX1 += r + r;
            midPointCircleAlgotwo(i);
        }
    }

    glFlush();
}

int main(void) {
    // printf("Enter the coordinates of the center:\n\n");

    // printf("X-coordinate   : ");
    // scanf("%d", &pntX1);

    // printf("\nY-coordinate : ");
    // scanf("%d", &pntY1);

    // printf("\nEnter radius : ");
    // scanf("%d", &r);

    pntX1=100;
    pntY1=100;
    r=80;

    if (!glfwInit()) {
        printf("Unable to initialize GLFW\n");
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(640, 480, "7 wave (r+1) opengl C", NULL, NULL);
    if (!window) {
        printf("Unable to create window\n");
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    myInit();

    while (!glfwWindowShouldClose(window)) {
        myDisplay();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}