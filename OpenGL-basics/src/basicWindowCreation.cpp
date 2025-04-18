#include <iostream>
#include <GLFW/glfw3.h>

int main (int argc, char *argv[]) {
  if(!glfwInit()){
    std::cerr << "Could not initialize GLFW...\n";
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
  GLFWwindow *window = glfwCreateWindow(800, 800, "Basic OpenGL Window", nullptr, nullptr);
  if(window == nullptr){
    std::cerr << "Could not create window...\n";
    glfwTerminate();
    return -2;
  }
  glfwMakeContextCurrent(window); // need to explicitly set OpenGL context
  
  // main render loop
  while(!glfwWindowShouldClose(window)){
    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  
  // delete resources allocated at runtime
  glfwDestroyWindow(window);
  glfwTerminate();
  return 0;
}
