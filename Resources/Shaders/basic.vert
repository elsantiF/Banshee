#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;
layout (location = 3) in vec3 aTangent;
layout (location = 4) in vec3 aBitangent;

uniform mat4 u_MatModel;
uniform mat4 u_MatView;
uniform mat4 u_MatProjection;

uniform vec3 u_LightPosition;

out vec3 FragPos;
out vec2 TexCoords;
out vec3 TangentLightPos;
out vec3 TangentViewPos;
out vec3 TangentFragPos;

void main() {
    FragPos = vec3(u_MatModel * vec4(aPos, 1.0));
    TexCoords = aTexCoords;

    mat3 normalMatrix = transpose(inverse(mat3(u_MatModel)));
    vec3 T = normalize(normalMatrix * aTangent);
    vec3 N = normalize(normalMatrix * aNormal);
    T = normalize(T - dot(T, N) * N);
    vec3 B = cross(N, T);

    mat3 TBN = transpose(mat3(T, B, N));
    TangentLightPos = TBN * u_LightPosition;
    TangentViewPos = TBN * vec3(0.0, 0.0, 0.0);
    TangentFragPos = TBN * FragPos;

    gl_Position = u_MatProjection * u_MatView * u_MatModel * vec4(aPos, 1.0);
}
