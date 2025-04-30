#pragma once
#ifndef WINDOW_MANAGER_HPP
#define WINDOW_MANAGER_HPP

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <stdexcept>

class WindowManager {
public:
  GLFWwindow *window;
  
  WindowManager(const int window_width, const int window_height, const char *window_title);
  ~WindowManager();

private:
  const int win_width, win_height;
};

#endif
