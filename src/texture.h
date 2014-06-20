#ifndef TEXTURE_H
#define TEXTURE_H

#include<GL/glew.h>
#include "bitmap.h"

class Texture
{
public:
    Texture(const Bitmap& bitmap,GLint minMagFilter=GL_LINEAR,GLint wrapMode=GL_CLAMP_TO_EDGE);
    virtual ~Texture();

    inline GLuint objectId()const
    {
        return m_objectId;
    }
    inline GLfloat originalHeight()const
    {
        return m_originalHeight;
    }
    inline GLfloat originalWidth()const
    {
        return m_originalWidth;
    }

protected:
private:
    GLfloat m_originalWidth;
    GLfloat m_originalHeight;
    GLuint m_objectId;

    Texture(const Texture& other) {}
    void operator=(const Texture& other) {}
};

#endif // TEXTURE_H
