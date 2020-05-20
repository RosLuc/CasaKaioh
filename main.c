#include <GL/glut.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "draw.c"


#define WIDTH 400
#define HEIGHT 400

void init(void);
void display(void);
void keyboard(unsigned char key, int x, int y);
void mouse(int button, int state,
           int x, int y);
void mouseMovie(int x, int y);

int mause_start_x;
int mause_start_y;
int button_click = 0;
float button_x = 0;
float button_y = 0;
float angle = 0;
float angle2 = 0;
float trans_rate = 0;

int main(int argc, char **argv)
{
  glutInit (&argc, argv);
  glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize (WIDTH, HEIGHT);
  glutInitWindowPosition (100, 100);
  glutCreateWindow ("Arvore");
  glutDisplayFunc (display);
  glutKeyboardFunc(keyboard);
  glutMouseFunc (mouse);
  glutMotionFunc(mouseMovie);
  init ();
  glutMainLoop ();
  return 0;
}

void init(void)
{
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_TEXTURE_2D);
  glEnable(GL_BLEND);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glClearColor(1.0, 1.0, 1.0, 1.0);
  gluPerspective(45.0f,
                 (float)WIDTH / (float)HEIGHT,
                 0.1f, 100.0f);
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  makeTexture();

  glutIgnoreKeyRepeat(1);
}

void display(void)
{
  glEnable(GL_DEPTH_TEST);
  glutPostRedisplay();
  glutSwapBuffers();
  static float pos_z = 0;
  float angleA = (360.0/2.0)*glutGet(GLUT_ELAPSED_TIME)/1000.0;
  glPushMatrix();
    glLoadIdentity();
    
    pos_z += trans_rate;
    trans_rate = 0.0;
    if(pos_z >= 0.0 && pos_z <= 2.5)
      glTranslatef(0.0, 0.0, pos_z);
    else {
      if(pos_z < 0.0) pos_z = 0.0;
      if(pos_z > 1.5) pos_z = 2.5;
      glTranslatef(0.0, 0.0, pos_z);
    }
  
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glTranslatef(0.0, 0.0, -5.0);
    
    glRotatef(-angle2, 1.0, 0.0, 0.0);
    glRotatef(-angle, 0.0, 1.0, 0.0);
    
    drawCeu();
    drawPlaneta();
    glPushMatrix();

      

      glPushMatrix();
        glRotatef(90, 0.0, 1.0, 0.0);
        glRotatef(-51, 1.0, 0.0, 0.0);
        glRotatef(angleA*0.2, 0.0, 0.0, 1.0);
        glScalef(0.2, 0.2, 0.2);
        glTranslatef(-1.0, 4.9, -0.3);
        drawCar();
      glPopMatrix();

      drawArvores();

      glPushMatrix();
        glRotatef(5, 1.0, 0.0, 0.0);
        glScalef(0.2, 0.2, 0.2);
        glTranslatef(0.0, 4.8, 0.0);
        drawDepsito();
      glPopMatrix();

      glPushMatrix();
        glRotatef(-25, 0.0, 1.0, 0.0);
        glRotatef(40, 1.0, 0.0, 0.0);
        glTranslatef(0.0, 1.0, 0.0);
        glScalef(0.1, 0.1, 0.1);
        glRotatef(-90, 1.0, 0.0, 0.0);
        drawPlantacao();
      glPopMatrix();

      glPushMatrix();
        glRotatef(-39, 0.0, 1.0, 0.0);
        glRotatef(30, 1.0, 0.0, 0.0);
        glTranslatef(0.0, 1.03, 0.0);
        glScalef(0.04, 0.04, 0.04);
        drawBanco();
      glPopMatrix();

      glPushMatrix();
        glRotatef(30, 0.0, 0.0, 1.0);
        glRotatef(13, 1.0, 0.0, 0.0);
        glTranslatef(0.0, 0.98, 0.0);
        glScalef(0.3, 0.3, 0.3);
        drawCasaCompleta();
      glPopMatrix();

    glPopMatrix();
      
  glPopMatrix();

  glFlush();
  glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y){
    printf("%d\n", key);
    switch(key) {
        case 27:
          exit(0);
    break;
  }
}

void mouse(int button, int state,
           int x, int y)
{
  if (((button == 3) || (button == 4)) && state == GLUT_DOWN) {
    (button == 3) ? (trans_rate = 0.05) : (trans_rate = -0.05);
  }

  if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
      mause_start_x = x;
      mause_start_y = y;
      button_click = 1;
  }
  if(button == GLUT_LEFT_BUTTON && state == GLUT_UP){
    button_click = 0;
    button_x = 0;
    button_y = 0;
  }
}

void mouseMovie(int x, int y) {
  if(button_click == 1){
    button_x = mause_start_x - x;
    button_y = mause_start_y - y;
    angle += button_x*0.02;
    angle2 += button_y*0.02;
   }
}
