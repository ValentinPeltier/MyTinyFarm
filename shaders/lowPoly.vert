#version 450

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 color;
layout(location = 2) in vec3 normal;

layout(location = 0) out vec3 fragColor;

layout(set = 0, binding = 0) uniform GlobalUbo {
    mat4 projection;
    mat4 view;
} ubo;

layout(push_constant) uniform Push {
    mat4 modelMatrix;
} push;

const vec3 LIGHT_DIRECTION = normalize(vec3(1.0, -3.0, -1.0));
const float AMBIENT = 0.02;

void main() {
    // Position
    vec4 worldPosition = push.modelMatrix * vec4(position, 1.0);
    gl_Position = ubo.projection * ubo.view * worldPosition;

    // Color
    vec3 normalWorldSpace = normalize(mat3(push.modelMatrix) * normal);
    float lightIntensity = AMBIENT + max(dot(normalWorldSpace, LIGHT_DIRECTION), 0);
    fragColor = lightIntensity * color;
}
