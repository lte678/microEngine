#version 330 core

layout (location = 0) out vec4 color;


uniform sampler2D textures[32];

in DATA {
	vec4 position;
	vec4 color;
	float tid;
	vec2 texcoord;
} fs_in;




void main() {

	vec4 texColor = fs_in.color;
	if(fs_in.tid > 0.0) {
		int tid = int(fs_in.tid - 0.5);
		texColor = fs_in.color * texture(textures[tid], fs_in.texcoord);
	}

	color = texColor;
}