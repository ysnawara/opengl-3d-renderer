#version 330 core

out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

uniform vec3 viewPos;
uniform vec3 sunDir;

void main() {
    float lat = TexCoords.y * 3.14159265 - 1.5708;
    float lon = TexCoords.x * 6.28318530;

    float land = 0.0;
    land += step(0.3, sin(lon * 2.0 + 0.5) * cos(lat * 1.5 + 0.3) * 0.5 + 0.5);
    land *= step(-0.6, lat) * step(lat, 1.2);

    float polar = smoothstep(1.1, 1.4, abs(lat));

    vec3 ocean = vec3(0.05, 0.15, 0.45);
    vec3 ground = vec3(0.15, 0.35, 0.12);
    vec3 ice = vec3(0.85, 0.88, 0.92);

    vec3 baseColor = mix(ocean, ground, land);
    baseColor = mix(baseColor, ice, polar);

    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(sunDir);
    float diff = max(dot(norm, lightDir), 0.0);

    vec3 ambient = 0.08 * baseColor;
    vec3 diffuse = diff * baseColor;

    float fresnel = pow(1.0 - max(dot(norm, normalize(viewPos - FragPos)), 0.0), 3.0);
    vec3 atmosphere = vec3(0.3, 0.5, 1.0) * fresnel * 0.25;

    FragColor = vec4(ambient + diffuse + atmosphere, 1.0);
}
