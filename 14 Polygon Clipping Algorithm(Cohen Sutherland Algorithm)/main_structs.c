#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdbool.h>

int screenWidth = 500, screenHeight = 500;

float xmin = 100, ymin = 100, xmax = 400, ymax = 400;

const int INSIDE = 0; // 0000 - region codes
const int LEFT = 1;   // 0001
const int RIGHT = 2;  // 0010
const int BOTTOM = 4; // 0100
const int TOP = 8;    // 1000

bool showClipped = false;  //toggle between original and clipped view

int computeCode(float x, float y) {
    int code = INSIDE;

    if (x < xmin)      //left of rectangle
        code |= LEFT;
    else if (x > xmax) //right of rectangle
        code |= RIGHT;
    if (y < ymin)      //below the rectangle
        code |= BOTTOM;
    else if (y > ymax) //above the rectangle
        code |= TOP;

    return code;
}

// Cohen-Sutherland line clipping algorithm
void cohenSutherlandClip(float x1, float y1, float x2, float y2) {
    int code1 = computeCode(x1, y1);
    int code2 = computeCode(x2, y2);
    int accept = 0;

    while (1) {
        if ((code1 == 0) && (code2 == 0)) {
            // Both endpoints are inside the rectangle
            accept = 1;
            break;
        } else if (code1 & code2) {
            // Both endpoints share an outside region
            break;
        } else {
            // One endpoint is outside the rectangle
            float x, y;

            int outcode = (code1 != 0) ? code1 : code2;

            if (outcode & TOP) {
                // Point is above the clipping rectangle
                x = x1 + (x2 - x1) * (ymax - y1) / (y2 - y1);
                y = ymax;
            } else if (outcode & BOTTOM) {
                // Point is below the rectangle
                x = x1 + (x2 - x1) * (ymin - y1) / (y2 - y1);
                y = ymin;
            } else if (outcode & RIGHT) {
                // Point is to the right of the rectangle
                y = y1 + (y2 - y1) * (xmax - x1) / (x2 - x1);
                x = xmax;
            } else if (outcode & LEFT) {
                // Point is to the left of the rectangle
                y = y1 + (y2 - y1) * (xmin - x1) / (x2 - x1);
                x = xmin;
            }

            // Replace the point outside the clipping rectangle
            if (outcode == code1) {
                x1 = x;
                y1 = y;
                code1 = computeCode(x1, y1);
            } else {
                x2 = x;
                y2 = y;
                code2 = computeCode(x2, y2);
            }
        }
    }

    if (accept) {
        glColor3f(0.0f, 1.0f, 0.0f); // Green color for clipped line
        glBegin(GL_LINES);
        glVertex2f(x1, y1);
        glVertex2f(x2, y2);
        glEnd();
    }
}

// Function to draw the clipping window
void drawClippingWindow() {
    glColor3f(1.0f, 0.0f, 0.0f); // Red color for clipping window
    glBegin(GL_LINE_LOOP);
    glVertex2f(xmin, ymin);
    glVertex2f(xmax, ymin);
    glVertex2f(xmax, ymax);
    glVertex2f(xmin, ymax);
    glEnd();
}

// Mouse button callback to toggle between original and clipped view
void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        // Toggle the clipped view when the left mouse button is pressed
        showClipped = !showClipped;
    }
}

int main() {
    if (!glfwInit()) {
        return -1;
    }
    GLFWwindow* window = glfwCreateWindow(screenWidth, screenHeight, "Cohen-Sutherland Line Clipping", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glOrtho(0, screenWidth, 0, screenHeight, -1, 1);
    glfwSetMouseButtonCallback(window, mouseButtonCallback);

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        drawClippingWindow();

        if (showClipped) {
            cohenSutherlandClip(50, 50, 450, 450);
            cohenSutherlandClip(50, 450, 450, 50);
        } else {
            glColor3f(1.0f, 1.0f, 1.0f); 
            glBegin(GL_LINES);
            glVertex2f(50, 50);
            glVertex2f(450, 450);
            glVertex2f(50, 450);
            glVertex2f(450, 50);
            glEnd();
        }

        glfwSwapBuffers(window);

        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}