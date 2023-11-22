#version 450

layout(binding = 0) uniform UniformBufferObject {
    mat4 model;
    mat4 view;
    mat4 proj;
    vec3 color;
    vec3 playerPos;
} ubo;

layout(location = 0) in vec3 inPosition;


layout(location = 0) out vec3 fragColor;
layout(location = 1) out vec3 fragPos;
layout(location = 2) out vec3 fragNormal;
layout(location = 3) out vec3 lightPos;


void main() {   
    vec4 p = ubo.proj * ubo.view * ubo.model * vec4(inPosition, 1.0);
    gl_Position = ubo.proj * ubo.view * ubo.model * vec4(inPosition, 1.0);
    fragColor = ubo.color;
    fragPos = vec3(ubo.model * vec4(inPosition,1.0));
    fragNormal = inPosition;
    lightPos = ubo.playerPos;
}