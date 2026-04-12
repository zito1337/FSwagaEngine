//actual includes
#include <stdio.h>
#include <stdbool.h>
#include <glad/glad.h> //INCLUDE BEFORE GLFW3
#include <GLFW/glfw3.h>

//fw src
#include "headers/windowparams.h"
#include "headers/window.h"
#include "headers/render.h"

int init(GLFWwindow* window)
{
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    render_init();

    while(!glfwWindowShouldClose(window)){
        process_input(window);
        
        render_tick(vao, vbo, shader_program);

        glfwSwapBuffers(window);
        glfwPollEvents();    
    }

    glfwTerminate();
    return 0;
}

void process_input(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glfwGetFramebufferSize(window, &width, &height);
    if (width <= 0 || height <= 0) return;

    glViewport(0, 0, width, height);

    // force a redraw so the window updates during resize
    render_tick(vao, vbo, shader_program);
    
    glfwSwapBuffers(window);
}