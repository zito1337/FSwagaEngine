//actual includes
#include <stdio.h>
#include <stdbool.h>
#include <glad/glad.h> //INCLUDE BEFORE GLFW3
#include <GLFW/glfw3.h>

//fw src
#include "../headers/windowparams.h"
#include "../headers/window.h"

float vertices[] = {
    // first triangle
     0.5f,  0.5f, 0.0f,  // top right
     0.5f, -0.5f, 0.0f,  // bottom right
    -0.5f,  0.5f, 0.0f,  // top left 
    // second triangle
     0.5f, -0.5f, 0.0f,  // bottom right
    -0.5f, -0.5f, 0.0f,  // bottom left
    -0.5f,  0.5f, 0.0f   // top left
};
//TODO: indices and EBO instead of this shitty little vertices array

const char* fragment_shader =
"#version 410 core\n"
"out vec4 frag_colour;"
"void main() {"
"  frag_colour = vec4( 0.5, 0.0, 0.5, 1.0 );"
"}";

const char* vertex_shader =
"#version 410 core\n"
"layout(location = 0) in vec3 vp;"
"void main() {"
"  gl_Position = vec4( vp, 1.0 );"
"}";

GLuint vbo = 0;
GLuint vao = 0;
GLuint shader_program;

int render_init(){
    glGenBuffers( 1, &vbo );

    glGenVertexArrays( 1, &vao );

    //bind buffer data
    glBindBuffer( GL_ARRAY_BUFFER, vbo );
    //Q: why did you ( flamka6 ) use 9*sizeof(float) instead of sizeof(vertices)?
    //I mean, wouldn't it be better if I could render more vertices than 3
    glBufferData( GL_ARRAY_BUFFER, sizeof( vertices ), vertices, GL_STATIC_DRAW );

    //bind vertex array and put into buffers
    glBindVertexArray( vao );
    glEnableVertexAttribArray( 0 );
    glBindBuffer( GL_ARRAY_BUFFER, vbo );
    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, NULL );

    //define vertex & fragment shaders
    // fragment - color
    // vertex - coords of vertices & object
    GLuint vs = glCreateShader( GL_VERTEX_SHADER );
    glShaderSource( vs, 1, &vertex_shader, NULL );
    glCompileShader( vs );
    GLuint fs = glCreateShader( GL_FRAGMENT_SHADER );
    glShaderSource( fs, 1, &fragment_shader, NULL );
    glCompileShader( fs );
    
    shader_program = glCreateProgram();
    glAttachShader( shader_program, fs );
    glAttachShader( shader_program, vs );
    glLinkProgram( shader_program );
    return 0;
}

int render_tick(GLuint vao, GLuint vbo, GLuint shader_program){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.329f, 0.745f, 0.941f, 1.0f);
    
    glUseProgram(shader_program);
    glBindVertexArray(vao);

    // maybe a shitcode but I guess I have no choice (sizeof vertices is 72 and I don't know why)
    glDrawArrays(GL_TRIANGLES, 0, sizeof(vertices));

    return 0;
}