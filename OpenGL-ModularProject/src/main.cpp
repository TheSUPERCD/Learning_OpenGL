#include <windowManager.hpp>
#include <shaderSource.hpp>
#include <vertexArrayObject.hpp>
#include <vertexBufferObject.hpp>
#include <elementBufferObject.hpp>
#include <cmath>

// set default window width and height
static const int window_width = 400;
static const int window_height = 400;

int main(int argc, char *argv[]) {
  // create a OpenGL window manager 
  WindowManager win_manager(window_width, window_height, "OpenGL - Drawing Triple Triangles");
  
  // create shaders from glsl source files
  Shader shaderProgram("shaders/default.vert", "shaders/default.frag");
  
  // define triangle vertices
  GLfloat vertices[] = {
    // vertices                                       // colors
    -0.5f,     -0.5f * float(sqrt(3)) / 3,    0.0f,   0.8f, 0.3f, 0.02f,
    0.5f,      -0.5f * float(sqrt(3)) / 3,    0.0f,   0.8f, 0.3f, 0.02f,
    0.0f,      0.5f * float(sqrt(3)) * 2 / 3, 0.0f,   1.0f, 0.6f, 0.32f,
    -0.5f / 2, 0.5f * float(sqrt(3)) / 6,     0.0f,   0.9f, 0.45f, 0.17f,
    0.5f / 2,  0.5f * float(sqrt(3)) / 6,     0.0f,   0.9f, 0.45f, 0.17f,
    0.0f,      -0.5f * float(sqrt(3)) / 3,    0.0f,   0.8f, 0.3f, 0.02f
  };

  GLuint indices[] = {0, 3, 5, 3, 2, 4, 5, 4, 1};
 
  // create array of vertexes and the container for them in the GPU
  // and an index array that describes in which order the vertexes should be used
  VertexArrayObject VAO;
  VAO.bind();

  VertexBufferObject VBO(vertices, 36*sizeof(GLfloat));
  ElementBufferObject EBO(indices, 9*sizeof(GLuint));

  VAO.link_vertex_attrib(VBO, 0, 3, GL_FLOAT, 6*sizeof(GLfloat), (void *)0);
  VAO.link_vertex_attrib(VBO, 1, 3, GL_FLOAT, 6*sizeof(GLfloat), (void *)(3*sizeof(GLfloat)));

  GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");

  // need this for wireframe mode
  // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

  // main render loop
  while (!glfwWindowShouldClose(win_manager.window)) {
    glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    shaderProgram.activate();
    glUniform1f(uniID, 1.0f);
    
    // gave 9 vertexes to use (need 3 per triangle)
    glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);

    glfwSwapBuffers(win_manager.window);
    glfwPollEvents();
  }
  

  return 0;
}
