#include <windowManager.hpp>

// callback function for dynamically resizing the OpenGL window
static void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
  // set the OpenGL viewport (like in website design)
  glViewport(0, 0, width, height);
}

WindowManager::WindowManager(const int window_width, const int window_height, const char *window_title):
  win_width(window_width), win_height(window_height)
{
  if (!glfwInit()) {
    throw std::runtime_error("Unable to initialize GLFW library...");
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
  window = glfwCreateWindow(window_width, window_height, window_title, nullptr, nullptr);
  if (window == nullptr) {
    glfwTerminate();
    throw std::runtime_error("Unable to create GLFW window...");
  }

  // need to explicitly set OpenGL context
  glfwMakeContextCurrent(window);
  
  // conveniently loads all the OpenGL functions 
  // these functions need to be queried from the GPU driver at runtime
  int OGL_version = gladLoadGL(glfwGetProcAddress);
  if(OGL_version == 0) {
    glfwDestroyWindow(window);
    glfwTerminate();
    throw std::runtime_error("Unable to initialize GLAD...");
  }
  
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
}

WindowManager::~WindowManager() {
  glfwDestroyWindow(window);
  glfwTerminate();
}




