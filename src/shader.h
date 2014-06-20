#ifndef SHADER_H
#define SHADER_H

#include <iostream>
#include <string>
#include<GL/glew.h>

class Shader {
public:
	Shader(const std::string& shaderCode, GLenum shaderType);
	Shader(const Shader& other);
	Shader& operator =(const Shader& other);

	static Shader shaderFromFile(const std::string& filePath, GLenum shaderType);
	GLuint objectId() const;
	virtual ~Shader();
private:
	GLuint m_objectId;
	unsigned* m_count;

	void retain();
	void release();
};


#endif // SHADER_H
