#version 430 core

layout(location = 0) in vec3 vertex;

uniform mat4 View;
uniform mat4 Projection;

out VertexData
{
	vec3 texcoord;
} vertexData;

void main()
{
	vec4 position = Projection * View * (vec4(vertex * 1000, 1.0));
	gl_Position = position.xyww;

	vertexData.texcoord = vec3(vertex.x, -vertex.y, -vertex.z);
}
