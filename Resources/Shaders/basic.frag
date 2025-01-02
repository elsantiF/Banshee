#version 330 core
out vec4 FragColor;

in vec3 FragPos;
in vec2 TexCoords;
in vec3 TangentLightPos;
in vec3 TangentViewPos;
in vec3 TangentFragPos;

uniform sampler2D texture_diffuse;
uniform sampler2D texture_normal;
uniform vec3 u_LightPosition;

void main() {
    vec3 normal = texture(texture_normal, TexCoords).rgb;
    normal = normalize(normal * 2.0 - 1.0);

    vec4 textureColor = texture(texture_diffuse, TexCoords);
    if (textureColor.a < 0.1) {
        discard;
    }

    vec3 color = textureColor.rgb;

    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * color;

    vec3 lightDir = normalize(TangentLightPos - TangentFragPos);
    float diff = max(dot(lightDir, normal), 0.0);
    vec3 diffuse = diff * color;

    vec3 viewDir = normalize(TangentViewPos - TangentFragPos);
    vec3 reflectDir = reflect(-lightDir, normal);
    vec3 halfwayDir = normalize(lightDir + viewDir);
    float spec = pow(max(dot(normal, halfwayDir), 0.0), 32.0);
    vec3 specular = vec3(0.2) * spec;

    FragColor = vec4(ambient + diffuse + specular, 1.0);
}
