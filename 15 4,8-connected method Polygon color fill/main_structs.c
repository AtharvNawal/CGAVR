#include <stdio.h>
//#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdbool.h> // For boolean values

#define maxHt 800
#define maxWd 600
#define STACK_SIZE 1000000

struct Point {
    int x, y;
};

// Global variables to store user's input
int fillMethod = 8; // Default to 4-connected
struct Point firstRect[2];  // First rectangle coordinates
struct Point secondRect[2]; // Second rectangle coordinates
struct Point startPoint;    // Starting point for filling

// Stack for flood fill
struct Point stack[STACK_SIZE];
int top = -1;

// Function to push a point to the stack
void push(int x, int y) {
    if (top < STACK_SIZE - 1) {
        top++;
        stack[top].x = x;
        stack[top].y = y;
    }
}

// Function to pop a point from the stack
struct Point pop() {
    return stack[top--];
}

// Function to check if the stack is empty
bool isStackEmpty() {
    return top == -1;
}

// Function to plot a single pixel
void plotPixel(int x, int y) {
    glColor3f(0.0f, 0.7f, 0.0f); // Green color for filling
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
    glFlush();
}

// Function to check if (x, y) is within bounds
bool isInBounds(int x, int y) {
    return (x >= 0 && x < maxHt && y >= 0 && y < maxWd);
}

// Function to check if (px, py) is inside the two non-overlapping rectangles
bool isInsideShape(int px, int py) {
    // Check if the point is inside the first rectangle
    bool inFirstRectangle = (px >= firstRect[0].x && px < firstRect[1].x &&
                             py >= firstRect[0].y && py < firstRect[1].y);

    // Check if the point is inside the second rectangle
    bool inSecondRectangle = (px >= secondRect[0].x && px < secondRect[1].x &&
                              py >= secondRect[0].y && py < secondRect[1].y);

    return inFirstRectangle || inSecondRectangle;
}

// 4-connected flood fill using stack
void fillShape4Connected(int startX, int startY) {
    bool visited[maxHt][maxWd] = {false};

    if (!isInBounds(startX, startY) || !isInsideShape(startX, startY)) return;

    push(startX, startY);
    visited[startX][startY] = true;

    while (!isStackEmpty()) {
        struct Point p = pop();

        // Plot the pixel
        plotPixel(p.x, p.y);

        // 4-connected neighbors
        struct Point neighbors[4] = {
            {p.x - 1, p.y}, {p.x + 1, p.y}, {p.x, p.y - 1}, {p.x, p.y + 1}
        };

        for (int i = 0; i < 4; i++) {
            int nx = neighbors[i].x;
            int ny = neighbors[i].y;

            if (isInBounds(nx, ny) && !visited[nx][ny] && isInsideShape(nx, ny)) {
                visited[nx][ny] = true;
                push(nx, ny);
            }
        }
    }
}

// 8-connected flood fill using stack
void fillShape8Connected(int startX, int startY) {
    bool visited[maxHt][maxWd] = {false};

    if (!isInBounds(startX, startY) || !isInsideShape(startX, startY)) return;

    push(startX, startY);
    visited[startX][startY] = true;

    while (!isStackEmpty()) {
        struct Point p = pop();

        // Plot the pixel
        plotPixel(p.x, p.y);

        // 8-connected neighbors
        struct Point neighbors[8] = {
            {p.x - 1, p.y}, {p.x + 1, p.y}, {p.x, p.y - 1}, {p.x, p.y + 1},
            {p.x - 1, p.y - 1}, {p.x + 1, p.y - 1}, {p.x - 1, p.y + 1}, {p.x + 1, p.y + 1}
        };

        for (int i = 0; i < 8; i++) {
            int nx = neighbors[i].x;
            int ny = neighbors[i].y;

            if (isInBounds(nx, ny) && !visited[nx][ny] && isInsideShape(nx, ny)) {
                visited[nx][ny] = true;
                push(nx, ny);
            }
        }
    }
}

void myInit() {
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glLoadIdentity();
    glOrtho(0, maxHt, 0, maxWd, -1, 1);
    glClear(GL_COLOR_BUFFER_BIT);
}

void display(GLFWwindow* window) {
    myInit();

    // Draw the first rectangle with a red outline
    glColor3f(1.0f, 0.0f, 0.0f); // Red color for edges
    glBegin(GL_LINE_LOOP);
    glVertex2i(firstRect[0].x, firstRect[0].y);
    glVertex2i(firstRect[1].x, firstRect[0].y);
    glVertex2i(firstRect[1].x, firstRect[1].y);
    glVertex2i(firstRect[0].x, firstRect[1].y);
    glEnd();

    // Draw the second rectangle with a red outline
    glBegin(GL_LINE_LOOP);
    glVertex2i(secondRect[0].x, secondRect[0].y);
    glVertex2i(secondRect[1].x, secondRect[0].y);
    glVertex2i(secondRect[1].x, secondRect[1].y);
    glVertex2i(secondRect[0].x, secondRect[1].y);
    glEnd();

    // Fill the shape using the selected flood fill method
    if (fillMethod == 4) {
        fillShape4Connected(startPoint.x, startPoint.y);
    } else if (fillMethod == 8) {
        fillShape8Connected(startPoint.x, startPoint.y);
    }

    glfwSwapBuffers(window);
    glfwPollEvents();
}

int main(void) {
    // Prompt user to enter rectangle coordinates and starting point
    printf("Enter the coordinates of the first rectangle (x1 y1 x2 y2): ");
    scanf("%d %d %d %d", &firstRect[0].x, &firstRect[0].y, &firstRect[1].x, &firstRect[1].y);

    printf("Enter the coordinates of the second rectangle (x1 y1 x2 y2): ");
    scanf("%d %d %d %d", &secondRect[0].x, &secondRect[0].y, &secondRect[1].x, &secondRect[1].y);

    printf("Enter the starting point for filling (x y): ");
    scanf("%d %d", &startPoint.x, &startPoint.y);

    // Prompt user to choose fill method
    int choice=1;
    // printf("Choose flood fill method:\n");
    // printf("1. 4-connected\n");
    // printf("2. 8-connected\n");
    // printf("Enter 1 or 2: ");
    // scanf("%d", &choice);

    // Set fill method based on user input
    if (choice == 1) {
        fillMethod = 4;
    } else if (choice == 2) {
        fillMethod = 8;
    } else {
        printf("Invalid choice. Defaulting to 4-connected.\n");
        fillMethod = 4;
    }

    if (!glfwInit()) {
        fprintf(stderr, "Failed to initialize GLFW\n");
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(maxHt, maxWd, "Connected Fill method", NULL, NULL);
    if (!window) {
        glfwTerminate();
        fprintf(stderr, "Failed to create GLFW window\n");
        return -1;
    }

    glfwMakeContextCurrent(window);

    // Initialize GLAD
    // if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    //     fprintf(stderr, "Failed to initialize GLAD\n");
    //     return -1;
    // }

    while (!glfwWindowShouldClose(window)) {
        display(window);
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}