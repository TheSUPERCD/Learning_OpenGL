#include <vertexArrayObject.hpp>

VertexArrayObject::VertexArrayObject() {
  glGenVertexArrays(1, &ID);
}

VertexArrayObject::~VertexArrayObject() {
  glDeleteVertexArrays(1, &ID);
}

void VertexArrayObject::link_vertex_buffer(VertexBufferObject &vbo, GLuint layout){
  vbo.bind();
  glVertexAttribPointer(layout, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
  glEnableVertexAttribArray(layout);
  vbo.unbind();
}

void VertexArrayObject::bind() {
  glBindVertexArray(ID);
}

void VertexArrayObject::unbind() {
  glBindVertexArray(0);
}

