#version 430 core                                                              

uniform sampler2D tex;
uniform int Mode;
uniform int Time;

out vec4 color;                                                                

in VS_OUT                                                                      
{                                                                              
vec2 texcoord;                                                             
} fs_in;        

float ripple(float dis,float scale,float width,float num,float speed){
    return width*(sin(dis*2.*3.14*num-Time* 0.0001*speed)/(1./scale*dis*2.*3.14*num));
}

void main(void)                                                                
{                                                                              
	vec4 texture_color = texture(tex, fs_in.texcoord);
	if (Mode == 0) {
		color = texture_color;

	}
	else if (Mode == 1) {
		float grayscale_color = 0.299*texture_color.r + 0.587*texture_color.g + 0.114*texture_color.b;
		color = vec4(grayscale_color, grayscale_color, grayscale_color, 1.0);
	}
	else if (Mode == 2) {
		vec2 uv = fs_in.texcoord.xy;
		float dx = 0.01;
		float dy = 0.01;
		vec2 coord = vec2(dx * floor(uv.x / dx + 0.5), dy * floor(uv.y / dy + 0.5));
		color = texture(tex, coord);
	}
    else if (Mode == 3) {
        float kernal[9] = float[](
             0, -1,  0,
            -1,  5, -1,
             0, -1,  0
        );
        float offsetX = 1.0 / 800.0;
        float offsetY = 1.0 / 600.0;

        vec4 col = vec4(0.0);
        col += kernal[0] * texture(tex, fs_in.texcoord.st + vec2(-offsetX, offsetY));
        col += kernal[1] * texture(tex, fs_in.texcoord.st + vec2(0.0f, offsetY));
        col += kernal[2] * texture(tex, fs_in.texcoord.st + vec2(offsetX, offsetY));
        col += kernal[3] * texture(tex, fs_in.texcoord.st + vec2(-offsetX, 0.0f));
        col += kernal[4] * texture(tex, fs_in.texcoord.st + vec2(0.0f, 0.0f));
        col += kernal[5] * texture(tex, fs_in.texcoord.st + vec2(-offsetX, 0.0f));
        col += kernal[6] * texture(tex, fs_in.texcoord.st + vec2(-offsetX, -offsetY));
        col += kernal[7] * texture(tex, fs_in.texcoord.st + vec2(-0.0f, -offsetY));
        col += kernal[8] * texture(tex, fs_in.texcoord.st + vec2(offsetX, -offsetY));

        color = col;
    }
    else if (Mode == 4) {
        float kernal[9] = float[](
            1, 2, 1,
            2, 4, 2,
            1, 2, 1
        );
        float offsetX = 1.0 / 800.0;
        float offsetY = 1.0 / 600.0;

        vec4 col = vec4(0.0);
        col += kernal[0]/16.0 * texture(tex, fs_in.texcoord.st + vec2(-offsetX, offsetY));
        col += kernal[1]/16.0 * texture(tex, fs_in.texcoord.st + vec2(0.0f, offsetY));
        col += kernal[2]/16.0 * texture(tex, fs_in.texcoord.st + vec2(offsetX, offsetY));
        col += kernal[3]/16.0 * texture(tex, fs_in.texcoord.st + vec2(-offsetX, 0.0f));
        col += kernal[4]/16.0 * texture(tex, fs_in.texcoord.st + vec2(0.0f, 0.0f));
        col += kernal[5]/16.0 * texture(tex, fs_in.texcoord.st + vec2(-offsetX, 0.0f));
        col += kernal[6]/16.0 * texture(tex, fs_in.texcoord.st + vec2(-offsetX, -offsetY));
        col += kernal[7]/16.0 * texture(tex, fs_in.texcoord.st + vec2(-0.0f, -offsetY));
        col += kernal[8]/16.0 * texture(tex, fs_in.texcoord.st + vec2(offsetX, -offsetY));

        color = col;
    }
    else if (Mode == 5) {
        color = texture_color;
        vec3 mColor = vec3(1, 1, 1);

        vec2 uv = fs_in.texcoord;
        vec2 center=vec2(0.5,0.5);
        float dis=distance(uv, center) - Time * 0.0001;

        if (dis > 0 && dis< 0.3) {
            float value=ripple(dis,5.,1.6,20.,3.);
            value+=ripple(distance(uv,center-0.2),2.,1.,5.,5.);
            value+=ripple(distance(uv,center+vec2(0.35, 0)),2.,0.5,5.,5.);

            if (value > 0.3) {
                color = vec4(1,1,1,1);
            }
        }
    }
    else if (Mode == 6) {
        vec3 mColor = vec3(1, 0, 0);

        if (texture_color.a < 1) {
            vec2 coord = fs_in.texcoord * 2 - vec2(1, 1);
            float distance = sqrt(coord.x * coord.x + coord.y * coord.y);
            if (/*distance > 0.5 &&*/  (int(abs((distance * 6 + Time * 0.0001)  ))) % 2 == 0) {
                color.xyz = mColor;
            }
            else {
                color.xyz = 1 - mColor;
            }
            color.w = 1;
        }
        else {
            color = texture_color;
        }
    }

}                                                                              