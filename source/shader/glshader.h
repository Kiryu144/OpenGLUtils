/* Created by David Klostermann on 01.10.2018. */
#ifndef GLSHADER_H
#define GLSHADER_H

#include <GLEW/glew.h>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <streambuf>
#include <map>

#include <GLM/common.hpp>
#include <GLM/matrix.hpp>

struct GLShaderException : public std::exception {
    std::string error;

    GLShaderException(std::string error){
        this->error = error;

    }

    std::string what(){
        return this->error;
    }
};

class GLShader {
private:
    GLuint program;
    std::map<std::string, GLuint> uniformLocations;

    void readFile(const char* filename, std::string& buffer);
    void cacheShaderInformation();
public:
    GLShader();
    GLShader(const char* vertexFilePath, const char* fragmentFilePath, const char* geometryFilePath);
    GLShader(const char* vertexFilePath, const char* fragmentFilePath);
    ~GLShader();

    void parseShaders(const char* vertexFilePath, const char* fragmentFilePath, const char* geometryFilePath);
    void parseShaders(const char* vertexFilePath, const char* fragmentFilePath);

    GLuint compileShader(const char* shaderData, GLuint type);

    GLuint linkShader(GLuint vertex, GLuint fragment, GLuint geometry);
    GLuint linkShader(GLuint vertex, GLuint fragment);

    GLuint getProgramID() const;

    GLint getCachedUniformLocation(const char* uniform) const;

    void setUniform(const char* uniform, GLint value) const;
    void setUniform(const char* uniform, GLuint value) const;
    void setUniform(const char* uniform, GLfloat value) const;
    void setUniform(const char* uniform, GLdouble value) const;

    void setUniform(const char* uniform, glm::vec2 value) const;
    void setUniform(const char* uniform, glm::vec3 value) const;
    void setUniform(const char* uniform, glm::vec4 value) const;
    void setUniform(const char* uniform, glm::mat4x4 value) const;

    bool operator<(const GLShader& other) const;
};

#endif
