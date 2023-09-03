#version 330 core
layout(location = 0) in vec2 inPosition;
uniform mat4 model;
out vec4 fragColor;

void main()
{
    gl_Position = model * vec4(inPosition, 0.0, 1.0);
    fragColor = vec4(1.0, 1.0, 1.0, 1.0); // Default color (white)
}