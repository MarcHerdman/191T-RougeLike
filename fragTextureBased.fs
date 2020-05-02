#version 450

uniform float iTime;
uniform sampler2D iTex;
in vec2 uv;
out vec4 fragColor;

void main() {
	vec4 n = texture(iTex,uv+iTime*0.1);
	vec4 n2 = texture(iTex,uv.yx-iTime*0.1);
	n-=n2;
	vec4 m =  mix(vec4(0.05,0.0,0.15,n),vec4(0.9,0.9,0.9,n),n);
	int steps = 10;
    fragColor = floor(m * steps)/steps;
}
