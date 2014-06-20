#include "texture.h"
#include <stdexcept>

static GLenum textureFormat(Bitmap::Format format){
    switch(format){
        case Bitmap::Format_Grayscale: return GL_LUMINANCE;
        case Bitmap::Format_GrayscaleAlpha: return GL_LUMINANCE_ALPHA;
        case Bitmap::Format_RGB: return GL_RGB;
        case Bitmap::Format_RGBA: return GL_RGBA;
        default:
            throw std::runtime_error("Unrecognized Format");
    }
}

Texture::Texture(const Bitmap& bitmap,GLint minMagFilter,GLint wrapMode):
m_originalWidth((GLfloat)bitmap.height()),
m_originalHeight((GLfloat)bitmap.width())
{
    glGenTextures(1,&m_objectId);
    glBindTexture(GL_TEXTURE_2D,m_objectId);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,minMagFilter);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,minMagFilter);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,wrapMode);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,wrapMode);
    glTexImage2D(GL_TEXTURE_2D,
        0,
        textureFormat(bitmap.format()),
        (GLsizei)bitmap.width(),
        (GLsizei)bitmap.height(),
        0,
        textureFormat(bitmap.format()),
        GL_UNSIGNED_BYTE,
        bitmap.pixelBuffer());
    glBindTexture(GL_TEXTURE_2D,0);
}

Texture::~Texture()
{
    glDeleteTextures(GL_TEXTURE_2D,&m_objectId);
}

