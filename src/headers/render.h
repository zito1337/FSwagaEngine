#ifndef RENDER_H
#define RENDER_H

extern GLuint vbo;
extern GLuint vao;
extern GLuint shader_program;

extern int render_init();

//I DONT know why is shader_program here I just added it for compatibility.
extern int render_tick(GLuint vao, GLuint vbo, GLuint shader_program);

#endif