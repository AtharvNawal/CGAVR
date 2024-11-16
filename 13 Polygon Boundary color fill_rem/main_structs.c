#include <GLFW/glfw3.h>
#include <stdlib.h> 

int screenWidth = 500, screenHeight = 500;

float fillColor[3] = {1.0f, 0.0f, 0.0f}; // Red 
float boundaryColor[3] = {1.0f, 1.0f, 0.0f}; // Yellow 

void setPixel(int x, int y, float color[3]) {
    glColor3fv(color);
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

void getPixelColor(int x, int y, float color[3]) {
    glReadPixels(x, y, 1, 1, GL_RGB, GL_FLOAT, color);
}

//compare two colors
int colorsMatch(float color1[3], float color2[3]) {
    return color1[0] == color2[0] && color1[1] == color2[1] && color1[2] == color2[2];
}

void boundaryFill4(int x, int y, float fillColor[3], float boundaryColor[3]) {
    float currentColor[3];
    getPixelColor(x, y, currentColor);

    if (!colorsMatch(currentColor, fillColor) && !colorsMatch(currentColor, boundaryColor)) {
        setPixel(x, y, fillColor);

        boundaryFill4(x + 1, y, fillColor, boundaryColor);
        boundaryFill4(x - 1, y, fillColor, boundaryColor);
        boundaryFill4(x, y + 1, fillColor, boundaryColor);
        boundaryFill4(x, y - 1, fillColor, boundaryColor);
    }
}

void drawPolygon() {
    glColor3f(1.0f, 1.0f, 0.0f); // Boundary color - yellow
    glBegin(GL_LINE_LOOP);
    glVertex2i(150, 150);
    glVertex2i(350, 150);
    glVertex2i(350, 350);
    glVertex2i(150, 350);
    glEnd();
}

int main() {
    if (!glfwInit()) {
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(screenWidth, screenHeight, "Boundary Fill Algorithm", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    glOrtho(0, screenWidth, 0, screenHeight, -1, 1);

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        drawPolygon();

        boundaryFill4(200, 200, fillColor, boundaryColor);

        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
