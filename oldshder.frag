#version 130
uniform float time;
uniform vec2 mouse;
uniform vec2 resolution;

void main() {
  vec2 pos_out = gl_FragCoord.xy / resolution.xy;
  vec4 new_col;
  new_col.x = mouse.x;
  new_col.y = abs(sin(time));
  new_col.z = mouse.y;
  new_col.w = 1; 
  float d = 1- dot(pos_out, pos_out);
  float x_fract = fract(sin(time) + pos_out.x * floor(pos_out.x * 10));
  float y_fract = fract(sin(time) + pos_out.y *  floor(pos_out.y * 10));

  gl_FragColor = new_col * x_fract * y_fract;
}
