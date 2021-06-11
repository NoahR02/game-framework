#version 430 core

layout(location = 0) in vec2 pos;
layout(location = 1) in vec2 texCoord;

uniform mat4 uMVP;

out vec2 vTexCoord;

void main() {
  gl_Position = uMVP * vec4(pos, 0.0f, 1.0f);
  vTexCoord = texCoord;
}