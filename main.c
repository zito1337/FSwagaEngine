//actual includes
#include <stdio.h>
#include <stdbool.h>
#include <glad/glad.h> //INCLUDE BEFORE GLFW3
#include <GLFW/glfw3.h>

//fw src
#include "src/headers/windowparams.h"
#include "src/headers/window.h"
#include "src/headers/render.h"

int window_width = 800;
int window_height = 600;

int main()
{
    //glfw init
    glfwInit();
    
    //now we're setting glfw 4.6
    //set major glfw version
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    //set minor glfw version
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    //set glfw profile to core
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    //creating window
    GLFWwindow* window = glfwCreateWindow(window_width, window_height, "FSwagaEngine", NULL, NULL);
    if (window == NULL)
    {
        printf("Failed to create GLFW window");
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        printf("Failed to initialize GLAD");
        return -1;
    }
    
    //start opengl render pipeline
    init(window);
    
    return 0;
}