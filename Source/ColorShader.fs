#version 430 core                                                              

uniform sampler2D tex;                                                         
uniform int Mode;                                                         

out vec4 color;                                                                

in VS_OUT                                                                      
{                                                                              
vec2 texcoord;                                                             
} fs_in;                                                                       

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

}                                                                              