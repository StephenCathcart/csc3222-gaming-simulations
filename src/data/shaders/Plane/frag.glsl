#version 420 core

uniform sampler2D colourTex;

in Vertex {
	vec3 normal; 
	vec2 texCoord;
} IN;

void main() {
	vec4 color = vec4(IN.normal, 0.3);
    
    gl_FragColor = color;
}