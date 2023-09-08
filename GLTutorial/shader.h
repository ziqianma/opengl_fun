#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

class Shader {
private:
    std::string _vertexShaderSourceCode;
    std::string _fragmentShaderSourceCode;
    std::vector<std::string> uniforms;
    unsigned int _shaderProgram;
public:
    Shader(const char* vertexShaderPath, const char* fragmentShaderPath);
    void addUniform4f(const std::string& name, float x, float y, float z, float w) const;
    void addUniform1i(const std::string& name, int x) const;
    void addUniform1f(const std::string& name, float x) const;

    unsigned int createShaderProgram();
};