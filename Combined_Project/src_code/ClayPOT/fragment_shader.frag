#version 330 core

in vec4 vert_pos;
in vec4 vColor;
in vec2 vTexCoord;

out vec4 FragColor;

uniform sampler2D texture0;  // bound by SFML
uniform bool hasTexture;
uniform vec2 lightPos;

void main()
{
    // ambient light
    vec4 ambient = vec4(0.02, 0.02, 0.5, 1.0);

    // vector from light to fragment (in world coords)
    vec2 lightToFrag = lightPos - vert_pos.xy;
    lightToFrag.y = lightToFrag.y / 1.7;

    // distance
    float vecLength = clamp(length(lightToFrag) * 2, 0.0, 1.0);

    // sample texture
    vec4 pixel = texture(texture0, vTexCoord);

    // lighting
    if (hasTexture)
        FragColor = vColor * pixel * clamp(ambient + vec4(1.0 - vecLength), 0.0, 1.0);
    else
        FragColor = vColor;
}
