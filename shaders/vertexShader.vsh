#version 330 core
uniform mat4 mvpMatrix;
in vec4 vertex;
in vec4 color;

out vec4 varyingColor;

void main(void)
{
gl_PointSize = 9;
varyingColor = color;
gl_Position = mvpMatrix * vertex;
}
