#include "shaderprogram.h"
#include <stdexcept>
#include <glm/gtc/type_ptr.hpp>

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

void ShaderProgram::use()const{
    glUseProgram(m_objectId);
}

bool ShaderProgram::isInUse()const{
    GLint current=0;
    glGetIntegerv(GL_CURRENT_PROGRAM,&current);
    return current==(GLint)m_objectId;
}

void ShaderProgram::stopUsing()const{
    assert(isInUse());
    glUseProgram(0);
}

#define ATTRIB_N_UNIFORM_SETTERS(OGL_TYPE, TYPE_PREFIX, TYPE_SUFFIX) \
\
    void ShaderProgram::setAttrib(const GLchar* name, OGL_TYPE v0) \
        { assert(isInUse()); glVertexAttrib ## TYPE_PREFIX ## 1 ## TYPE_SUFFIX (attribute(name), v0); } \
    void ShaderProgram::setAttrib(const GLchar* name, OGL_TYPE v0, OGL_TYPE v1) \
        { assert(isInUse()); glVertexAttrib ## TYPE_PREFIX ## 2 ## TYPE_SUFFIX (attribute(name), v0, v1); } \
    void ShaderProgram::setAttrib(const GLchar* name, OGL_TYPE v0, OGL_TYPE v1, OGL_TYPE v2) \
        { assert(isInUse()); glVertexAttrib ## TYPE_PREFIX ## 3 ## TYPE_SUFFIX (attribute(name), v0, v1, v2); } \
    void ShaderProgram::setAttrib(const GLchar* name, OGL_TYPE v0, OGL_TYPE v1, OGL_TYPE v2, OGL_TYPE v3) \
        { assert(isInUse()); glVertexAttrib ## TYPE_PREFIX ## 4 ## TYPE_SUFFIX (attribute(name), v0, v1, v2, v3); } \
\
    void ShaderProgram::setAttrib1v(const GLchar* name, const OGL_TYPE* v) \
        { assert(isInUse()); glVertexAttrib ## TYPE_PREFIX ## 1 ## TYPE_SUFFIX ## v (attribute(name), v); } \
    void ShaderProgram::setAttrib2v(const GLchar* name, const OGL_TYPE* v) \
        { assert(isInUse()); glVertexAttrib ## TYPE_PREFIX ## 2 ## TYPE_SUFFIX ## v (attribute(name), v); } \
    void ShaderProgram::setAttrib3v(const GLchar* name, const OGL_TYPE* v) \
        { assert(isInUse()); glVertexAttrib ## TYPE_PREFIX ## 3 ## TYPE_SUFFIX ## v (attribute(name), v); } \
    void ShaderProgram::setAttrib4v(const GLchar* name, const OGL_TYPE* v) \
        { assert(isInUse()); glVertexAttrib ## TYPE_PREFIX ## 4 ## TYPE_SUFFIX ## v (attribute(name), v); } \
\
    void ShaderProgram::setUniform(const GLchar* name, OGL_TYPE v0) \
        { assert(isInUse()); glUniform1 ## TYPE_SUFFIX (uniform(name), v0); } \
    void ShaderProgram::setUniform(const GLchar* name, OGL_TYPE v0, OGL_TYPE v1) \
        { assert(isInUse()); glUniform2 ## TYPE_SUFFIX (uniform(name), v0, v1); } \
    void ShaderProgram::setUniform(const GLchar* name, OGL_TYPE v0, OGL_TYPE v1, OGL_TYPE v2) \
        { assert(isInUse()); glUniform3 ## TYPE_SUFFIX (uniform(name), v0, v1, v2); } \
    void ShaderProgram::setUniform(const GLchar* name, OGL_TYPE v0, OGL_TYPE v1, OGL_TYPE v2, OGL_TYPE v3) \
        { assert(isInUse()); glUniform4 ## TYPE_SUFFIX (uniform(name), v0, v1, v2, v3); } \
\
    void ShaderProgram::setUniform1v(const GLchar* name, const OGL_TYPE* v, GLsizei count) \
        { assert(isInUse()); glUniform1 ## TYPE_SUFFIX ## v (uniform(name), count, v); } \
    void ShaderProgram::setUniform2v(const GLchar* name, const OGL_TYPE* v, GLsizei count) \
        { assert(isInUse()); glUniform2 ## TYPE_SUFFIX ## v (uniform(name), count, v); } \
    void ShaderProgram::setUniform3v(const GLchar* name, const OGL_TYPE* v, GLsizei count) \
        { assert(isInUse()); glUniform3 ## TYPE_SUFFIX ## v (uniform(name), count, v); } \
    void ShaderProgram::setUniform4v(const GLchar* name, const OGL_TYPE* v, GLsizei count) \
        { assert(isInUse()); glUniform4 ## TYPE_SUFFIX ## v (uniform(name), count, v); }

ATTRIB_N_UNIFORM_SETTERS(GLfloat, , f);
ATTRIB_N_UNIFORM_SETTERS(GLdouble, , d);
ATTRIB_N_UNIFORM_SETTERS(GLint, I, i);
ATTRIB_N_UNIFORM_SETTERS(GLuint, I, ui);

void ShaderProgram::setUniformMatrix2(const GLchar* name, const GLfloat* v, GLsizei count, GLboolean transpose) {
    assert(isInUse());
    glUniformMatrix2fv(uniform(name), count, transpose, v);
}

void ShaderProgram::setUniformMatrix3(const GLchar* name, const GLfloat* v, GLsizei count, GLboolean transpose) {
    assert(isInUse());
    glUniformMatrix3fv(uniform(name), count, transpose, v);
}

void ShaderProgram::setUniformMatrix4(const GLchar* name, const GLfloat* v, GLsizei count, GLboolean transpose) {
    assert(isInUse());
    glUniformMatrix4fv(uniform(name), count, transpose, v);
}

void ShaderProgram::setUniform(const GLchar* name, const glm::mat2& m, GLboolean transpose) {
    assert(isInUse());
    glUniformMatrix2fv(uniform(name), 1, transpose, glm::value_ptr(m));
}

void ShaderProgram::setUniform(const GLchar* name, const glm::mat3& m, GLboolean transpose) {
    assert(isInUse());
    glUniformMatrix3fv(uniform(name), 1, transpose, glm::value_ptr(m));
}

void ShaderProgram::setUniform(const GLchar* name, const glm::mat4& m, GLboolean transpose) {
    assert(isInUse());
    glUniformMatrix4fv(uniform(name), 1, transpose, glm::value_ptr(m));
}

void ShaderProgram::setUniform(const GLchar* uniformName, const glm::vec3& v) {
    setUniform3v(uniformName, glm::value_ptr(v));
}

void ShaderProgram::setUniform(const GLchar* uniformName, const glm::vec4& v) {
    setUniform4v(uniformName, glm::value_ptr(v));
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
	GLint uniform = glGetUniformLocation(m_objectId, uniformName);
	if (uniform == -1)
		throw std::runtime_error(std::string("uniform not found: ") + uniformName);
	return uniform;
}

ShaderProgram::~ShaderProgram() {
	if (m_objectId != 0)
		glDeleteProgram(m_objectId);
}

