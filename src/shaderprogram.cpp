/*
 * shaderprogram.cpp
 *
 *  Created on: Jun 15, 2014
 *      Author: satriaprayoga
 */

#include "shaderprogram.h"
#include <stdexcept>

ShaderProgram::ShaderProgram(const std::vector<Shader>& shaders) :
		m_objectId(0) {
	if (shaders.size() <= 0)
		throw std::runtime_error("No shaders provided!");
	m_objectId = glCreateProgram();
	if (m_objectId == 0)
		throw std::runtime_error("Failed to create program");

	for (unsigned int i = 0; i < shaders.size(); i++)
		glAttachShader(m_objectId, shaders[i].objectId());

	glLinkProgram(m_objectId);

	for (unsigned int i = 0; i < shaders.size(); i++)
		glDetachShader(m_objectId, shaders[i].objectId());

	GLint status;
	glGetProgramiv(m_objectId, GL_LINK_STATUS, &status);
	if (status == GL_FALSE) {
		std::string msg("Program linking failure: ");

		GLint infoLogLength;
		glGetProgramiv(m_objectId, GL_INFO_LOG_LENGTH, &infoLogLength);
		char* strInfoLog = new char[infoLogLength + 1];
		glGetProgramInfoLog(m_objectId, infoLogLength, NULL, strInfoLog);
		msg += strInfoLog;
		delete[] strInfoLog;

		glDeleteProgram(m_objectId);
		m_objectId = 0;
		throw std::runtime_error(msg);
	}

}

GLuint ShaderProgram::objectId() const {
	return m_objectId;
}

GLuint ShaderProgram::attribute(const GLchar * attributeName) const {
	if (!attributeName)
		throw std::runtime_error("attribute Name was NULL");
	GLint attr = glGetAttribLocation(m_objectId, attributeName);
	if (attr == -1)
		throw std::runtime_error(std::string("attribute not found: ") + attributeName);
	return attr;
}

GLuint ShaderProgram::uniform(const GLchar* uniformName) const {
	if (!uniformName)
		throw std::runtime_error("uniform Name was NULL");
	GLint uniform = glGetAttribLocation(m_objectId, uniformName);
	if (uniform == -1)
		throw std::runtime_error(std::string("uniform not found: ") + uniformName);
	return uniform;
}

ShaderProgram::~ShaderProgram() {
	if (m_objectId != 0)
		glDeleteProgram(m_objectId);
}

