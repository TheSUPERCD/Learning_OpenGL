#include <vertexArrayObject.hpp>

VertexArrayObject::VertexArrayObject() {
  glGenVertexArrays(1, &ID);
}

VertexArrayObject::~VertexArrayObject() {
  glDeleteVertexArrays(1, &ID);
}

void VertexArrayObject::link_vertex_attrib(VertexBufferObject &vbo, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void *offset){
  vbo.bind();
  glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
  glEnableVertexAttribArray(layout);
}

void VertexArrayObject::bind() {
  glBindVertexArray(ID);
}

void VertexArrayObject::unbind() {
  glBindVertexArray(0);
}

