#version 330 core

layout (location = 0) out vec4 color;

uniform vec4 color_in;
uniform vec2 light_pos;

uniform sampler2D tex;

in DATA {
	vec4 position;
	vec4 color;
	vec2 texcoord;
} fs_in;

void main() {
	float intensity = 1.0 / length(fs_in.position.xy - light_pos);
	vec4 lit = fs_in.color * intensity;
	vec4 sampled = texture(tex, fs_in.texcoord);
	float alpha = (1.0 - sampled.x) + (1.0 - sampled.y) + (1.0 - sampled.z) / 3.0;
	color = vec4(lit.xyz, alpha) * alpha;
}