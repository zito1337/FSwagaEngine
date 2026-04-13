//actual includes
#include <stdio.h>
#include <stdbool.h>
#include <glad/glad.h> //INCLUDE BEFORE GLFW3
#include <GLFW/glfw3.h>

//fw src
#include "headers/windowparams.h"
#include "headers/window.h"
#include "headers/render.h"
double lastTime;
int nbFrames = 0;

int init(GLFWwindow* window)
{
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    
    render_init();
    glfwSwapInterval(0);

    while(!glfwWindowShouldClose(window)){
        process_input(window);
        render_tick(vao, vbo, shader_program);
        
        static double fpsTimer = 0.0;
        static int frames = 0;

        double currentTime = glfwGetTime();
        frames++;

        fpsTimer += currentTime - lastTime;
        lastTime = currentTime;

        if (fpsTimer >= 1) {
            double fps = frames / fpsTimer;

            char title[128];
            snprintf(title, sizeof(title), "FSwagaEngine | FPS: %.0f |", fps);

            glfwSetWindowTitle(window, title);

            frames = 0;
            fpsTimer = 0.0;
    }

        glfwSwapBuffers(window);
        glfwPollEvents();    
    }

    shader_destroy(&shader);
    glfwTerminate();

    return 0;
}

void process_input(GLFWwindow *window)
{
    static int e_prev = GLFW_RELEASE;
    int e_state = glfwGetKey(window, GLFW_KEY_E);

    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    e_prev = e_state;
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