// ADS Point lighting Shader
// Fragment Shader
// Richard S. Wright Jr.
// OpenGL SuperBible
#version 430

uniform int Mode;
uniform vec3 Eye;
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
uniform sampler2D tex;

vec2 matcap(vec3 eye, vec3 normal) {
  vec3 reflected = reflect(eye, normal);
  float m = 2.8284271247461903 * sqrt( reflected.z+1.0 );
  return reflected.xy / m + 0.5;
}

void main(void)
{ 
    if (Mode == 1) {
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
    else if (Mode == 2) {
        vec4 color1;
        color1.rgb = Kd;
        color1.a = 1;
        vec4 color2;

        float intensity = dot(normalize(vVaryingLightDir), vVaryingNormal);

        if (intensity > 0.95)      color2 = vec4(1.0, 1.0, 1.0, 1.0);
        else if (intensity > 0.75) color2 = vec4(0.8, 0.8, 0.8, 1.0);
        else if (intensity > 0.50) color2 = vec4(0.6, 0.6, 0.6, 1.0);
        else if (intensity > 0.25) color2 = vec4(0.4, 0.4, 0.4, 1.0);
        else                       color2 = vec4(0.2, 0.2, 0.2, 1.0);

        vFragColor = color1 * color2;
    }
    else if (Mode == 3) {
        vFragColor.xyz = vVaryingNormal;
        vFragColor.w = 1;
    }
    else if (Mode == 4) {
       vec3 eye = normalize(Eye);
       eye.z -= 1.4;
       eye.x += 1,4;
       vec2 uv = matcap(normalize(eye), normalize(vVaryingNormal)).xy;
       vFragColor = vec4(
          texture(tex, uv).rgb,
          1.0
        );
    }
    else {
        vFragColor = vec4(1,1,1,1);
    }
}
    