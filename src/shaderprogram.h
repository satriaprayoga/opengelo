/*
 * shaderprogram.h
 *
 *  Created on: Jun 15, 2014
 *      Author: satriaprayoga
 */

#ifndef SHADERPROGRAM_H_
#define SHADERPROGRAM_H_

#include <vector>
#include "shader.h"

class ShaderProgram {
public:
	ShaderProgram(const std::vector<Shader>& shaders);
	GLuint objectId()const;
	GLuint attribute(const GLchar* attributeName)const;
	GLuint uniform(const GLchar* uniformName)const;
	virtual ~ShaderProgram();
private:
	GLuint m_objectId;

	//disable copy
	ShaderProgram(const ShaderProgram&):m_objectId(0){}
	void operator=(const ShaderProgram&){}
};

#endif /* SHADERPROGRAM_H_ */
