#pragma once
#ifndef SHADER_SOURCE_HPP
#define SHADER_SOURCE_HPP

#include <glad/gl.h>
#include <string>
#include <fstream>
#include <stdexcept>

#ifndef RESOURCE_DIR
#define RESOURCE_DIR
#endif

class Shader {
public:
  GLuint ID;
  Shader(std::string vertex_shader_file, std::string fragment_shader_file);
  void activate();
  void deactivate();
  void checkCompilationErrors(GLuint shader, std::string shader_type);
  ~Shader();
private:

};

#endif
