#version 130
uniform float u_time;
uniform vec2 u_mouse;
uniform vec2 u_resolution;

void main() {
  vec2 st = gl_FragCoord.xy / u_resolution.xy;
  float pct = 0.0;

  pct = distance(fract(st * 5), vec2(0.5));

  vec3 color = vec3(pct);
  color = fract(color * 10 + fract(u_time));

  gl_FragColor = vec4( color, 1.0 );
}
