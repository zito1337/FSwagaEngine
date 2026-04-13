//actual includes
#include <stdio.h>
#include <stdbool.h>
#include <glad/glad.h> //INCLUDE BEFORE GLFW3
#include <GLFW/glfw3.h>
#include <math.h>
#include <cglm/cglm.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

//fw src
#include "../headers/windowparams.h"
#include "../headers/window.h"
#include "../headers/shader.h"

float vertices[] = {
    // positions           // colors          // texcoords

    // FRONT
    -0.5f, -0.5f,  0.5f,   1.0f,1.0f,1.0f,   0.0f,0.0f,
     0.5f, -0.5f,  0.5f,   1.0f,1.0f,1.0f,   1.0f,0.0f,
     0.5f,  0.5f,  0.5f,   1.0f,1.0f,1.0f,   1.0f,1.0f,
    -0.5f,  0.5f,  0.5f,   1.0f,1.0f,1.0f,   0.0f,1.0f,

    // BACK
    -0.5f, -0.5f, -0.5f,   1.0f,1.0f,1.0f,   1.0f,0.0f,
     0.5f, -0.5f, -0.5f,   1.0f,1.0f,1.0f,   0.0f,0.0f,
     0.5f,  0.5f, -0.5f,   1.0f,1.0f,1.0f,   0.0f,1.0f,
    -0.5f,  0.5f, -0.5f,   1.0f,1.0f,1.0f,   1.0f,1.0f,
};

unsigned int indices[] = {
    // front
    0, 1, 2,
    2, 3, 0,

    // right
    1, 5, 6,
    6, 2, 1,

    // back
    5, 4, 7,
    7, 6, 5,

    // left
    4, 0, 3,
    3, 7, 4,

    // top
    3, 2, 6,
    6, 7, 3,

    // bottom
    4, 5, 1,
    1, 0, 4
};

GLuint vbo = 0;
GLuint vao = 0;
GLuint ebo = 0;
Shader shader;
GLuint shader_program;
unsigned int texture;

int render_init(){

    glEnable(GL_DEPTH_TEST);

    glGenVertexArrays( 1, &vao );
    glGenBuffers( 1, &vbo );
    glGenBuffers(1, &ebo);

    //bind vertex array and put into buffers
    glBindVertexArray( vao );

    //bind buffer data
    glBindBuffer( GL_ARRAY_BUFFER, vbo );
    glBufferData( GL_ARRAY_BUFFER, sizeof( vertices ), vertices, GL_STATIC_DRAW );

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW); 

    glEnableVertexAttribArray( 0 );

    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0 );

    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    shader = shader_from_files("resources/shaders/coreshader.vert", "resources/shaders/coreshader.frag");
    if (shader.id == 0) {
        fprintf(stderr, "err: failed to create shader program\n");
        return -1;
    }

    shader_program = shader.id;

    glUseProgram(shader_program);
    glUniform1i(glGetUniformLocation(shader_program, "ourTexture"), 0);

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    // wrapping
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // filtering:
    //old
    // flamka: i turned it off because it's look's ugly and idk why
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

    //new
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    // image loading
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);  
    unsigned char *data = stbi_load("resources/textures/Flag_of_Russia.png",
                                &width, &height, &nrChannels, 0);

    if (data)
    {
        GLenum format = (nrChannels == 4) ? GL_RGBA : GL_RGB;

        glTexImage2D(GL_TEXTURE_2D, 0, format,
                 width, height, 0,
                 format, GL_UNSIGNED_BYTE, data);

        //glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        printf("Failed to load texture\n");
    }

    stbi_image_free(data);

    return 0;
}

int render_tick(GLuint vao, GLuint vbo, GLuint shader_program, GLFWwindow* window){
    glClearColor(0.329f, 0.745f, 0.941f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    float timeValue = glfwGetTime();
    float greenValue = sinf(timeValue) / 2.0f + 0.5f;

    glUseProgram(shader_program);

    //WTF THIS CODE MAKE A +7k FPS WTF BROOOOOOOO
    int vertexColorLocation = glGetUniformLocation(shader_program, "ourColor");
    glUniform4f(vertexColorLocation, 0.0f, greenValue, greenValue, 1.0f);
    //WTF THIS CODE MAKE A +7k FPS WTF BROOOOOOOO

    //texture activation to object
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);

    //perspective relative by object
    mat4 model;
    //perspective relative by camera
    mat4 view;
    //perspective relative by projection
    mat4 projection;

    float angle = glfwGetTime();
    glm_mat4_identity(model);

    glm_rotate(model, angle, (vec3){0.0f, 1.0f, 0.0f});
    glm_mat4_identity(view);
    glm_mat4_identity(projection);

    //camera transform set to 1.0f by z (move camera to back by 1.0f)
    glm_translate(view, (vec3){0.0f, 0.0f, -2.0f});

    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    float aspect = (float)width / (float)height;

    glm_perspective(glm_rad(60.0f),
                 aspect,
                 0.1f,
                 100.0f,
                 projection);

    int m = glGetUniformLocation(shader_program, "model");
    int v = glGetUniformLocation(shader_program, "view");
    int p = glGetUniformLocation(shader_program, "projection");

    glUniformMatrix4fv(m, 1, GL_FALSE, (float*)model);
    glUniformMatrix4fv(v, 1, GL_FALSE, (float*)view);
    glUniformMatrix4fv(p, 1, GL_FALSE, (float*)projection);

    //draw quad
    glBindVertexArray(vao);

    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    return 0;
}