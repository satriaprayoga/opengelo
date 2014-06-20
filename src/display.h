#ifndef DISPLAY_H
#define DISPLAY_H
#include<iostream>
#include<string>
#include<GL/glew.h>
#include<GLFW/glfw3.h>

class Display
{
public:
    Display(int w,int h,const std::string & title);
    void Update();
    bool IsClosed();
    void Clear(float r, float g, float b, float a);
    virtual ~Display();
protected:
private:

    GLFWwindow * window;
    Display(const Display& other) {}
    void operator=(const Display& other) {}

};

#endif // DISPLAY_H
