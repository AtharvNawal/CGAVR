#include <GLFW/glfw3.h>
#include <stdlib.h> 

int screenWidth = 500, screenHeight = 500;

float fillColor[3] = {0.0f, 1.0f, 0.0f}; // Green 
float targetColor[3] = {1.0f, 1.0f, 1.0f}; // background color

void setPixel(int x, int y, float color[3]) {
    glColor3fv(color);
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

void getPixelColor(int x, int y, float color[3]) {
    glReadPixels(x, y, 1, 1, GL_RGB, GL_FLOAT, color);
}

int colorsMatch(float color1[3], float color2[3]) {
    return color1[0] == color2[0] && color1[1] == color2[1] && color1[2] == color2[2];
}

//flood fill algorithm using a 4-connected 
void floodFill4(int x, int y, float fillColor[3], float targetColor[3]) {
    float currentColor[3];
    getPixelColor(x, y, currentColor);

    if (colorsMatch(currentColor, targetColor)) {
        setPixel(x, y, fillColor);

        floodFill4(x + 1, y, fillColor, targetColor);
        floodFill4(x - 1, y, fillColor, targetColor);
        floodFill4(x, y + 1, fillColor, targetColor);
        floodFill4(x, y - 1, fillColor, targetColor);
    }
}

void drawPolygon() {
    glColor3f(0.0f, 0.0f, 1.0f); // Blue Boundary color
    glBegin(GL_LINE_LOOP);
    glVertex2i(200, 150); // Vertex 1
    glVertex2i(350, 350); // Vertex 2
    glVertex2i(50, 350);  // Vertex 3
    glEnd();
}

int main() {
    if (!glfwInit()) {
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(screenWidth, screenHeight, "Flood Fill Algorithm", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, screenWidth, 0, screenHeight, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glClearColor(1.0f, 1.0f, 1.0f, 1.6); // Light blue background

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        drawPolygon();

        floodFill4(200, 200, fillColor, targetColor);

        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}