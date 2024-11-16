#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Point {
  float x;
  //char u;
  //char v;
  float y;
} Point;
// [ x x x x | u y y y | y ]

int main() {
	if (!glfwInit()) {
    printf("Unable to init glfw library.");
    exit(1);
  }
  
  GLFWwindow* win = glfwCreateWindow(1080, 720, "Hello Triangle", 0, 0);
  glfwMakeContextCurrent(win);

  Point points1[] = {
    { -0.5, -0.5 },
    {  0.5, -0.5 },
    {  -0.5,  0.5 },
    {  0.5,  0.5 },
  };
  
  while (!glfwWindowShouldClose(win)) {
    glfwPollEvents();
    
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 4; i++) {
      //glVertex2f(points[i*2], points[(i*2)+1]);
      glVertex2f(points1[i].x, points1[i].y);
    }
    glEnd();
    
    glfwSwapBuffers(win);
  }
  
  
  
  glfwDestroyWindow(win);
  glfwTerminate();
}
