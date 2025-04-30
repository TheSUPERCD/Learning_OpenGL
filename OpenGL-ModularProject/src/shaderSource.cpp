#include <shaderSource.hpp>


static const std::string get_shader_source(const std::string& source_path) {
  std::ifstream glShaderFile(source_path, std::ios::binary | std::ios::in | std::ios::ate);
  if(!glShaderFile.is_open()){
    throw std::runtime_error(std::string("Unable to open shader source file: ") + source_path);
  }
  
  // enable exceptions
  glShaderFile.exceptions(std::ios::failbit | std::ios::badbit);
  
  std::string file_content;
  size_t file_size = glShaderFile.tellg();
  file_content.resize(file_size);
  glShaderFile.seekg(0, std::ios::beg);
  if(!glShaderFile.read(&file_content[0], file_size)){
    throw std::runtime_error(std::string("Unable to read shader source file: ") + source_path);
  }

  return file_content;
}


Shader::Shader(std::string vertex_shader_file, std::string fragment_shader_file){
  std::string vertexShaderCode = get_shader_source(RESOURCE_DIR + vertex_shader_file);
  std::string fragmentShaderCode = get_shader_source(RESOURCE_DIR + fragment_shader_file);

  const char *vertexShaderSource = vertexShaderCode.c_str();
  const char *fragmentShaderSource = fragmentShaderCode.c_str();

  GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
  glCompileShader(vertexShader);
  checkCompilationErrors(vertexShader, "VERTEX");

  GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
  glCompileShader(fragmentShader);
  checkCompilationErrors(fragmentShader, "FRAGMENT");

  ID = glCreateProgram();
  glAttachShader(ID, vertexShader);
  glAttachShader(ID, fragmentShader);

  glLinkProgram(ID);
  checkCompilationErrors(ID, "PROGRAM");

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

void Shader::checkCompilationErrors(GLuint shader, std::string shader_type){
  GLint compilation_status;
  char compilation_info[1024];
  
  if(shader_type != "PROGRAM") {
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compilation_status);
    if(!compilation_status){
      glGetShaderInfoLog(shader, 1024, nullptr, compilation_info);
      throw std::runtime_error(compilation_info);
    }
  } else {
    glGetProgramiv(shader, GL_LINK_STATUS, &compilation_status);
    if(!compilation_status){
      glGetShaderInfoLog(shader, 1024, nullptr, compilation_info);
      throw std::runtime_error(compilation_info);
    }
  }

  return;
}





