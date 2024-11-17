#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

uniform mat4 u_MatModel;
uniform mat4 u_MatView;
uniform mat4 u_MatProjection;

out vec3 Normal;
out vec3 FragPos;
out vec2 TexCoords;

void main()
{
    TexCoords = aTexCoords;
    Normal = mat3(transpose(inverse(u_MatModel))) * aNormal;
    FragPos = vec3(u_MatModel * vec4(aPos, 1.0));
    gl_Position = u_MatProjection * u_MatView * u_MatModel * vec4(aPos, 1.0);
}