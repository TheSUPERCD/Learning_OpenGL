#version 460 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec3 color;

uniform float scale;

void main(){
  vec3 scaledPos = aPos * scale;
  gl_Position = vec4(scaledPos.x, scaledPos.y, scaledPos.z, 1.0);
  color = aColor;
}
