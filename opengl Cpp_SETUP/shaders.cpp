#include <glad/glad.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "util.h"

const char *vs = "#version 330 core\n"
				 "layout (location=0) in vec2 a_pos;\n"
				 "layout (location=1) in vec4 a_col;\n"
				 "out vec4 v_col;\n"
				 "void main() {\n"
				 "  gl_Position = vec4(a_pos, 0.0, 1.0);\n"
				 "  v_col = a_col;\n"
				 "}\n";

const char *fs = "#version 330 core\n"
				 "in vec4 v_col;\n"
				 "layout (location=0) out vec4 frag_color;\n"
				 "void main() {\n"
				 "  frag_color = v_col;\n"
				 "}\n";

int load_shaders(void)
{
	int program = glCreateProgram();

	int vsm = glCreateShader(GL_VERTEX_SHADER);
	int fsm = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(vsm, 1, &vs, 0);
	glShaderSource(fsm, 1, &fs, 0);

	glCompileShader(vsm);

	int error;
	glGetShaderiv(vsm, GL_COMPILE_STATUS, &error);
	if (error == GL_FALSE)
	{
		printf("Vertex Shader Compilation failed!\n");
		int length = 0;
		glGetShaderiv(vsm, GL_INFO_LOG_LENGTH, &length);
		GLchar *info = (GLchar*)malloc(length * sizeof(GLchar));
		glGetShaderInfoLog(vsm, length * sizeof(GLchar), (GLsizei*)nullptr, info);
		printf("%s\n", info);
		exit(-1);
	}

	glCompileShader(fsm);

	glGetShaderiv(fsm, GL_COMPILE_STATUS, &error);
	if (error == GL_FALSE)
	{
		printf("Fragment Shader Compilation failed!\n");
		int length = 0;
		glGetShaderiv(fsm, GL_INFO_LOG_LENGTH, &length);
		GLchar *info = (GLchar*)malloc(length * sizeof(GLchar));
		glGetShaderInfoLog(fsm, length * sizeof(GLchar), (GLsizei*)nullptr, info);
		printf("%s\n", info);
		exit(-1);
	}

	glAttachShader(program, vsm);
	glAttachShader(program, fsm);
	glLinkProgram(program);

	glGetProgramiv(program, GL_LINK_STATUS, &error);
	if (error == GL_FALSE)
	{
		printf("Program Linking Failed:\n");
		int length = 0;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
		GLchar *info = (GLchar*)malloc(length * sizeof(GLchar));
		glGetProgramInfoLog(program, length * sizeof(GLchar), (GLsizei*)nullptr, info);
		printf("%s\n", info);
		exit(-1);
	}

	glValidateProgram(program);
	glUseProgram(program);

	return program;
}