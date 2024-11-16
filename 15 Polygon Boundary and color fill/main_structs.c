#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PI 3.14159265

int *x, *y;    // Arrays to hold the x and y coordinates of the polygon vertices
int vertex;    // Number of vertices
int radius = 100;   // Radius of the polygon
int centreX = 300;  // Center X-coordinate
int centreY = 300;  // Center Y-coordinate

void generatePolygonPoints() {
    x = (int*)malloc(vertex * sizeof(int));
    y = (int*)malloc(vertex * sizeof(int));

    for (int i = 0; i < vertex; i++) {
        x[i] = (int)(centreX + radius * cos((i * 2.0 * PI) / vertex));
        y[i] = (int)(centreY + radius * sin((i * 2.0 * PI) / vertex));
    }
}

void lineDraw(int a1, int b1, int a2, int b2) {
    glBegin(GL_LINES);
    glVertex2i(a1, b1);
    glVertex2i(a2, b2);
    glEnd();
}

void drawPolygon() {
    glLineWidth(30.0); // Set the line width to 3.0 (you can adjust this value)
    for (int i = 0; i < vertex - 1; i++)
        lineDraw(x[i], y[i], x[i + 1], y[i + 1]);
    lineDraw(x[vertex - 1], y[vertex - 1], x[0], y[0]);

}

void fillPolygon(int cx, int cy) {
    glColor3f(1.0, 1.0, 0.0); // Yellow fill color
    glBegin(GL_POLYGON);
    for (int i = 0; i < vertex; i++) {
        glVertex2i(x[i], y[i]);
    }
    glEnd();
    glFlush();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 0.0, 0.0); // Red boundary color
    drawPolygon();
    fillPolygon(centreX, centreY); // Fill the polygon
    glfwSwapBuffers(glfwGetCurrentContext());
}

void init() {
    glClearColor(0.0, 0.0, 0.0, 0.0); // Black background color
    glOrtho(0.0, 1080.0, 0.0, 720.0, -1, 1);
}

int main() {
    if (!glfwInit()) {
        printf("Unable to initialize GLFW library.\n");
        return -1;
    }

    // printf("Enter the number of vertices of the polygon: ");
    // scanf("%d", &vertex);
    vertex=7;  // number of vertices
    generatePolygonPoints();

    GLFWwindow* win = glfwCreateWindow(1080, 720, "Simple Polygon Fill", NULL, NULL);
    if (!win) {
        printf("Unable to create window.\n");
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(win);
    init();

    while (!glfwWindowShouldClose(win)) {
        glfwPollEvents();
        display();
    }

    glfwDestroyWindow(win);
    glfwTerminate();
    free(x);
    free(y);

    return 0;
}