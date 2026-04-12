//actual includes
#include <stdio.h>
#include <stdbool.h>
#include <glad/glad.h> //INCLUDE BEFORE GLFW3
#include <GLFW/glfw3.h>

//fw src
#include "headers/windowparams.h"
#include "headers/render.h"

int render(GLFWwindow* window)
{
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    while(!glfwWindowShouldClose(window)){
        processInput(window);
        
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.0f, 0.65f, 0.70f, 1.0f);
        
        glfwSwapBuffers(window);
        glfwPollEvents();    
    }

    glfwTerminate();
    return 0;
}
void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}