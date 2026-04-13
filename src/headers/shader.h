#ifndef SHADER_H
#define SHADER_H

typedef struct {
    GLuint id;
} Shader;

// create shader program from files path
// returns Shader with id == 0 if error
Shader shader_from_files(const char* vertex_path, const char* fragment_path);

// activate shader program
void shader_use(const Shader* s);

void setFloat(Shader* s, const char* name, float value);

// DESTROY shader program to free memory
void shader_destroy(Shader* s);

#endif