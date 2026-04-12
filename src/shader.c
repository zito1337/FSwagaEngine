//actual includes
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glad/glad.h>

//fw src
#include "headers/shader.h"

static char* read_file(const char* path)
{
    FILE* f = fopen(path, "rb"); //"rb" = read binary mode
    if (!f) return NULL;
    
    //scrolls to the end of the file
    if (fseek(f, 0, SEEK_END) != 0){
        fclose(f); return NULL;
    }

    //tells the end of the file (end of the file == file's length in bytes)
    long size = ftell(f);
    if (size < 0) {
        fclose(f); return NULL;
    }

    //rewind file to the start of it, if application does not rewind it, then it would read file as a 0-byte trash because it would be readen from the end
    rewind(f);
    
    //allocating memory for size of a file PLUS "\0" symbol at the end
    char* buf = (char*)malloc((size_t)size + 1); // +1 is for "\n" so theres no buffer overflow
    if (!buf) {
        fclose(f); return NULL;
    }

    // reading the file in buf
    size_t read = fread(buf, 1, (size_t)size, f); //fread returns how many bytes were really readen

    //file is now readen. close it
    fclose(f);
    buf[read] = '\0';
    
    return buf;
}

//...
//no more documentation
//more soon
//...

static void print_shader_log(GLuint shader)
{
    GLint len = 0;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);
    if (len > 1) {
        char* log = (char*)malloc(len);
        glGetShaderInfoLog(shader, len, NULL, log);
        fprintf(stderr, "shader log:\n%s\n", log);
        free(log);
    }
}

static void print_program_log(GLuint prog)
{
    GLint len = 0;
    glGetProgramiv(prog, GL_INFO_LOG_LENGTH, &len);
    if (len > 1) {
        char* log = (char*)malloc(len);
        glGetProgramInfoLog(prog, len, NULL, log);
        fprintf(stderr, "program log:\n%s\n", log);
        free(log);
    }
}

Shader shader_from_files(const char* vertex_path, const char* fragment_path)
{
    Shader out = { 0 };
    char* vsrc = read_file(vertex_path);
    char* fsrc = read_file(fragment_path);
    if (!vsrc || !fsrc) {
        fprintf(stderr, "err: failed to read shader files: %s , %s\n", vertex_path, fragment_path);
        free(vsrc); free(fsrc);
        return out;
    }

    GLuint vert = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vert, 1, (const char**)&vsrc, NULL);
    glCompileShader(vert);
    GLint status = 0;
    glGetShaderiv(vert, GL_COMPILE_STATUS, &status);
    if (!status) {
        fprintf(stderr, "vertex shader compile error (%s):\n", vertex_path);
        print_shader_log(vert);
        glDeleteShader(vert);
        free(vsrc); free(fsrc);
        return out;
    }

    GLuint frag = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(frag, 1, (const char**)&fsrc, NULL);
    glCompileShader(frag);
    glGetShaderiv(frag, GL_COMPILE_STATUS, &status);
    if (!status) {
        fprintf(stderr, "fragment shader compile error (%s):\n", fragment_path);
        print_shader_log(frag);
        glDeleteShader(vert);
        glDeleteShader(frag);
        free(vsrc); free(fsrc);
        return out;
    }

    GLuint prog = glCreateProgram();
    glAttachShader(prog, vert);
    glAttachShader(prog, frag);
    glLinkProgram(prog);
    GLint linkStatus = 0;
    glGetProgramiv(prog, GL_LINK_STATUS, &linkStatus);
    if (!linkStatus) {
        fprintf(stderr, "shader program link error:\n");
        print_program_log(prog);
        glDeleteShader(vert);
        glDeleteShader(frag);
        glDeleteProgram(prog);
        free(vsrc); free(fsrc);
        return out;
    }

    // cleanup shaders
    glDeleteShader(vert);
    glDeleteShader(frag);

    out.id = prog;
    free(vsrc); free(fsrc);
    return out;
}

void shader_use(const Shader* s)
{
    if (s && s->id) glUseProgram(s->id);
}

void shader_destroy(Shader* s)
{
    if (s && s->id) {
        glDeleteProgram(s->id);
        s->id = 0;
    }
}