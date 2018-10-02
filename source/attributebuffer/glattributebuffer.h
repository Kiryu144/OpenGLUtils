/* Created by David Klostermann on 01.10.2018. */
#ifndef GLATTRIBUTEBUFFER_H
#define GLATTRIBUTEBUFFER_H

#include <GLEW/glew.h>
#include <GLM/glm.hpp>
#include <vector>

struct GLAttributeBufferException : public std::exception {
    std::string error;

    GLAttributeBufferException(std::string error){
        this->error = error;
    }

    std::string what(){
        return this->error;
    }
};

template <typename T>
class GLAttributeBuffer {
private:
    GLuint vboID;

    void upload(T* data, size_t lenght){
        glGenBuffers(1, &vboID);
        glBindBuffer(GL_ARRAY_BUFFER, vboID);
        glBufferData(GL_ARRAY_BUFFER, lenght * sizeof(T), data, GL_STATIC_DRAW);
    }
public:
    GLAttributeBuffer(){}

    GLAttributeBuffer(T* data, size_t lenght){
        if(lenght == 0 || data == nullptr){
            throw GLAttributeBufferException("Provided data lenght is zero!");
        }
        upload(data, lenght);
    }

    GLAttributeBuffer(std::vector<T>& data){
        if(data.size() == 0){
            throw GLAttributeBufferException("Provided data lenght is zero!");
        }
        upload(&data.at(0), data.size());
    }

    ~GLAttributeBuffer(){
        if(vboID > 1){
            glDeleteBuffers(1, &vboID);
        }
    }

    void bind(GLuint location){
        glEnableVertexAttribArray(location);
        glBindBuffer(GL_ARRAY_BUFFER, vboID);
        glVertexAttribPointer(location, sizeof(T)/sizeof(float), GL_FLOAT, GL_FALSE, 0, (void *) 0);
    }
};

#endif
