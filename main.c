#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

typedef struct _Uniforms Uniforms;

struct Callback_ptrs{
};

struct _Uniforms {
  float u_time;
  int u_resolution[2];
  double u_mouse[2];
};

char* frag_read_file() {
  FILE* file;
  size_t size;
  char* buffer;

  file = fopen("shader.frag", "rb");

  fseek(file, 0L, SEEK_END);
  size = ftell(file);
  rewind(file);

  buffer = calloc(1, size + 1);
  fread(buffer, size, 1, file);

  fclose(file);

  printf("Got shader:\n%s\n", buffer);

  return buffer;
}

GLuint
shader_compile(const char* vs_raw, const char* fs_raw)
{
  GLuint vs = 0;
  GLuint fs = 0;
  GLuint shader = 0;
  vs = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vs, 1, &(vs_raw), NULL);
  glCompileShader(vs);

  fs = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fs, 1, &(fs_raw), NULL);
  glCompileShader(fs);

  shader = glCreateProgram();
  glAttachShader(shader, fs);
  glAttachShader(shader, vs);
  glLinkProgram(shader);
  return shader;
}

GLuint
shader_setup(char* fs)
{
  const char* vs =
    "#version 130\n"
    "in vec4 position;"
    "in vec4 color_in;"
    "uniform float time;"
    "out vec4 color_out;"
    "out vec4 pos_out;"
    ""
    "void main() {"
    "pos_out = position;"
    "color_out = color_in;"
    "gl_Position = position;"
    "}";

  return shader_compile(vs, fs);
}

void shader_draw(GLuint shader, Uniforms uniforms)
{

  glColor3f(0.0, 1.0, 0.0);
  glUseProgram(shader);

  GLuint u_time = glGetUniformLocation(shader, "u_time");
  glUniform1f(u_time, uniforms.u_time);

  GLuint u_mouse = glGetUniformLocation(shader, "u_mouse");
  glUniform2f(u_mouse, uniforms.u_mouse[0], uniforms.u_mouse[1]);

  GLuint u_resolution = glGetUniformLocation(shader, "u_resolution");
  glUniform2f(u_resolution, uniforms.u_resolution[0], uniforms.u_resolution[1]);

  glBegin(GL_QUADS);
  glVertex3f(-1.0f, -1.0f, 0.0f);
  glVertex3f(1.0f, -1.0f, 0.0f);
  glVertex3f(1.0f, 1.0f, 0.0f);
  glVertex3f(-1.0f, 1.0f, 0.0f);
  glEnd();
  glUseProgram(0);
}

int
main(int argc, char **argv)
{
  GLFWwindow* window;

  // For passing structs between callbacks in glfw
  //struct Callback_ptrs callb_ptrs;

  /* Initalize glfw and glut*/
  if (!glfwInit())
    return -1; //exit

  /* Create window */
  window = glfwCreateWindow(800, 600, "fragEditor", NULL, NULL);
  if (!window)
  {
    glfwTerminate();
    return -1;
  }

  /* Set the windows context */
  glfwMakeContextCurrent(window);

  /* initalize glew and do various gl setup */
  glewInit();
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  Uniforms uniforms;

  char* frag_shader = frag_read_file();

  GLuint shader = shader_setup(frag_shader);

  printf("Attempting to draw shader!\n");
  printf("A green screen suggests an error with your shader\n");
  printf("Make sure to use GLSL version 130\n");

  /* Main loop */
  while(!glfwWindowShouldClose(window))
  {
    /* Set the uniforms */
    glfwGetFramebufferSize(window, 
        &(uniforms.u_resolution[0]), 
        &(uniforms.u_resolution[1]));
    glfwGetCursorPos(window, &(uniforms.u_mouse[0]), &(uniforms.u_mouse[1]));
    uniforms.u_time = glfwGetTime();

    /* Set the viewport */
    glViewport(0, 0, uniforms.u_resolution[0], uniforms.u_resolution[1]);

    glClear(GL_COLOR_BUFFER_BIT);

    shader_draw(shader, uniforms);

    glfwSwapBuffers(window);

    glfwPollEvents();
  }

  return 0;
}
