#ifndef RENDER_H
#define RENDER_H
#include "shader.h"
extern GLuint vbo;
extern GLuint vao;
extern GLuint ebo;
extern Shader shader;
extern GLuint shader_program;

extern int render_init();

//I DONT actually know why is shader_program here I just added it for compatibility.
extern int render_tick(GLuint vao, GLuint vbo, GLuint shader_program, GLFWwindow* window);

#endif