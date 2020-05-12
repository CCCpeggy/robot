// ADS Point lighting Shader
// Fragment Shader
// Richard S. Wright Jr.
// OpenGL SuperBible
#version 430

out vec4 vFragColor;

//lighting color
vec4    ambientColor = vec4(0.1,0.1,0.1,1);
vec4    diffuseColor = vec4(0.6,0.6,0.7, 1);   
vec4    specularColor = vec4(0.8,0.8, 1, 1);

in vec3 vVaryingNormal;
in vec3 vVaryingLightDir;
in vec2 UV;
in vec3 Kd;
float Shininess = 150.0;//for material specular

void main(void)
{ 
    // Dot product gives us diffuse intensity
    float diff = max(0.0, dot(normalize(vVaryingNormal), normalize(vVaryingLightDir)));

    // Multiply intensity by diffuse color, force alpha to 1.0
    vFragColor = diff * diffuseColor * vec4(Kd, 1);

    // Add in ambient light
    vFragColor += ambientColor;


    // Specular Light
    vec3 vReflection = normalize(reflect(-normalize(vVaryingLightDir), normalize(vVaryingNormal)));//¤Ï®g¨¤
    float spec = max(0.0, dot(normalize(vVaryingNormal), vReflection));
    if(diff != 0) {
        spec = pow(spec, Shininess);
        vFragColor += specularColor * spec * 0.2;
    }
}
    