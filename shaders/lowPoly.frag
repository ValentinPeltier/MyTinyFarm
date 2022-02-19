#version 450

layout (location = 0) in vec3 fragColor;

layout (location = 0) out vec4 outColor;

layout(set = 0, binding = 0) uniform GlobalUbo {
  mat4 projection;
  mat4 view;
} ubo;

layout(push_constant) uniform Push {
  mat4 modelMatrix;
} push;

void main() {
  vec3 diffuseLight = vec3(.02, .02, .02);
  
  outColor = vec4(diffuseLight * fragColor, 1.0);
}
