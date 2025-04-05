#pragma once
#ifndef VERTEX_BUFFER_OBJ_HPP
#define VERTEX_BUFFER_OBJ_HPP

#include <glad/gl.h>

class VertexBufferObject {
public:
  GLuint ID;

  VertexBufferObject(GLfloat *vertices, GLsizeiptr size);
  void bind();
  void unbind();
  ~VertexBufferObject();

private:

};


#endif
