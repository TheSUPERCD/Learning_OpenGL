#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// set default window width and height
static const int window_width = 400;
static const int window_height = 400;

// Vertex Shader source code
const char* vertexShaderSource = "#version 460 core\n"
  "layout (location = 0) in vec3 aPos;\n"
  "void main()\n"
  "{\n"
  "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
  "}\0";

//Fragment Shader source code
const char* fragmentShaderSource = "#version 460 core\n"
  "out vec4 FragColor;\n"
  "void main()\n"
  "{\n"
  "   FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
  "}\n\0";

// callback function for dynamically resizing the OpenGL window
void framebuffer_size_callback(GLFWwindow* window, int width, int height){
  // set the OpenGL viewport (like in website design)
  glViewport(0, 0, width, height);
}

int main (int argc, char *argv[]) {
  if(!glfwInit()){
    std::cerr << "Unable to initialize GLEW...\n";
    return -1;
  }
  
  // requesting OpenGL version 4.6 -- creates either 4.6 or newer context, never older
  // the newest will not have any functions from 4.6 deprecated (otherwise window creation will fail)
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
  // only use the CORE modern OpenGL stuff, none of the old Legacy stuff
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
  // only for MacOS
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
  
  // create the window
  GLFWwindow *window = glfwCreateWindow(window_width, window_height, "OpenGL - Drawing Double Triangles", nullptr, nullptr);
  if(window == nullptr){
    std::cerr << "Unable to create main window...\n";
    glfwTerminate();
    return -2;
  }
  
  // need to explicitly set OpenGL context
  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
  
  // load the GLAD functions that need to be queried from the GPU driver at runtime
  if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
    std::cerr << "Unable to initialize GLAD...\n";
    return -3;
  }
  
  // define triangle vertices
  GLfloat vertices[] = {
    -0.5f, -0.5f,  0.0f,
     0.5f, -0.5f,  0.0f,
     0.0f,  0.25f,  0.0f,
   -0.5f, 0.0f,  0.0f,
    0.5f, 0.0f,  0.0f,
     0.0f,-0.75f,  0.0f
  };

  GLuint indices[] = {
    0, 1, 2,
    3, 4, 5
  };
  
  // create the Vertex Shader
  GLuint vs_id = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vs_id, 1, &vertexShaderSource, nullptr);
  glCompileShader(vs_id);
  
  // create the Fragment Shader
  GLuint fs_id = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fs_id, 1, &fragmentShaderSource, nullptr);
  glCompileShader(fs_id);
  
  // create the final shader program
  GLuint shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vs_id);
  glAttachShader(shaderProgram, fs_id);
  
  // link the compiled shader program
  glLinkProgram(shaderProgram);
  
  // delete the remnant files from the compilation (just to clean up)
  glDeleteShader(vs_id);
  glDeleteShader(fs_id);
  
  // create array of vertexes and the container for them in the GPU
  // and an index array that describes in which order the vertexes should be used
  GLuint vertexArrayObject, vertexBufferObject, elementBufferObject;
  
  glGenVertexArrays(1, &vertexArrayObject);
  glGenBuffers(1, &vertexBufferObject);
  glGenBuffers(1, &elementBufferObject);
  
  // bind them
  glBindVertexArray(vertexArrayObject);
  
  glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
  glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(GLfloat), vertices, GL_STATIC_DRAW);
  
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferObject);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(GLuint), indices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(GLfloat), (void *)0);
  glEnableVertexAttribArray(0);
  
  // unbind them so they're not accidentally bound to something else (not really necessary)
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  
  // need this for wireframe mode
  // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

  // main render loop
  while(!glfwWindowShouldClose(window)){
    glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    glUseProgram(shaderProgram);
    glBindVertexArray(vertexArrayObject);
    
    // gave 6 vertexes to use (need 3 per triangle)
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  
  // delete resources allocated at runtime
  glDeleteVertexArrays(1, &vertexArrayObject);
  glDeleteBuffers(1, &vertexBufferObject);
  glDeleteBuffers(1, &elementBufferObject);
  glDeleteProgram(shaderProgram);

  glfwDestroyWindow(window);
  glfwTerminate();
  return 0;
}
