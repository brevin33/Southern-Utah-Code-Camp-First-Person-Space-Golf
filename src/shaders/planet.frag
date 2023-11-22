#version 450

layout(location = 0) in vec3 fragColor;
layout(location = 1) in vec3 fragPos;
layout(location = 2) in vec3 fragNormal;
layout(location = 3) in vec3 lightPos;

layout(location = 0) out vec4 outColor;


void main() {
    float ambLight = 1.0f;
    float diffuseLight = dot(normalize(fragNormal),normalize(fragPos-lightPos));
    diffuseLight = diffuseLight * 1.6;
    diffuseLight = diffuseLight * (1/(distance(fragPos,lightPos)*0.1f));
    float light = max(min(diffuseLight * 0.4f,1),0);
    outColor = vec4(fragColor * light,1.0f);
}