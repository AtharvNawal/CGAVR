#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <stdio.h>
#include <stdlib.h>

#include "util.h"
#include "shaders.h"

int main() {
	if (!glfwInit()) {
    printf("Unable to init glfw library.");
    exit(1);
  }
  
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  
  GLFWwindow* win = glfwCreateWindow(1080, 720, "Hello Triangle", 0, 0);
  glfwMakeContextCurrent(win);
  gladLoadGL();
  
  float verts[] = {
    -0.5f, -0.5f, 0.2f, 0.3f, 0.8f, 1.0f,
    +0.5f, -0.5f, 0.3f, 0.8f, 0.2f, 1.0f,
    +0.0f, +0.5f, 0.8f, 0.2f, 0.3f, 1.0f,
  };
  
  GLuint vao, vbo;
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);
  
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);
	
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*) 0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*) (2*sizeof(float)));
	glEnableVertexAttribArray(1);
  
  int prog = load_shaders();
  glUseProgram(prog);
  
  while (!glfwWindowShouldClose(win)) {
    glfwPollEvents();
    
    glClear(GL_COLOR_BUFFER_BIT);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    
    glfwSwapBuffers(win);
  }
  
  
  
  glfwDestroyWindow(win);
  glfwTerminate();
}
