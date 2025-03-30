#pragma once
#ifndef ELEMENT_BUFFER_OBJ_HPP
#define ELEMENT_BUFFER_OBJ_HPP

#include <glad/glad.h>

class ElementBufferObject {
public:
  GLuint ID;

  ElementBufferObject(GLuint *indices, GLsizeiptr size);
  void bind();
  void unbind();
  ~ElementBufferObject();

private:

};


#endif
