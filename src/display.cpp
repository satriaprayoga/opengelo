#include "display.h"

Display::Display(int w,int h,const std::string & title)
{
    if(!glfwInit())
    {
        std::cerr<<"GLFW initialization failed";
        glfwTerminate();
    }

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    window = glfwCreateWindow( w, h, title.c_str(), NULL, NULL);
    if( window == NULL )
    {
        std::cerr<<"Failed to open GLFW window.\n";
        glfwTerminate();
    }
    glfwMakeContextCurrent(window);
    if (glewInit() != GLEW_OK)
    {
        std::cerr<<"Failed to initizalized GLEW.\n";
    }
}

bool Display::IsClosed(){
    return glfwWindowShouldClose(window)==1;
}
void Display::Update()
{
    glfwSwapBuffers(window);
    glfwPollEvents();
}

void Display::Clear(float r, float g, float b, float a)
{
    glClearColor(r,g,b,a);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
}

Display::~Display()
{
    if(window!=NULL)
        glfwDestroyWindow(window);
    glfwTerminate();
}


