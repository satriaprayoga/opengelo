/*
 * shader.cpp
 *
 *  Created on: Jun 15, 2014
 *      Author: satriaprayoga
 */

#include "shader.h"
#include <stdexcept>
#include <fstream>
#include <string>
#include <cassert>
#include <sstream>

Shader::Shader(const std::string& shaderCode, GLenum shaderType) :
		m_objectId(0), m_count(NULL) {
	m_objectId = glCreateShader(shaderType);
	if (m_objectId == 0)
		throw std::runtime_error("glCreateShader() Failed");
	const char* code = shaderCode.c_str();
	glShaderSource(m_objectId, 1, (const GLchar**) &code, NULL);

	glCompileShader(m_objectId);

	GLint status;
	glGetShaderiv(m_objectId, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE) {
		std::string msg("Compile Shader failure: \n");
		GLint infoLength;
		glGetShaderiv(m_objectId, GL_INFO_LOG_LENGTH, &infoLength);
		char* strInfoLog = new char[infoLength + 1];
		glGetShaderInfoLog(m_objectId, infoLength, NULL, strInfoLog);
		msg += strInfoLog;
		delete[] strInfoLog;

		glDeleteShader(m_objectId);
		m_objectId = 0;
		throw std::runtime_error(msg);
	}
	m_count=new unsigned;
	*m_count=1;

}

Shader::Shader(const Shader& other):m_objectId(other.m_objectId),
		m_count(other.m_count)
{
	retain();

}

Shader& Shader::operator = (const Shader& other){
	release();
	m_objectId=other.m_objectId;
	m_count=other.m_count;
	retain();
	return *this;
}

GLuint Shader::objectId()const{
	return m_objectId;
}

Shader Shader::shaderFromFile(const std::string& filePath, GLenum shaderType){
	std::ifstream f;
	f.open(filePath.c_str(),std::ios::in|std::ios::binary);
	if(!f.is_open()){
		throw std::runtime_error(std::string("Failed to open file: ") + filePath);
	}
	std::stringstream buffer;
	buffer<<f.rdbuf();
	Shader shader(buffer.str(),shaderType);
	return shader;
}

Shader::~Shader() {
	if (m_count)
		release();
}

void Shader::retain() {
	assert(m_count);
	*m_count += 1;
}

void Shader::release() {
	assert(m_count && *m_count > 1);
	*m_count -= 1;
	if (*m_count == 0) {
		glDeleteShader(m_objectId);
		m_objectId = 0;
		delete m_count;
		m_count = NULL;
	}
}

