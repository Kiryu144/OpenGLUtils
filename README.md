# OpenGLUtils
### GLShader
Parses GLSL shader files from your system, compiles and links them together. 
Currently there is only support for vertex, fragment and geometry shaders.

The GLShader object represents the Program in the GPU, **so if it's deconstructor is called, the program is removed from the GPU!**

```C++
try{
    GLShader* shader = new GLShader("./compile_test.vert", "./compile_test.frag", "./compile_test.geom");
    shader->bind();
    shader->setUniform("model", model);
}catch(GLShaderException& exception){
    std::cerr << exception.what() << std::endl;
}
```

## GLAttributeBuffer<>

Uploads attribute data to the GPU.

The GLAttributeBuffer object represents the Data in the GPU, **so if it's deconstructor is called, the data is removed from the GPU!**

```C++
try{
    glm::vec3* vertices = new glm::vec3[6];
    vertices[0] = glm::vec3(0, 1, 0);
    vertices[1] = glm::vec3(0, 1, 1);
    vertices[2] = glm::vec3(1, 0, 0);
    vertices[3] = glm::vec3(0, 1, 1);
    vertices[4] = glm::vec3(1, 1, 0);
    vertices[5] = glm::vec3(0, 1, 0);

    std::vector<glm::vec4> colors;
    colors.push_back(glm::vec4(1.0, 0.0, 0.25, 0.5f));
    colors.push_back(glm::vec4(1.0, 0.0, 0.25, 0.5f));
    colors.push_back(glm::vec4(1.0, 1.0, 0.25, 0.5f));
    colors.push_back(glm::vec4(1.0, 0.0, 0.25, 0.5f));
    colors.push_back(glm::vec4(1.0, 0.2, 0.5, 0.5f));
    colors.push_back(glm::vec4(1.0, 0.0, 0.25, 0.5f));

    GLAttributeBuffer<glm::vec3> verticeBuffer1(vertices, 6);
    GLAttributeBuffer<glm::vec4> verticeBuffer2(colors);
}catch(GLAttributeBufferException& exception){
    std::cerr << exception.what() << std::endl;
}
```

## GLTexture
Uploads texture data to the GPU.

The GLTexture object represents the Data in the GPU, **so if it's deconstructor is called, the data is removed from the GPU!**

```C++
try{
    GLTexture* texture1 = new GLTexture("./image1.png");
    GLTexture* texture2 = new GLTexture("./image2.png");
}catch(GLTextureException error){
    std::cerr << error.what() << std::endl;
}
```

## Transform2D
Holds the position, rotation & size.
Is useful for getting the model matrix for opengl

```C++
//transform2D(glm::vec2 position, float rotation (normalized), glm::vec2 size)
Transform2D transform2D(glm::vec2(300, 300), 0.25, glm::vec2(100, 100));
transform.setOrigin(glm::vec2(0.5f, 0.5f)); //Sets the origin exactly in the center
transform.getMatrix(); //Gets the model matrix
```
