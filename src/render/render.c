//actual includes
#include <stdio.h>
#include <stdbool.h>
#include <glad/glad.h> //INCLUDE BEFORE GLFW3
#include <GLFW/glfw3.h>
#include <math.h>
//fw src
#include "../headers/windowparams.h"
#include "../headers/window.h"
#include "../headers/shader.h"

float vertices[] = {
     0.5f,  0.5f, 0.0f,  // top right
     0.5f, -0.5f, 0.0f,  // bottom right
    -0.5f, -0.5f, 0.0f,  // bottom left
    -0.5f,  0.5f, 0.0f   // top left 
};
unsigned int indices[] = {  // note that we start from 0!
    0, 1, 3,   // first triangle
    1, 2, 3    // second triangle
};

GLuint vbo = 0;
GLuint vao = 0;
GLuint ebo = 0;
Shader shader;
GLuint shader_program;

int render_init(){
    glGenBuffers( 1, &vbo );
    glGenBuffers(1, &ebo);

    glGenVertexArrays( 1, &vao );
    
    //bind buffer data
    glBindBuffer( GL_ARRAY_BUFFER, vbo );

    glBufferData( GL_ARRAY_BUFFER, sizeof( vertices ), vertices, GL_STATIC_DRAW );

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW); 

    //bind vertex array and put into buffers
    glBindVertexArray( vao );
    glEnableVertexAttribArray( 0 );
    glBindBuffer( GL_ARRAY_BUFFER, vbo );
    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, NULL );


    shader = shader_from_files("resources/shaders/coreshader.vert", "resources/shaders/coreshader.frag");
    if (shader.id == 0) {
        fprintf(stderr, "err: failed to create shader program\n");
        return -1;
    }

    shader_program = glCreateProgram();
    
    shader_program = shader.id;

    return 0;
}

int render_tick(GLuint vao, GLuint vbo, GLuint shader_program){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.329f, 0.745f, 0.941f, 1.0f);
    
    float timeValue = glfwGetTime();
    float greenValue = sinf(timeValue) / 2.0f + 0.5f;
    int vertexColorLocation = glGetUniformLocation(shader_program, "ourColor");
    glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

    glUseProgram(shader_program);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

    //draw elements with indices (finally not vertices!!!!)
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    return 0;
}