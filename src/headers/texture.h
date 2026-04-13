#include <glad.h>
#ifndef TEXTURE_H
#define TEXTURE_H

typedef struct {
    GLuint id;
} Texture;

void bind_texture(Texture* txt);
void use_texture(Texture* txt);

//Texture texture_from_files(const char* vertex_path, const char* fragment_path);

#endif