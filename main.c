//actual includes
#include <stdio.h>
#include <stdbool.h>
#include <glad/glad.h> //INCLUDE BEFORE GLFW3
#include <GLFW/glfw3.h>

//fw src
#include "src/headers/windowparams.h"
#include "src/headers/window.h"
#include "src/headers/render.h"

int WWIDTH = 800;
int WHEIGHT = 600;

int main()
{
    //glfw init
    glfwInit();
    
    //now we're setting glfw 3.3
    //set major glfw version
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    //set minor glfw version
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    //set glfw profile to core
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    //creating window
    GLFWwindow* window = glfwCreateWindow(WWIDTH, WHEIGHT, "FSwagaEngine", NULL, NULL);
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