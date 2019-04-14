#version 130
in vec4 color_out;
in vec4 pos_out;
uniform float time;

void main() {
  vec2 pos = pos_out.xy;
  vec4 new_col = vec4(sin(pos.x + time), sin(time), sin(pos.y + time), 1.0);
  gl_FragColor = new_col;
}
