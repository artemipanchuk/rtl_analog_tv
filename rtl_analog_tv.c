#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>

#include <GL/gl.h>
#include <GL/glut.h>

#define GLOBAL_WIDTH  720
#define GLOBAL_HEIGHT 576

static uint64_t vskip = 0;
static uint64_t hskip = 0;
static uint64_t w = 128;
static uint64_t h = 625;
static int n = 0;

void keyboard(unsigned char key, int x, int y) {
  if(key == 'q') exit(0);

  if(key == 'g'){
    --hskip;
    printf("hs %f\n", hskip);
  }

  if(key == 'j'){
    ++hskip;
    printf("hs %f\n", hskip);
  }

  if(key == 'a'){
    --w;
    printf("w %i\n", w);
  }

  if(key == 's'){
    ++w;
    printf("w %i\n", w);
  }

  if(key == 'd'){
    h--;
    printf("h %i\n", h);
  }

  if(key == 'f'){
    h++;
    printf("h %i\n", h);
  }

  if(key == 'c'){
    --vskip;
    printf("vskip %i\n", vskip);
  }

  if(key == 'b'){
    ++vskip;
    printf("vskip %i\n", vskip);
  }
}  

void display() {  
  int i, y, x, cx;
  for (i = 0; i < vskip; ++i) {
    getchar();
  }

  glBegin(GL_POINTS);
  for (y = (n&1) ? 1 : 0; y < h; y += 2) {
    for(i = 0; i < hskip; ++i){
      getchar();
    }

    for (x = 0; x < w; ++x) {
      char a, b, c;
      a = getchar();
      b = getchar();

      float t1 = ((float) a) * 0.004,
            t2 = ((float) b) * 0.004,
            t3 = hypot(t1, t2)/2;

      glColor3f(t3, t3, t3);
     
      for(cx = 0; cx < 5; ++cx)
        glVertex2i(5*x+cx, y);
    }
  }

  glEnd();

  if (n == 1)
    --n;
  else
    ++n;

  glFlush();

  glutTimerFunc(1, display, 1);
}

void reshape(GLsizei w, GLsizei h) {
  glViewport(0, 0, GLOBAL_WIDTH, GLOBAL_HEIGHT);
}

void init_video(int argc, char** argv) {
  glutInitDisplayMode(GLUT_RGBA | GLUT_SINGLE);
  glutInit(&argc, argv);
  
  glutCreateWindow("rtl_analog_tv");
  glutInitWindowSize(GLOBAL_WIDTH, GLOBAL_HEIGHT);
  
  glutKeyboardFunc(keyboard);
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  glOrtho(0, GLOBAL_WIDTH, GLOBAL_HEIGHT, 0, 0, 1);
  glViewport(0, 0, GLOBAL_WIDTH, GLOBAL_HEIGHT);
  glClearColor(0, 0, 0, 0);
}

int main(int argc, char** argv) {
  init_video(argc, argv);

  glutMainLoop();
}
