#version 330 core

layout(location = 0) in vec3 aPos;      // from SFML (vertex position)
layout(location = 1) in vec4 aColor;    // from SFML (vertex color)
layout(location = 2) in vec2 aTexCoord; // from SFML (texture coordinates)

out vec4 vert_pos;
out vec4 vColor;
out vec2 vTexCoord;

uniform mat4 projection;  // auto-set by SFML
uniform mat4 transform;   // auto-set by SFML

void main()
{
    // compute world position
    vert_pos = transform * vec4(aPos, 1.0);

    // final clip position
    gl_Position = projection * vert_pos;

    // forward attributes
    vTexCoord = aTexCoord;
    vColor = aColor;
}
