#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>


struct Callback_ptrs{
};

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
shader_setup()
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

  const char* fs  =
    "#version 130\n"
    "in vec4 color_out;"
    "in vec4 pos_out;"
    "uniform float time;"
    ""
    "void main() {"
    "vec2 pos = pos_out.xy;"
    "vec4 new_col = vec4(sin(pos.x + time), sin(time), sin(pos.y + time), 1.0);"
    "gl_FragColor = new_col;"
    "}";

  return shader_compile(vs, fs);
}

void shader_draw(GLuint shader, float time)
{
  glColor3f(0.0, 1.0, 0.0);
  glUseProgram(shader);

  GLuint loc = glGetUniformLocation(shader, "time");
  glUniform1f(loc, time);

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
  struct Callback_ptrs callb_ptrs;

  /* Initalize glfw and glut*/
  if (!glfwInit())
    return -1; //exit

  /* Create window */
  window = glfwCreateWindow(1600, 900, "fragEditor", NULL, NULL);
  if (!window)
  {
    glfwTerminate();
    return -1;
  }

  /* Set the windows context */
  glfwMakeContextCurrent(window);

  /* initalize glew and do various gl setup */
  glewInit();
  glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  srand((unsigned int)time(NULL));


  /* Setup callbacks */
  //callb_ptrs.aa = agent_array;
  //callb_ptrs.wv = world_view;
  //glfwSetWindowSizeCallback(window, window_size_callback);
  //

  GLuint shader = shader_setup();


  /* Main loop */
  while(!glfwWindowShouldClose(window))
  {
    /* Set the viewport & grab scale*/
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);

    /* Clear*/
    glClear(GL_COLOR_BUFFER_BIT);

    shader_draw(shader, glfwGetTime());

    glfwSwapBuffers(window);
    /* Poll for events */
    glfwPollEvents();
  }

  return 0;
}
