#version 450

#define PI 3.14159265358979323846

uniform float iTime;

in vec2 uv;
out vec4 fragColor;


float fade(float t) { 
	return t * t * t * (t * (t * 6.0 - 15.0) + 10.0); 
}
vec2 smth(vec2 x) {
 return vec2(fade(x.x), fade(x.y)); 
}

vec2 hash(vec2 co) {
    float m = dot(co, vec2(12.9898, 78.233));
    return fract(vec2(sin(m),cos(m))* 43758.5453) * 2. - 1.;
}

float perlinNoise(vec2 uv) {
    vec2 PT  = floor(uv);
    vec2 pt  = fract(uv);
    vec2 mmpt= smth(pt);

    vec4 grads = vec4(
        dot(hash(PT + vec2(.0, 1.)), pt-vec2(.0, 1.)),   dot(hash(PT + vec2(1., 1.)), pt-vec2(1., 1.)),
        dot(hash(PT + vec2(.0, .0)), pt-vec2(.0, .0)),   dot(hash(PT + vec2(1., .0)), pt-vec2(1., 0.))
    );

    return 5.*mix (mix (grads.z, grads.w, mmpt.x), mix (grads.x, grads.y, mmpt.x), mmpt.y);
}

float fbm(vec2 uv) {
    float finalNoise = 0.;
    finalNoise += .50000*perlinNoise(2.*uv);
    finalNoise += .25000*perlinNoise(4.*uv);
    finalNoise += .12500*perlinNoise(8.*uv);
    finalNoise += .06250*perlinNoise(16.*uv);
    finalNoise += .03125*perlinNoise(32.*uv);

    return finalNoise;
}

void main() {

	//float n = snoise((uv+iTime*0.1)/vec2(2024,2024)*10000)*0.7;
	//float n2 = snoise((uv-iTime*0.1)/vec2(2024,2024)*10000)*0.7;
	
	float n = fbm(uv*0.5+iTime*0.1)*0.7;
	float n2 = fbm(uv*0.5-iTime*0.1)*0.7;
	n-=n2;
    fragColor = vec4(mix(vec3(0.094, 0.000, 0.110),vec3(0.902, 0.902, 0.900),n),n);
}
