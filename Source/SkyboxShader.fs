#version 430 core

out vec4 vFragColor;

in VertexData
{
	vec3 texcoord;
} vertexData;

uniform samplerCube tex;

void main()
{
	vFragColor = texture(tex, vertexData.texcoord);
	vFragColor.w = 1;
}