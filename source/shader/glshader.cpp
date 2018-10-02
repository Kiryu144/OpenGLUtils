/* Created by David Klostermann on 01.10.2018. */
#include "GLShader.h"

GLShader::GLShader() {
    /* pass */
}

GLShader::GLShader(const char *vertexFilePath, const char *fragmentFilePath, const char *geometryFilePath) {
    parseShaders(vertexFilePath, fragmentFilePath, geometryFilePath);
}

GLShader::GLShader(const char *vertexFilePath, const char *fragmentFilePath) {
    parseShaders(vertexFilePath, fragmentFilePath, nullptr);
}

GLShader::~GLShader() {
    glDeleteProgram(program);
}

void GLShader::readFile(const char* filename, std::string& buffer) {
    std::ifstream fstream(filename);
    if(fstream.fail()){
        throw std::ifstream::failure("Could not read file!");
    }
    buffer.insert(buffer.begin(), std::istreambuf_iterator<char>(fstream), std::istreambuf_iterator<char>());
}

void GLShader::cacheShaderInformation() {
    GLint amount;
    glGetProgramiv(program, GL_ACTIVE_UNIFORMS, &amount);

    for(GLuint i = 0; i < amount; i++){
        char* name = new char[16];
        GLsizei lenght;
        GLint size;
        GLenum type;
        glGetActiveUniform(program, i, 16, &lenght, &size, &type, name);
        uniformLocations.insert(std::pair<std::string, GLuint>(std::string(name), i));
    }
}

void GLShader::parseShaders(const char *vertexFilePath, const char *fragmentFilePath, const char *geometryFilePath) {
    GLuint vertexShaderID = 0, fragmentShaderID = 0, geometryShaderID = 0;

    bool successReadingFiles = true;
    try{
        if(vertexFilePath != nullptr){
            std::string vertexShader;
            readFile(vertexFilePath, vertexShader);
            vertexShaderID = compileShader(vertexShader.c_str(), GL_VERTEX_SHADER);
        }
        if(fragmentFilePath != nullptr){
            std::string fragmentShader;
            readFile(fragmentFilePath, fragmentShader);
            fragmentShaderID = compileShader(fragmentShader.c_str(), GL_FRAGMENT_SHADER);
        }
        if(geometryFilePath != nullptr){
            std::string geometryShader;
            readFile(geometryFilePath, geometryShader);
            geometryShaderID = compileShader(geometryShader.c_str(), GL_GEOMETRY_SHADER);
        }
    }catch(std::ifstream::failure& exception){
        glDeleteShader(vertexShaderID);
        glDeleteShader(fragmentShaderID);
        throw GLShaderException("One or more files could not be read!");
    }

    program = linkShader(vertexShaderID, fragmentShaderID, geometryShaderID);
    glDeleteShader(vertexShaderID);
    glDeleteShader(fragmentShaderID);
    glDeleteShader(geometryShaderID);
    cacheShaderInformation();
}

void GLShader::parseShaders(const char *vertexFilePath, const char *fragmentFilePath) {
    parseShaders(vertexFilePath, fragmentFilePath, nullptr);
}

GLuint GLShader::compileShader(const char *shaderData, GLuint type) {
    GLuint shaderID = glCreateShader(type);

    glShaderSource(shaderID, 1, &shaderData, nullptr);
    glCompileShader(shaderID);

    GLint success = GL_FALSE;
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
    if(success == GL_FALSE){
        GLint logLenght = 0;
        char* log;

        glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &logLenght);
        log = new char[logLenght];
        glGetShaderInfoLog(shaderID, logLenght, &logLenght, &log[0]);
        glDeleteShader(shaderID);

        std::string shaderType;
        switch(type){
            case GL_VERTEX_SHADER: shaderType = "GL_VERTEX_SHADER"; break;
            case GL_FRAGMENT_SHADER: shaderType = "GL_FRAGMENT_SHADER"; break;
            case GL_GEOMETRY_SHADER: shaderType = "GL_GEOMETRY_SHADER"; break;
            default: shaderType = "UNKNOWN"; break;
        }

        throw(GLShaderException("Could not compile " + shaderType + "\n" + std::string(log)));
    }

    return shaderID;
}

GLuint GLShader::linkShader(GLuint vertex, GLuint fragment, GLuint geometry) {
    GLuint programID = glCreateProgram();

    if(vertex != 0){
        glAttachShader(programID, vertex);
    }

    if(fragment != 0){
        glAttachShader(programID, fragment);
    }

    if(geometry != 0){
        glAttachShader(programID, geometry);
    }

    glLinkProgram(programID);

    GLint isLinked = 0;
    glGetProgramiv(programID, GL_LINK_STATUS, &isLinked);
    if(isLinked == GL_FALSE){
        GLint logLenght;
        std::string log;

        glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &logLenght);
        log.reserve(logLenght);
        glGetProgramInfoLog(programID, logLenght, &logLenght, &log[0]);
        glDeleteProgram(programID);

        throw(GLShaderException("Could not link shaders!\n" + std::string(log)));
    }

    glDetachShader(programID, vertex);
    glDetachShader(programID, fragment);
    glDetachShader(programID, geometry);

    return programID;
}

GLuint GLShader::linkShader(GLuint vertex, GLuint fragment) {
    linkShader(vertex, fragment, 0);
}

GLint GLShader::getCachedUniformLocation(const char *uniform) const {
    try{
        return uniformLocations.at(uniform);
    }catch(...){
        throw GLShaderException("Unknown uniform!");
    }
}

void GLShader::setUniform(const char *uniform, GLint value) const {
    glUniform1i(getCachedUniformLocation(uniform), value);
}

void GLShader::setUniform(const char *uniform, GLuint value) const {
    glUniform1i(getCachedUniformLocation(uniform), value);
}

void GLShader::setUniform(const char *uniform, GLfloat value) const {
    glUniform1f(getCachedUniformLocation(uniform), value);
}

void GLShader::setUniform(const char *uniform, GLdouble value) const {
    glUniform1d(getCachedUniformLocation(uniform), value);
}

void GLShader::setUniform(const char *uniform, glm::vec2 value) const {
    glUniform2f(getCachedUniformLocation(uniform), value.x, value.y);
}

void GLShader::setUniform(const char *uniform, glm::vec3 value) const {
    glUniform3f(getCachedUniformLocation(uniform), value.x, value.y, value.z);
}

void GLShader::setUniform(const char *uniform, glm::vec4 value) const {
    glUniform4f(getCachedUniformLocation(uniform), value.x, value.y, value.z, value.w);
}

void GLShader::setUniform(const char *uniform, glm::mat4x4 value) const {
    glUniformMatrix4fv(getCachedUniformLocation(uniform), 1, GL_FALSE, &value[0][0]);
}

GLuint GLShader::getProgramID() const {
    return program;
}

bool GLShader::operator<(const GLShader &other) const {
    return other.getProgramID() < getProgramID();
}

void GLShader::bind() {
    glUseProgram(program);
}


