#include <shaderSource.hpp>


static std::string get_shader_source(const char *filename) {
  std::ifstream in(filename, std::ios::binary);
  if (in) {
    std::string contents;
    in.seekg(0, std::ios::end);
    contents.resize(in.tellg());
    in.seekg(0, std::ios::beg);
    in.read(&contents[0], contents.size());
    in.close();
    return contents;
  }
  throw(errno);
  return nullptr;
}


Shader::Shader(const char *vertex_shader_file, const char *fragment_shader_file){
  std::string vertexShaderCode = get_shader_source(vertex_shader_file);
  std::string fragmentShaderCode = get_shader_source(fragment_shader_file);

  const char *vertexShaderSource = vertexShaderCode.c_str();
  const char *fragmentShaderSource = fragmentShaderCode.c_str();

  GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
  glCompileShader(vertexShader);
  

  GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
  glCompileShader(fragmentShader);

  ID = glCreateProgram();
  glAttachShader(ID, vertexShader);
  glAttachShader(ID, fragmentShader);

  glLinkProgram(ID);

  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);
}

Shader::~Shader(){
  glDeleteProgram(ID);
}

void Shader::activate(){
  glUseProgram(ID);
  return;
}

void Shader::deactivate(){
  glDeleteProgram(ID);
  return;
}
