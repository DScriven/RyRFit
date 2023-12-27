#version 430 core
layout (location=0) in vec2 vpos;
out vec4 pcolor;
uniform mat4 transform;
uniform vec4 BoundaryColour;
void main(void)
{
    gl_Position = transform*vec4(vpos,0.0,1.0);
    pcolor = BoundaryColour;
}
