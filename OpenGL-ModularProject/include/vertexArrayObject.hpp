#pragma once
#ifndef VERTEX_ARRAY_OBJ_HPP
#define VERTEX_ARRAY_OBJ_HPP

#include <glad/gl.h>
#include <vertexBufferObject.hpp>

class VertexArrayObject {
public:
  GLuint ID;

  VertexArrayObject();
  void link_vertex_attrib(VertexBufferObject &vbo, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void *offset);
  void bind();
  void unbind();
  ~VertexArrayObject();

private:

};

#endif
