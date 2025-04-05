#pragma once
#ifndef SHADER_SOURCE_HPP
#define SHADER_SOURCE_HPP

#include <glad/gl.h>
#include <string>
#include <fstream>
#include <cerrno>

#ifndef RESOURCES_PATH
#define RESOURCES_PATH
#endif

class Shader {
public:
  GLuint ID;
  Shader(const char *vertex_shader_file, const char *fragment_shader_file);
  void activate();
  void deactivate();
  ~Shader();
private:

};

#endif
