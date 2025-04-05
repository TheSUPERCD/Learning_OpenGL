#include <iostream>
#include <cmath>
#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include <shaderSource.hpp>
#include <vertexArrayObject.hpp>
#include <vertexBufferObject.hpp>
#include <elementBufferObject.hpp>

// set default window width and height
static const int window_width = 400;
static const int window_height = 400;

// callback function for dynamically resizing the OpenGL window
void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
  // set the OpenGL viewport (like in website design)
  glViewport(0, 0, width, height);
}

int main(int argc, char *argv[]) {
  if (!glfwInit()) {
    std::cerr << "Unable to initialize GLEW...\n";
    return -1;
  }

  // requesting OpenGL version 4.6 -- creates either 4.6 or newer context, never
  // older the newest will not have any functions from 4.6 deprecated (otherwise
  // window creation will fail)
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
  // only use the CORE modern OpenGL stuff, none of the old Legacy stuff
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
  // only for MacOS
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

  // create the window
  GLFWwindow *window = glfwCreateWindow(window_width, window_height, "OpenGL - Drawing Triple Triangles", nullptr, nullptr);
  if (window == nullptr) {
    std::cerr << "Unable to create main window...\n";
    glfwTerminate();
    return -2;
  }

  // need to explicitly set OpenGL context
  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  // load the GLAD functions that need to be queried from the GPU driver at
  // runtime
  int OGL_version = gladLoadGL(glfwGetProcAddress);
  if(OGL_version == 0){
    std::cerr << "Unable to initialize GLAD...\n";
    return -3;
  } else {
    std::cout << "DEBUG: GLAD successfully initialized for OpenGL version" 
      << GLAD_VERSION_MAJOR(OGL_version) << "." 
      << GLAD_VERSION_MINOR(OGL_version) << std::endl;
  }

  // define triangle vertices
  GLfloat vertices[] = {
      -0.5f,     -0.5f * float(sqrt(3)) / 3,    0.0f, // Lower left corner
      0.5f,      -0.5f * float(sqrt(3)) / 3,    0.0f, // Lower right corner
      0.0f,      0.5f * float(sqrt(3)) * 2 / 3, 0.0f, // Upper corner
      -0.5f / 2, 0.5f * float(sqrt(3)) / 6,     0.0f, // Inner left
      0.5f / 2,  0.5f * float(sqrt(3)) / 6,     0.0f, // Inner right
      0.0f,      -0.5f * float(sqrt(3)) / 3,    0.0f  // Inner down
  };

  GLuint indices[] = {0, 3, 5, 3, 2, 4, 5, 4, 1};

  Shader shaderProgram(RESOURCES_PATH"shaders/default.vert", RESOURCES_PATH"shaders/default.frag");
 
  // create array of vertexes and the container for them in the GPU
  // and an index array that describes in which order the vertexes should be used
  VertexArrayObject VAO;
  VAO.bind();

  VertexBufferObject VBO(vertices, 18*sizeof(GLfloat));
  ElementBufferObject EBO(indices, 9*sizeof(GLuint));

  VAO.link_vertex_buffer(VBO, 0);

  VAO.unbind();
  VBO.unbind();
  EBO.unbind();

  // need this for wireframe mode
  // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

  // main render loop
  while (!glfwWindowShouldClose(window)) {
    glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    shaderProgram.activate();
    VAO.bind();
    
    // gave 9 vertexes to use (need 3 per triangle)
    glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  // delete resources allocated at runtime
  glfwDestroyWindow(window);
  glfwTerminate();
  return 0;
}
