#version 330 core
out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;

uniform vec3 u_LightPosition;

uniform sampler2D texture_diffuse1;

void main() {
    vec4 textureColor = texture(texture_diffuse1, TexCoords);
    if (textureColor.a < 0.1) {
        discard;
    }

    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * vec3(1.0);

    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(u_LightPosition - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * vec3(1.0);

    vec3 result = (ambient + diffuse) * vec3(1.0);
    FragColor = vec4(result, 1.0) * textureColor;
}
