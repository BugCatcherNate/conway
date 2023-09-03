#version 330 core
in vec4 fragColor;
out vec4 FragColor;
uniform vec4 color; // Color uniform

void main()
{
    FragColor = color; // Use the color uniform
}
