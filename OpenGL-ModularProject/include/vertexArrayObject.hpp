#pragma once
#ifndef VERTEX_ARRAY_OBJ_HPP
#define VERTEX_ARRAY_OBJ_HPP

#include <glad/glad.h>
#include <vertexBufferObject.hpp>

class VertexArrayObject {
public:
  GLuint ID;

  VertexArrayObject();
  void link_vertex_buffer(VertexBufferObject &vbo, GLuint layout);
  void bind();
  void unbind();
  ~VertexArrayObject();

private:

};

#endif
