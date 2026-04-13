//actual includes
#include <stdio.h>
#include <stdbool.h>
#include <glad/glad.h> //INCLUDE BEFORE GLFW3
#include <GLFW/glfw3.h>

//fw src
#include "../headers/windowparams.h"
#include "../headers/window.h"
#include "../headers/render.h"
#include "../headers/usrinput.h"

//all inputs.
void process_input(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}
