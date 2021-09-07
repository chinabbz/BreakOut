#version 330 core

layout (location = 0) in vec3 aPos;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projection;

void main()
{
	// 注意乘法要从右向左读
    gl_Position = projection * viewMatrix * modelMatrix * vec4(aPos, 1.0);
}