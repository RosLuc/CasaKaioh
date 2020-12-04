#include <GL/glut.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "Textura.h"

GLuint texturas[15];

GLint facesFront[6][4] = {
    {0, 1, 2, 3},{4, 5, 6, 7},{4, 0, 3, 7},
    {5, 1, 2, 6},{4, 5, 1, 0},{7, 6, 2, 3}
};
GLfloat vFront[8][3] = {
    {0.165,0.51,0.6}, {0.65, 0.5,0.6},
    {0.65,0.5,0.1}, {0.165,0.51,0.1},
    {0.165,0.2,0.6}, {0.6,0.2,0.6},
    {0.6,0.2,0.1}, {0.165,0.2,0.1}

};

GLint facesRoof[5][4] = {
    {0, 1, 2, 3},{3, 2, 6, 7},{4, 0, 3, 7},
    {4, 5, 1, 0},{5, 1, 2, 6}
};
GLfloat vRoof[8][3] = {
    {0.69,0.72,0.6}, {0.69, 0.72,0.1},
    {1.0,0.68,0.1}, {1.0,0.68,0.6},
    {0.65,0.5,0.6}, {0.65,0.5,0.1},
    {1.2,0.5,0.1}, {1.2,0.5,0.6}

};

GLint facesBack[5][4] = {
    {0, 1, 2, 3}, {3, 2, 4, 4}, {5, 6, 2, 3},
    {7, 1, 6, 2}, {4, 0, 5, 3}
};
GLfloat vBack[8][3] = {
    {1.2, 0.5,0.6}, {1.2,0.5,0.1},
    {1.57,0.2,0.1}, {1.57,0.2,0.6},
    {1.2,0.2,0.6}, {1.6,0.52,0.6},
    {1.6,0.52,0.1}, {1.2,0.2,0.1}

};

GLint facesBody[3][4] = {
    {0, 1, 2, 3},{1, 4, 5, 2},{6, 4, 5, 7},
};
GLfloat vBody[8][3] = {
    {0.6, 0.5,0.6}, {0.6, 0.2,0.6},
    {1.2, 0.2, 0.6}, {1.2,0.5,0.6},
    {0.6,0.2,0.1}, {1.2,0.2,0.1},
    {0.6,0.5,0.1}, {1.2,0.5,0.1}
};

GLfloat vWindowSideT[3][3] = {
    {0.0,0.0,0.0}, {0.1, 0.1,0.0},
    {0.1,0.1,0.1}
};

int faces[6][4] = {
        {0, 1, 2, 3}, {3, 2, 6, 7}, {7, 6, 5, 4},
        {4, 5, 1, 0}, {5, 6, 2, 1}, {7, 4, 0, 3}};

GLfloat v[8][3] = {
	  {-1.0, -1.0, 1.0},
    {-1.0, -1.0, -1.0},
    {-1.0, 1.0, -1.0},
    {-1.0, 1.0, 1.0},
    {1.0, -1.0, 1.0},
    {1.0, -1.0, -1.0},
    {1.0, 1.0, -1.0},
    {1.0, 1.0, 1.0}};

static void
makeTexture(void)
{
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_TEXTURE_2D);
  glEnable(GL_COLOR_MATERIAL);
  
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
 
  glGenTextures(10, texturas);
 
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
 
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
 
  texturas[0] = carregaBmp("textura/tronco.bmp");
  texturas[1] = carregaBmp("textura/folha3.bmp");
  texturas[2] = carregaBmp("textura/grama.bmp");
  texturas[3] = carregaBmp("textura/estrada.bmp");
  texturas[4] = carregaBmp("textura/ceuX45.bmp");

  glBindTexture(GL_TEXTURE_2D, texturas[5]);

  GLubyte texture2[16][16][3];

  for (int i = 0; i < 16; i++) {
    for (int j = 0; j < 16; j++) {
      texture2[i][j][0] = 0xff;
      texture2[i][j][1] = 0x80;
      texture2[i][j][2] = 0xff; 
    }
  }

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 16, 16, 0,
      GL_RGB, GL_UNSIGNED_BYTE, texture2);
    
  
}

/* i, and j are mapped in [0, 1]
 * vertex is assigned to the point of a
 *		  a plane with (i, j) surface coordinates.
 */
void genPlaneVertex(float i, float j, float *vertex)
{
	float x = -1.0 + 2.0*i;
	float y = -1.0 + 2.0*j;
	float z = 0;

	vertex[0] = x;
	vertex[1] = y;
	vertex[2] = z;
}

/* i, and j are mapped in [0, 1]
 * vertex is assigned to the point of a
 *		  a plane with (i, j) surface coordinates.
 */
void genCylinderVertex(float i, float j, float *vertex)
{
	float x = cos(2.0*M_PI*i);
	float y = -1.0 + 2.0*j;
	float z = sin(2.0*M_PI*i);

	vertex[0] = x;
	vertex[1] = y;
	vertex[2] = z;
}

/* i, and j are mapped in [0, 1]
 * vertex is assigned to the point of a
 *		  a plane with (i, j) surface coordinates.
 */
void genConeVertex(float i, float j, float *vertex)
{
  float r = 1.0 - j;
	float x = r*cos(2.0*M_PI*i);
	float y = -1.0 +2.0*j;
	float z = r*sin(2.0*M_PI*i);

	vertex[0] = x;
	vertex[1] = y;
	vertex[2] = z;
}

/* i, and j are mapped in [0, 1]
 * vertex is assigned to the point of a
 *		  a plane with (i, j) surface coordinates.
 */
void genSphereVertex(float i, float j, float *vertex)
{
	float y = -1.0 +2.0*j;
  float r = sqrt(1.0 - y*y);
	float x = r*cos(2.0*M_PI*i);
	float z = r*sin(2.0*M_PI*i);

	vertex[0] = x;
	vertex[1] = y;
	vertex[2] = z;
}

void drawSurface(int e_u, int e_v, void (*genVertex)(float, float, float*))
{
  int i;
  int j;
  const int h_div = 30;
  const int v_div = 30;

  //glColor3f(1.0, 1.0, 1.0);

  for(j = 0; j < v_div; j++) {
    for(i = 0; i < h_div; i++) {
        glBegin(GL_QUADS);
          float vertex[3];
          float u, v;
          u = (float)i/h_div;
          v = (float)j/v_div;
          genVertex(u, v, vertex);
          glTexCoord2f(e_u*u, e_v*v);
          glVertex3fv(vertex);

          u = (float)(i+1)/h_div;
          v = (float)j/v_div;
          genVertex(u, v, vertex);
          glTexCoord2f(e_u*u, e_v*v);
          glVertex3fv(vertex);

          u = (float)(i+1)/h_div;
          v = (float)(j+1)/v_div;
          genVertex(u, v, vertex);
          glTexCoord2f(e_u*u, e_v*v);
          glVertex3fv(vertex);

          u = (float)i/h_div;
          v = (float)(j+1)/v_div;
          genVertex(u, v, vertex);
          glTexCoord2f(e_u*u, e_v*v);
          glVertex3fv(vertex);

        glEnd();
    }
  }
}

void genPlaneta(float i, float j, float *vertex){
	float y = -1.0 + 2.0*j;
    float r = sqrt(1.0 - y*y);
	float x = r*cos(2.0*M_PI*i);
	float z = r*sin(2.0*M_PI*i);

	vertex[0] = x;
	vertex[1] = y;
	vertex[2] = z;
}

void drawArvore() {
  glBindTexture(GL_TEXTURE_2D, texturas[0]);
  glPushMatrix();
     glTranslatef(0.0, -0.5, 0.0);
     glScalef(0.1, 0.5, 0.1);
     drawSurface(1, 1, genCylinderVertex);
  glPopMatrix();
 
  glBindTexture(GL_TEXTURE_2D, texturas[1]);
  glPushMatrix();
     glScalef(0.5, 0.5, 0.5);
     drawSurface(1, 1, genSphereVertex);
  glPopMatrix();
}

void drawArvores() {
  glPushMatrix();
      glRotatef(125, 1.0, 0.0, 0.0);
      glPushMatrix();
        glTranslatef(0.0, 1.25, 0.0);
        glScalef(0.3, 0.3, 0.3);
        drawArvore();
      glPopMatrix();
    
      glPushMatrix();
        glRotatef(-6, 0.0, 0.0, 1.0);
        glTranslatef(0.0, 1.20, 0.0);
        glScalef(0.25, 0.25, 0.25);
        drawArvore();
      glPopMatrix();
  glPopMatrix();
  
  glPushMatrix();
    glRotatef(100, 0.0, 1.0, 0.0);
    glRotatef(70, 1.0, 0.0, 0.0);
    glTranslatef(0.0, 1.25, 0.0);
    glScalef(0.3, 0.3, 0.3);
    drawArvore();
  glPopMatrix();

  glPushMatrix();
    glRotatef(-20, 0.0, 0.0, 1.0);
    glRotatef(-20, 1.0, 0.0, 0.0);
    glTranslatef(0.0, 1.25, 0.0);
    glScalef(0.3, 0.3, 0.3);
    drawArvore();
  glPopMatrix();

  glPushMatrix();
    glRotatef(70, 0.0, 1.0, 0.0);
    glRotatef(-100, 1.0, 0.0, 0.0);
    glTranslatef(0.0, 1.25, 0.0);
    glScalef(0.3, 0.3, 0.3);
    drawArvore();
  glPopMatrix();

  glPushMatrix();
    glRotatef(90, 0.0, 1.0, 0.0);
    glRotatef(-40, 1.0, 0.0, 0.0);
    glTranslatef(0.0, 1.25, 0.0);
    glScalef(0.3, 0.3, 0.3);
    drawArvore();
  glPopMatrix();
}

void drawCeu() {
  glBindTexture(GL_TEXTURE_2D, texturas[5]);
  float scale = 60.0;
  glPushMatrix();
    glScalef(scale, scale, scale);
    drawSurface(1, 1, genSphereVertex);
  glPopMatrix();
  
  glBindTexture(GL_TEXTURE_2D, texturas[4]);
  glPushMatrix();
    glTranslatef(0.0, -6.0, 0.0);
    glRotatef(90, 1.0, 0.0, 0.0);
    glScalef(scale, scale, scale);
    drawSurface(8, 8, genPlaneVertex);
  glPopMatrix();
  
}

void drawPlaneta() {
  
  glPushMatrix();
     glBindTexture(GL_TEXTURE_2D, texturas[2]);
     drawSurface(1, 1, genPlaneta);
  glPopMatrix();

  glPushMatrix();
     glBindTexture(GL_TEXTURE_2D, texturas[3]);
     glRotatef(-40, 0.0, 0.0, 1.0);
     glScalef(1.005, 0.1, 1.005);
     drawSurface(16, 1, genCylinderVertex);
  glPopMatrix();
}

void genGaragem(float i, float j, float *vertex){
	float x = cos(M_PI*i);
	float y = -1.0 +2.0*j;
	float z = sin(M_PI*i);

	vertex[0] = x;
	vertex[1] = y;
	vertex[2] = z;
}

void drawPreenche(void) {
    int linhas = 20;
    glBegin(GL_POLYGON);
    for(int i = 0; i < linhas; i++){
        float angle = (i*1.05*M_PI)/linhas;
        float u = cos(angle);
        float v = sin(angle);
        glVertex2f(u,v);
        glTexCoord2f(u,v);
    }
    glEnd();
}

void drawAba(void) {
    int linhas = 20;
    glBegin(GL_LINE_STRIP);
    for(int i = 0; i < linhas; i++){
        float angle = (i*1.05*M_PI)/linhas;
        float u = cos(angle);
        float v = sin(angle);
        glVertex2f(u,v);
        glTexCoord2f(u,v);
    }
    glEnd();
}

void drawPorta(void) {

    glBegin(GL_QUAD_STRIP);
        glVertex2f(-1.0,-1.0);
        glVertex2f( 1.0,-1.0);
        glVertex2f(-1.0, 0);
        glVertex2f( 1.0, 0);
        glVertex2f(-1.0, 1.0);
        glVertex2f( 1.0, 1.0);
        glVertex2f(-1.0, 1.0);
        glVertex2f( 1.0, 1.0);

    glEnd();
}

void drawCube(){
    int i;
    glRotatef(90,0.0,1.0,0.0);
    for (i = 0; i < 6; i++) {
      glBegin(GL_QUADS);

        glVertex3fv(&v[faces[i][0]][0]);
        glVertex3fv(&v[faces[i][1]][0]);
        glVertex3fv(&v[faces[i][2]][0]);
        glVertex3fv(&v[faces[i][3]][0]);

      glEnd();
    }
    glPopMatrix();
}


void drawGaragem(){
  int i;
  int j;
  const int h_div = 100;
  const int v_div = 100;
   glRotatef(90,0.0,1.0,0.0);
   glRotatef(-90,1.0,0.0,0.0);

  for(j = 0; j < v_div; j++) {
    for(i = 0; i < h_div; i++) {

        glBegin(GL_QUADS);
          float vertex[3];
          genGaragem((float)i/h_div, (float)j/v_div, vertex);
          glVertex3fv(vertex);
          genGaragem((float)(i+1)/h_div, (float)j/v_div, vertex);
          glVertex3fv(vertex);
          genGaragem((float)(i+1)/h_div, (float)(j+1)/v_div, vertex);
          glVertex3fv(vertex);
          genGaragem((float)i/h_div, (float)(j+1)/v_div, vertex);
          glVertex3fv(vertex);
        glEnd();
    }
  }
}

void drawDepsito() {
  glPushMatrix();
    glDisable(GL_TEXTURE_2D);
    glPushMatrix();
      glColor3f((float) 120/255, (float) 60/255, 0.0);
      glRotatef(90, 0.0, 1.0, 0.0);
      drawGaragem();
    glPopMatrix();
    
    glPushMatrix();
      glColor3f(1.0, 1.0, 1.0);
			glTranslatef(0.0, 0.0, 1.0);
      drawAba();
    glPopMatrix();
		
    glPushMatrix();
      glColor3f((float) 235/255,(float) 199/255,(float) 158/255);
      glTranslatef(0.0, 0.0, 0.9);
      drawPreenche();
      //glColor3f((float) 217/255,(float) 135/255,(float) 25/255);
      glTranslatef(0.0, 0.0, -1.91);
      drawPreenche();
    glPopMatrix();

    glPushMatrix();
      glColor3f(0.3, 0.2, 0.09);
      glTranslatef(0.0, 0.1, 0.904);
      glScalef(0.5, 0.45, 0.95);
      drawPreenche();
      glTranslatef(0.0, -0.9, 0.0);
      glScalef(1.0, 1.15, 0.95);
      drawPorta();
    glPopMatrix();

    glPushMatrix();        
      glColor3f(0.0, 0.0, 0.0);
      glTranslatef(0.0,0.7, 0.904);
      glScalef(0.3, 0.1, 1.0);
      drawPorta();
    glPopMatrix();

    glPushMatrix();
      glColor3f((float) 235/255,(float) 199/255,(float) 158/255);
      glTranslatef(0.0, -0.488, -0.05);
      glScalef(1.0, 0.5, 0.95);
      drawCube();
    glPopMatrix();
    glEnable(GL_TEXTURE_2D);
  glPopMatrix();
}

void genCasa(float i, float j, float *vertex){
	float y = j*2;
    float r = sqrt(2.0 - y*y);
	float x = r*cos(2.0*M_PI*i);
	float z = r*sin(2.0*M_PI*i);

	vertex[0] = x;
	vertex[1] = y;
	vertex[2] = z;
}

//Circulo
void drawPreenche2(void) {
    int linhas = 20;
    float angle;
    glBegin(GL_POLYGON);
    for(int i = 0; i < linhas; i++){
        angle = (i*2.0*M_PI)/linhas;
        glVertex2f(0.0 + (cos(angle)*1.0),0.0 + (sin(angle)*1.0));
    }
    glEnd();
}

//cria a chaminé
void drawChamine(){
    int i;
    glRotatef(90,0.0,1.0,0.0);
    for (i = 0; i < 6; i++) {
      glBegin(GL_QUADS);

        glVertex3fv(&v[faces[i][0]][0]);
        glVertex3fv(&v[faces[i][1]][0]);
        glVertex3fv(&v[faces[i][2]][0]);
        glVertex3fv(&v[faces[i][3]][0]);

      glEnd();
    }
    glPopMatrix();
}

//Cria plano
void drawPlane(){
    int i;
    int j;
    const int h_div = 10;
    const int v_div = 10;

    for(j = 0; j < v_div; j++) {
        for(i = 0; i < h_div; i++) {
        glBegin(GL_QUADS);
            float vertex[3];
            genPlaneVertex((float)i/h_div, (float)j/v_div, vertex);
            glVertex3fv(vertex);
            genPlaneVertex((float)(i+1)/h_div, (float)j/v_div, vertex);
            glVertex3fv(vertex);
            genPlaneVertex((float)(i+1)/h_div, (float)(j+1)/v_div, vertex);
            glVertex3fv(vertex);
            genPlaneVertex((float)i/h_div, (float)(j+1)/v_div, vertex);
            glVertex3fv(vertex);
        glEnd();
        }
    }
}

//cria cilindro
void drawCylinder(){
    int i;
    int j;
    const int h_div = 50;
    const int v_div = 50;

    for(j = 0; j < v_div; j++) {
        for(i = 0; i < h_div; i++) {
            glBegin(GL_QUADS);
            float vertex[3];
            genCylinderVertex((float)i/h_div, (float)j/v_div, vertex);
            glVertex3fv(vertex);
            genCylinderVertex((float)(i+1)/h_div, (float)j/v_div, vertex);
            glVertex3fv(vertex);
            genCylinderVertex((float)(i+1)/h_div, (float)(j+1)/v_div, vertex);
            glVertex3fv(vertex);
            genCylinderVertex((float)i/h_div, (float)(j+1)/v_div, vertex);
            glVertex3fv(vertex);
            glEnd();
        }
    }
}

//cria a casa
void drawCasa(){
    int i;
    int j;
    const int h_div = 20;
    const int v_div = 20;

    for(j = 0; j < v_div; j++) {
        for(i = 0; i < h_div; i++) {
            if((j==10)){
                glColor3f((float) 138/255, (float) 71/255, (float) 36/255);
            }
            else{
                glColor3f((float) 232/255, (float) 209/255, (float) 115/255);
            }
            glBegin(GL_QUADS);
            float vertex[3];
            genCasa((float)i/h_div, (float)j/v_div, vertex);
            glVertex3fv(vertex);
            glTexCoord2f((float)i/h_div, (float)j/v_div);

            genCasa((float)(i+1)/h_div, (float)j/v_div, vertex);
            glVertex3fv(vertex);
            glTexCoord2f((float)(i+1)/h_div, (float)j/v_div);

            genCasa((float)(i+1)/h_div, (float)(j+1)/v_div, vertex);
            glVertex3fv(vertex);
            glTexCoord2f((float)(i+1)/h_div, (float)(j+1)/v_div);

            genCasa((float)i/h_div, (float)(j+1)/v_div, vertex);
            glVertex3fv(vertex);
            glTexCoord2f((float)i/h_div, (float)(j+1)/v_div);

            glEnd();
        }
    }
}

//Arco da porta
void genPortaArco(float i, float j, float *vertex){
	float x = cos(M_PI*i);
	float y = -1.0 +2.0*j;
	float z = sin(M_PI*i);

	vertex[0] = x;
	vertex[1] = y;
	vertex[2] = z;
}

//Cria Arco branco em volta da porta
void drawCylinderArco(){
    int i;
    int j;
    const int h_div = 50;
    const int v_div = 50;

   glRotatef(-90,1.0,0.0,0.0);

    for(j = 0; j < v_div; j++) {
        for(i = 0; i < h_div; i++) {
            glBegin(GL_QUADS);
            float vertex[3];
            genPortaArco((float)i/h_div, (float)j/v_div, vertex);
            glVertex3fv(vertex);
            genPortaArco((float)(i+1)/h_div, (float)j/v_div, vertex);
            glVertex3fv(vertex);
            genPortaArco((float)(i+1)/h_div, (float)(j+1)/v_div, vertex);
            glVertex3fv(vertex);
            genPortaArco((float)i/h_div, (float)(j+1)/v_div, vertex);
            glVertex3fv(vertex);
            glEnd();
        }
    }
}

//Semicirculo
void drawPreenche1(void) {
    int linhas = 20;
    glBegin(GL_POLYGON);
    for(int i = 0; i < linhas; i++){
        float angle = (i*1.05*M_PI)/linhas;
        float u = cos(angle);
        float v = sin(angle);
        glVertex2f(u,v);
        glTexCoord2f(u,v);
    }
    glEnd();
}

//Cria as janelas
void janela(){
    glPushMatrix();

        glPushMatrix();

            glPushMatrix();
                glTranslatef(0.0,1.0,0.0);
                glRotatef(90,1.0,0.0,0.0);
                drawPlane();
            glPopMatrix();
            glPushMatrix();
                glTranslatef(1.0,0.9,0.0);
                glRotatef(90,0.0,1.0,0.0);
                glScalef(1.0, 0.1 , 1.0);
                drawPlane();
                glPopMatrix();

            glPushMatrix();
                glTranslatef(-1.0,0.9,0.0);
                glRotatef(90,0.0,1.0,0.0);
                glScalef(1.0, 0.1 , 1.0);
                drawPlane();
            glPopMatrix();
            glPushMatrix();
                glTranslatef(0.0,0.9,1.0);
                glScalef(1.0, 0.1 , 1.0);
                drawPlane();
            glPopMatrix();

       glPopMatrix();

        //lados

        glPushMatrix();
            glTranslatef(-0.89,0.2,0.258);
            glRotatef(50,1.0,0.0,0.0);
            glScalef(0.1, 1.0 , 0.1);
            drawPlane();
        glPopMatrix();

        glPushMatrix();
            glTranslatef(0.89,0.2,0.258);
            glRotatef(50,1.0,0.0,0.0);
            glScalef(0.1, 1.0 , 0.1);
            drawPlane();
        glPopMatrix();

    glPopMatrix();
}

void drawCasaCompleta() {
  glDisable(GL_TEXTURE_2D);
  glPushMatrix();

//Casa
    glPushMatrix();
        glRotatef(90, 0.0, 1.0, 0.0);
        glScalef(0.5, 0.5, 0.5);
        drawCasa();
    glPopMatrix();

    glPushMatrix();
        glScalef(0.5, 0.5, 0.5);
        glTranslatef(0.0, -0.3, 0.0);
        glScalef(1.39, 0.5, 1.39);
        drawCylinder();
    glPopMatrix();

//Detalhes da parte superior e janelas(Branco)
    glColor3f((float) 250/255, (float) 235/255, (float) 215/255);

    glPushMatrix();
        glTranslatef(0.0, 0.7, 0.0);
        glScalef(0.3, 0.04 , 0.3);
          
          glPushMatrix();
            glTranslatef(0.0, -0.9, 0.0);
            drawCylinder();
          glPopMatrix();
          glPushMatrix();
            glRotatef(90,1.0,0.0,0.0);
            drawPreenche2();
            glPopMatrix();
          glPopMatrix();

          glPushMatrix();
            glTranslatef(0.0,0.75, 0.0);
            glScalef(0.015, 0.2,0.015);
            drawCylinder();
          glPopMatrix();

          glPushMatrix();
            glTranslatef(0.1,0.75,0.1);
            glScalef(0.015, 0.1,0.015);
            drawCylinder();
          glPopMatrix();
        
          glPushMatrix();
             glTranslatef(-0.34, 0.23, 0.48);
             glRotatef(-37,0.0,1.0,0.0);
             glScaled(0.1,0.1,0.1);
             janela();
           glPopMatrix();

         glPushMatrix();
            glTranslatef(0.34, 0.23, 0.48);
            glRotatef(37,0.0,1.0,0.0);
            glScaled(0.1,0.1,0.1);
            janela();
         glPopMatrix();

         ///Porta e arco
         //Arco(branco)
        glPushMatrix();
            glPushMatrix();
                glTranslatef(0.0, -0.055, 0.62);
                glScalef(0.13,0.35,0.10);
                drawCylinderArco();
            glPopMatrix();
            glColor3f(0.3, 0.2, 0.09);
            glPushMatrix();
                glTranslatef(0.0, -0.055, 0.71);
                glScalef(0.13,0.35,0.13);
                drawPreenche1();
            glPopMatrix();
        glPopMatrix();

        //chamin�(cinza)
        glColor3f((float) 105/255, (float) 105/255, (float) 105/255);
        glPushMatrix();
          glPushMatrix();

            glPushMatrix();
                glTranslatef(0.77, 0.55, 0.158);
                glRotatef(90,1.0,0.0,0.0);
                glRotatef(90,0.0,0.0,1.0);
                glScalef(0.06,0.15,0.06);
                drawPlane();
            glPopMatrix();

            glPushMatrix();
                glTranslatef(0.77, 0.55, 0.158);
                glRotatef(90,0.0,1.0,0.0);
                glScalef(0.06,0.15,0.15);
                drawCylinderArco();
            glPopMatrix();

          glPopMatrix();


          glPushMatrix();
            glPushMatrix();
                glTranslatef(0.77, 0.4, 0.158);
                glScalef(0.03,0.15,0.03);
                drawCube();
            glPopMatrix();

            glPushMatrix();
                glTranslatef(0.65, 0.27, 0.158);
                glRotatef(90,1.0,0.0,0.0);
                glRotatef(90,0.0,0.0,1.0);
                glScalef(0.03,0.15,0.03);
                drawCube();
            glPopMatrix();
          glPopMatrix();

         glPopMatrix();

     glPopMatrix();

  glPopMatrix();
  glEnable(GL_TEXTURE_2D);
}

void genWheelVertex(float i, float j, float *vertex)
{
	float x = (cos(2.0*M_PI*i));
	float y = (sin(2.0*M_PI*i));
	float z = j;

	vertex[0] = x;
	vertex[1] = y;
	vertex[2] = z;
}

void genHubcapVertex(float i, float j, float *vertex)
{
    float z = 0;
    float r = sqrt(1.0 - j*j);
	float x = r*(cos(2.0*M_PI*i));
	float y = r*(sin(2.0*M_PI*i));


    vertex[0] = x;
    vertex[1] = y;
    vertex[2] = z;
}


void genSemiCylinderVertex(float i, float j, float *vertex)
{
	float x = (3.0 * i) - 1.0;
	float z = (7.15 * j) - 1.0;
	float r = (z/12);
	float y = sqrt(r - (x * x));

	vertex[0] = x;
	vertex[1] = y;
	vertex[2] = z;
}

void drawWindow(){
   glBegin(GL_QUADS);
   glVertex3f(0.0,0.0,0.0);
   glVertex3f(0.5,0.0,0.0);
   glVertex3f(0.5,0.25,0.0);
   glVertex3f(0.0,0.25,0.0);
   glEnd();
}

void drawWindowSideMM(){
   glBegin(GL_QUADS);
   glVertex3f(0.0,0.0,0.0);
   glVertex3f(0.3,0.0,0.0);
   glVertex3f(0.16,0.165,0.0);
   glVertex3f(0.0,0.185,0.0);
   glEnd();
}

void drawWindowSideM(){
   glBegin(GL_QUADS);
   glVertex3f(0.01,0.0,0.0);
   glVertex3f(0.12,-0.04,0.0);
   glVertex3f(0.17,0.143,0.0);
   glVertex3f(0.1,0.17,0.0);
   glEnd();
}

void drawCar()
{
  glDisable(GL_TEXTURE_2D);
  int i;
  float angle = (360.0/2.0)*glutGet(GLUT_ELAPSED_TIME)/10000.0;
glPushMatrix();

//---------------------------FRONT-----------------------------------//
  for (i = 0; i < 6; i++) {
    glBegin(GL_QUADS);
    glColor3f(10.7, 0.0, 0.1);
    glVertex3fv(&vFront[facesFront[i][0]][0]);
    glVertex3fv(&vFront[facesFront[i][1]][0]);
    glVertex3fv(&vFront[facesFront[i][2]][0]);
    glVertex3fv(&vFront[facesFront[i][3]][0]);
    glEnd();
  }
    glColor3f(1.7, 0.0, 0.1);
    glPushMatrix();
        glTranslatef(0.78,0.475,0.16);             //UPSIDE RIGHT
        glRotatef(-90, 0.0, 1.0, 0.0);
        glScaled(0.1,0.1,0.1);
        drawSurface(1, 1,genSemiCylinderVertex);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(0.78,0.475,0.53);             //UPSIDE LEFT
        glRotatef(-90, 0.0, 1.0, 0.0);
        glScaled(0.1,0.1,0.1);
        drawSurface(1, 1,genSemiCylinderVertex);
    glPopMatrix();

//---------------------------BACK-----------------------------------//
  for (i = 0; i < 5; i++) {
    glBegin(GL_QUADS);
    glColor3f(10.7, 0.0, 0.1);
    glVertex3fv(&vBack[facesBack[i][0]][0]);
    glVertex3fv(&vBack[facesBack[i][1]][0]);
    glVertex3fv(&vBack[facesBack[i][2]][0]);
    glVertex3fv(&vBack[facesBack[i][3]][0]);
    glEnd();
  }

//---------------------------BODY-----------------------------------//
  for (i = 0; i < 3; i++) {
    glBegin(GL_QUADS);
    glColor3f(10.7, 0.0, 0.1);
    glVertex3fv(&vBody[facesBody[i][0]][0]);
    glVertex3fv(&vBody[facesBody[i][1]][0]);
    glVertex3fv(&vBody[facesBody[i][2]][0]);
    glVertex3fv(&vBody[facesBody[i][3]][0]);
    glEnd();
  }


//---------------------------ROOF-----------------------------------//
  for (i = 0; i < 5; i++) {
    glBegin(GL_QUADS);
    glColor3f(0.8, 0.8, 0.8);
    glVertex3fv(&vRoof[facesRoof[i][0]][0]);
    glVertex3fv(&vRoof[facesRoof[i][1]][0]);
    glVertex3fv(&vRoof[facesRoof[i][2]][0]);
    glVertex3fv(&vRoof[facesRoof[i][3]][0]);
    glEnd();
  }

//----------------------------WHEEL--------------------------------//
  glColor3f(0.0,0.0,0.0);
  glPushMatrix();
    glTranslatef(0.32,0.2,0.512);         //WHEEL LEFT_FRONT
    glScaled(0.1,0.1,0.1);
    drawSurface(1, 1,genWheelVertex);
  glPopMatrix();

  glPushMatrix();
    glTranslatef(0.32,0.2,0.612);
    glScaled(0.1,0.1,0.1);
    drawSurface(1, 1,genHubcapVertex);
  glPopMatrix();

  glPushMatrix();
    glTranslatef(1.3, 0.2, 0.512);        //WHEEL LEFT_BACK
    glScaled(0.1,0.1,0.1);
    drawSurface(1, 1,genWheelVertex);
  glPopMatrix();

  glPushMatrix();
    glTranslatef(1.3, 0.2, 0.612);
    glScaled(0.1,0.1,0.1);
    drawSurface(1, 1,genHubcapVertex);
  glPopMatrix();

  glPushMatrix();
    glTranslatef(0.32,0.2,0.085);         //WHEEL RIGHT_FRONT
    glScaled(0.1,0.1,0.1);
    drawSurface(1, 1,genWheelVertex);
  glPopMatrix();

  glPushMatrix();
    glTranslatef(0.32,0.2,0.085);
    glScaled(0.1,0.1,0.1);
    drawSurface(1, 1,genHubcapVertex);
  glPopMatrix();

  glPushMatrix();
    glTranslatef(1.3,0.2,0.085);            //WHEEL RIGHT_BACK
    glScaled(0.1,0.1,0.1);
    drawSurface(1, 1,genWheelVertex);
  glPopMatrix();

  glPushMatrix();
    glTranslatef(1.3,0.2,0.085);
    glScaled(0.1,0.1,0.1);
    drawSurface(1, 1,genHubcapVertex);
  glPopMatrix();

//___HUBCAP OUTSIDE___//

  glColor3f(0.7,0.7,0.7);

  glPushMatrix();
    glTranslatef(0.32,0.2,0.615);         //HUBCAP LEFT_FRONT
    glScaled(0.06,0.06,0.06);
    drawSurface(1, 1,genHubcapVertex);
  glPopMatrix();

  glPushMatrix();
    glTranslatef(1.3, 0.2, 0.615);        //HUBCAP LEFT_BACK
    glScaled(0.06,0.06,0.06);
    drawSurface(1, 1,genHubcapVertex);
  glPopMatrix();

  glPushMatrix();
    glTranslatef(0.32,0.2,0.081);         //HUBCAP RIGHT_FRONT
    glScaled(0.06,0.06,0.06);
    drawSurface(1, 1,genHubcapVertex);
  glPopMatrix();

  glPushMatrix();
    glTranslatef(1.3,0.2,0.081);          //HUBCAP RIGHT_BACK
    glScaled(0.06,0.06,0.06);
    drawSurface(1, 1,genHubcapVertex);
  glPopMatrix();

//------------------------------WINDOWS----------------------------------//
  glColor3f(0.6, 0.6, 0.6);
  glPushMatrix();
    glTranslatef(0.65, 0.5,0.605);          //WINDOW LEFT_FRONT
    glRotated(17,0.0,0.0,0.1);
    drawWindowSideM();
  glPopMatrix();

  glPushMatrix();
    glTranslatef(0.653, 0.5,0.095);         //WINDOW RIGHT_FRONT
    glRotatef(17,0.0,0.0,0.1);
    drawWindowSideM();
  glPopMatrix();

  glPushMatrix();
    glTranslatef(0.78, 0.5,0.605);          //WINDOW LEFT_BACK
    drawWindowSideMM();
  glPopMatrix();

  glPushMatrix();
    glTranslatef(0.785, 0.5,0.095);         //WINDOW RIGHT_BACK
    drawWindowSideMM();
  glPopMatrix();

  glPushMatrix();
    glTranslatef(0.645,0.5,0.58);
    glRotatef(10.0, 0.0,0.0,-1.0);         //WINDOW FRONT
    glRotated(90.0, 0.0,1.0,0.0);
    glScaled(0.9,0.8,1.0);
    drawWindow();
  glPopMatrix();

  glPushMatrix();
    glTranslatef(1.21,0.5,0.575);
    glRotatef(49.0, 0.0,0.0,1.0);          //WINDOW BACK
    glRotated(90.0, 0.0,1.0,0.0);
    glScaled(0.9,0.75,1.0);
    drawWindow();
  glPopMatrix();

//------------------------------LIGHTS_FRONT------------------------------------//
  glColor3f(0.9,0.9,0.9);
  glPushMatrix();
    glTranslatef(0.16,0.47,0.53);
    glRotatef(90,0.0,1.0,0.0);                           //LIGHT LEFT
    glScaled(0.045,0.045,0.045);
    drawSurface(1, 1,genHubcapVertex);
  glPopMatrix();

  glPushMatrix();
    glTranslatef(0.16,0.47,0.17);
    glRotatef(90,0.0,1.0,0.0);                           //LIGHT RIGHT
    glScaled(0.04,0.04,0.04);
    drawSurface(1, 1,genHubcapVertex);
  glPopMatrix();

//------------------------------LIGHTS_BACK------------------------------------//
  glPushMatrix();
    glTranslatef(1.6,0.45,0.167);
    glRotatef(90,0.0,1.0,0.0);                          //LIGHT RIGHT
    glScaled(0.025,0.025,0.025);
    drawSurface(1, 1,genHubcapVertex);
  glPopMatrix();

  glPushMatrix();
    glTranslatef(1.6,0.45,0.55);
    glRotatef(90,0.0,1.0,0.0);                          //LIGHT LEFT
    glScaled(0.025,0.025,0.025);
    drawSurface(1, 1,genHubcapVertex);
  glPopMatrix();

  glColor3f(0.9,0.0,0.0);
  glPushMatrix();
    glTranslatef(1.602,0.45,0.167);                     //LIGHT RIGHT
    glRotatef(90,0.0,1.0,0.0);
    glScaled(0.012,0.012,0.012);
    drawSurface(1, 1,genHubcapVertex);
  glPopMatrix();

  glColor3f(0.9,0.0,0.0);
  glPushMatrix();
    glTranslatef(1.602,0.45,0.55);                       //LIGHT LEFT
    glRotatef(90,0.0,1.0,0.0);
    glScaled(0.012,0.012,0.012);
    drawSurface(1, 1,genHubcapVertex);
  glPopMatrix();

//------------------------------EXHAUST------------------------------------//
  glColor3f(0.7,0.7,0.7);
  glPushMatrix();
    glTranslatef(1.32,0.21,0.2);
    glRotatef(10.5,0.0,0.0,-1.0);
    glRotatef(90.0,0.0,1.0,0.0);
    glScaled(0.022, 0.022, 0.3);
    drawSurface(1, 1,genWheelVertex);
  glPopMatrix();

//------------------------------BUMPER------------------------------------//

  glColor3f(0.85,0.9,0.85);
  glPushMatrix();
    glTranslatef(0.15,0.17,0.595);       //BUMPER FRONT
    glRotatef(90.0,0.0,1.0,0.0);
    glScaled(1.0, 0.6, 1.0);
    drawWindow();
  glPopMatrix();

  glColor3f(0.85,0.9,0.85);
  glPushMatrix();
    glTranslatef(1.575,0.17,0.595);
    glRotatef(5,0.0,0.0,-1.0);       //BUMPER BACK
    glRotatef(90.0,0.0,1.0,0.0);
    glScaled(1.0, 0.6, 1.0);
    drawWindow();
  glPopMatrix();

glColor3f(1.0,1.0,1.0);
glPopMatrix();
glEnable(GL_TEXTURE_2D);
}

void drawfolhas(){
    int i, j;
    float x1, x2, x3, y1, y2, y3, z1, z2, z3;
    float x, y, z;
    for(i = 0; i < 10; i++){
    glBegin(GL_QUADS);
       for(j = 0; j < 10; j++){
            x = (2.0 * i / 9.0) - 1.0;
            y = 1 - (x * x);
            z = (2.0 * j / 9.0) - 1.0;

            x1 = (2.0 * (i + 1)/ 9.0) - 1.0;
            y1 = 1 - (x1 * x1);
            z1 = (2.0 * j / 9.0) - 1.0;

            x2 = (2.0 * (i + 1)/ 9.0) - 1.0;
            y2 = 1 - (x2 * x2);
            z2 = (2.0 * (j + 1)/ 9.0) - 1.0;

            x3 = (2.0 * i / 9.0) - 1.0;
            y3 = 1 - (x3 * x3);
            z3 = (2.0 * (j + 1)/ 9.0) - 1.0;

            glVertex3f(x, y, z);
            glVertex3f(x1, y1, z1);
            glVertex3f(x2, y2, z2);
            glVertex3f(x3, y3, z3);
       }
        glEnd();
    }
}

void drawPreenche3(void) {
    int linhas = 50;
    float angle;
    glBegin(GL_POLYGON);
    for(int i = 0; i < linhas; i++){
        angle = (i*2.0*M_PI)/linhas;
        glVertex2f(0.0 + (cos(angle)*1.0),0.0 + (sin(angle)*1.0));
    }
    glEnd();
}

void drawPlantacao() {
  glDisable(GL_TEXTURE_2D);

    glPushMatrix();

      glPushMatrix();
        glColor3f((float) 232/255, (float) 209/255, (float) 115/255);
        glPushMatrix();
            drawPreenche3();
        glPopMatrix();

        glColor3f((float) 185/255, (float) 103/255, (float) 50/255);
        glPushMatrix();
            glTranslatef(0.0, 0.0,0.13);
            glRotatef(90,1.0,0.0,0.0);
            glScalef(0.9,0.13,0.9);
            drawCylinder();
        glPopMatrix();

        glColor3f((float) 232/255, (float) 209/255, (float) 115/255);
        glPushMatrix();
            glTranslatef(0.0, 0.0,0.3);
            glRotatef(90,1.0,0.0,0.0);
            glScalef(0.9,0.05,0.9);
            drawCylinder();
        glPopMatrix();

        glColor3f((float) 172/255, (float) 89/255, (float) 45/255);
        glPushMatrix();
             glTranslatef(0.0, 0.0,0.33);
             glScalef(0.88,0.88,0.88);
             drawPreenche3();
        glPopMatrix();

        glColor3f((float) 35/255, (float) 142/255, (float) 35/255);
        glPushMatrix();
            glTranslatef(0.0, 0.0,0.45);
            glRotatef(90,0.0,1.0,0.0);
            glRotatef(90,0.0,0.0,1.0);
            glScalef(0.12,0.3,0.02);

            glPushMatrix();
                glPushMatrix();
                    glTranslatef(-1.2, 0.0, 1.0);
                    drawfolhas();
                glPopMatrix();

                glPushMatrix();
                    glTranslatef(1.2, 0.0, 1.0);
                    glRotatef(-180,0.0,1.0,0.0);
                    drawfolhas();
                glPopMatrix();

             glPopMatrix();

         glPopMatrix();
       glPopMatrix();

    glPopMatrix();

  glEnable(GL_TEXTURE_2D);
}

void genPernas(float i, float j, float *vertex){
	float x = cos(2.0*3.14*i);
	float y = -1.0 +2.0*j;
	float z = sin(2.0*3.14*i);

	vertex[0] = x;
	vertex[1] = y;
	vertex[2] = z;
}

void drawMadeira(void) {

    glBegin(GL_QUADS);
        glVertex3f(4.0, 2.0, 1.0);
        glVertex3f(4.0, 2.0,-1.0);
        glVertex3f(4.0,-2.0,-1.0);
        glVertex3f(4.0,-2.0, 1.0);
    glEnd();
    
    glBegin(GL_QUADS);
        glVertex3f( 4.0, 2.0, 1.0);
        glVertex3f(-4.0, 2.0, 1.0);
        glVertex3f(-4.0, 2.0,-1.0);
        glVertex3f( 4.0, 2.0,-1.0);
    glEnd();
    
    glBegin(GL_QUADS);
        glVertex3f( 4.0,-2.0, 1.0);
        glVertex3f(-4.0,-2.0, 1.0);
        glVertex3f(-4.0,-2.0,-1.0);
        glVertex3f( 4.0,-2.0,-1.0);
    glEnd();
    
    glBegin(GL_QUADS);
        glVertex3f( 4.0,-2.0,1.0);
        glVertex3f( 4.0, 2.0,1.0);
        glVertex3f(-4.0, 2.0,1.0);
        glVertex3f(-4.0,-2.0,1.0);
    glEnd();
    
    glBegin(GL_QUADS);
        glVertex3f( 4.0, 2.0,-1.0);
        glVertex3f( 4.0,-2.0,-1.0);
        glVertex3f(-4.0,-2.0,-1.0);
        glVertex3f(-4.0, 2.0,-1.0);
    glEnd();
    
    glBegin(GL_QUADS);
        glVertex3f(-4.0, 2.0, 1.0);
        glVertex3f(-4.0,-2.0, 1.0);
        glVertex3f(-4.0,-2.0,-1.0);
        glVertex3f(-4.0, 2.0,-1.0);
    glEnd();
}

void drawPernas(){
  int i;
  int j;
  const int h_div = 5;
  const int v_div = 5;
   glRotatef(90,0.0,1.0,0.0);
   glRotatef(-90,1.0,0.0,0.0);

  for(j = 0; j < v_div; j++) {
    for(i = 0; i < h_div; i++) {

        glBegin(GL_QUADS);
          float vertex[3];
          genPernas((float)i/h_div, (float)j/v_div, vertex);
          glVertex3fv(vertex);
          genPernas((float)(i+1)/h_div, (float)j/v_div, vertex);
          glVertex3fv(vertex);
          genPernas((float)(i+1)/h_div, (float)(j+1)/v_div, vertex);
          glVertex3fv(vertex);
          genPernas((float)i/h_div, (float)(j+1)/v_div, vertex);
          glVertex3fv(vertex);
        glEnd();
    }
  }
}

void drawBanco(void){
  glDisable(GL_TEXTURE_2D);
  glPushMatrix();

        glColor3f((float) 172/255, (float) 89/255, (float) 45/255);

        glPushMatrix();
            glTranslatef(0.2, -0.3, 0.8);
            glRotatef(90, 0.0, 0.0, 1.0);
            glRotatef(45.0, 1.0, 0.0, 1.0);
            glScalef(0.1, 0.1, 0.1);
            glScalef(3.0, 0.5, 0.5);
            drawPernas();
        glPopMatrix();
        
        glPushMatrix();
            glTranslatef(-0.2, -0.3, 0.8);
            glRotatef(90, 0.0, 0.0, 1.0);
            glRotatef(45.0, 1.0, -0.0, -1.0);
            glScalef(0.1, 0.1, 0.1);
            glScalef(3.0, 0.5, 0.5);
            drawPernas();
        glPopMatrix();
        
        glPushMatrix();
            glTranslatef(0.2, -0.3, -0.9);
            glRotatef(90, 0.0, 0.0, 1.0);
            glRotatef(45.0, 1.0, 0.0, 1.0);
            glScalef(0.1, 0.1, 0.1);
            glScalef(3.0, 0.5, 0.5);
            drawPernas();
        glPopMatrix();
        
        glPushMatrix();
            glTranslatef(-0.2, -0.3, -0.8);
            glRotatef(90, 0.0, 0.0, 1.0);
            glRotatef(45.0, 1.0, -0.0, -1.0);
            glScalef(0.1, 0.1, 0.1);
            glScalef(3.0, 0.5, 0.5);
            drawPernas();
        glPopMatrix();

        glPushMatrix();
            glScalef(0.1, 0.1, 1.0);
            glScalef(1.5, 0.3, 1.0);
            drawMadeira();
        glPopMatrix();

       glPushMatrix();
       	    glRotatef(90.0, 0.0, 0.0, 1.0);
            glTranslatef(-0.2, 0.0, 0.0);
            glScalef(0.1, 0.1, 1.0);
            glScalef(1.0, 0.3, 1.0);
            glScalef(0.3, 0.3, 1.0);
            drawMadeira();
        glPopMatrix();


    glPopMatrix();
    glEnable(GL_TEXTURE_2D);
}