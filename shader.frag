#version 130
uniform float time;
uniform vec2 mouse;
uniform vec2 resolution;

void main() {
	vec2 st = gl_FragCoord.xy / resolution.xy;
	float pct = 0.0;

	pct = distance(st,mouse);

	vec3 color = vec3(pct);
	color = fract(color * 10 + fract(time * 2));

	gl_FragColor = vec4( color, 1.0 );
}
