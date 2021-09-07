#version 330 core

layout (location = 0) in vec4 inPos;

uniform mat4 modelMatrix;
uniform mat4 projection;

out vec2 TexCoords;

void main()
{	
    gl_Position = projection * modelMatrix * vec4(inPos.xy, 0.0, 1.0);// 注意乘法要从右向左读
	TexCoords = inPos.zw;
}