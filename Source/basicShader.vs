// ADS Point lighting Shader
// Vertex Shader
// Richard S. Wright Jr.
// OpenGL SuperBible
#version 430

layout(location = 0) in vec3 vPosition;
layout(location = 1) in vec2 vertexUV;
layout(location = 2) in vec3 vertexNormal;
layout(location = 3) in vec3 vOffset;
layout(location = 4) in vec3 vKd;

vec3 vLightPosition = vec3(0, 20, 50);

uniform mat4 View;
uniform mat4 Projection;
uniform mat4 Model;

// Color to fragment program
out vec3 vVaryingNormal;
out vec3 vVaryingLightDir;
out vec2 UV;
out vec3 Kd;

void main(void) 
{ 
    Kd = vKd;
	mat4 offsetMatrix;
    offsetMatrix[0][0] = 0;
    offsetMatrix[0][1] = 0;
    offsetMatrix[0][2] = 0;
    offsetMatrix[0][3] = 0;
    offsetMatrix[1][0] = 0;
    offsetMatrix[1][1] = 0;
    offsetMatrix[1][2] = 0;
    offsetMatrix[1][3] = 0;
    offsetMatrix[2][0] = 0;
    offsetMatrix[2][1] = 0;
    offsetMatrix[2][2] = 0;
    offsetMatrix[2][3] = 0;
    offsetMatrix[3][0] = 0;
    offsetMatrix[3][1] = 0;
    offsetMatrix[3][2] = 0;
    offsetMatrix[3][3] = 0;
	
    offsetMatrix[0][0] = 1;
    offsetMatrix[1][1] = 1;
    offsetMatrix[2][2] = 1;
    offsetMatrix[3][3] = 1;
    offsetMatrix[3][0] = vOffset.x;
    offsetMatrix[3][1] = vOffset.y;
    offsetMatrix[3][2] = vOffset.z;
	mat4 MVP = Projection*View *offsetMatrix* Model;
	mat4 MV = View*offsetMatrix*Model;
	
    // Get surface normal in eye coordinates
	mat3 normalMatrix = mat3(MV); //normal matrix is MV matrix's 3*3 excluding 'w' 
    vVaryingNormal = normalMatrix * vertexNormal;

    // Get vertex position in eye coordinates
    vec4 vPosition4 = MV * vec4(vPosition, 1);
    vec3 vPosition3 = vPosition4.xyz / vPosition4.w;

    // Get vector to light source
    vVaryingLightDir = normalize(vLightPosition - vPosition3);

	UV = vertexUV;
    // Don't forget to transform the geometry!
    gl_Position = MVP * vec4(vPosition, 1);
}
