#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <time.h>
#include <stdlib.h>

#include "openglMaterial.h"
#include "drone.cpp"
#include "asteroide.cpp"
#include "ball.cpp"
#include "minhoca.cpp"
#include "Model_OBJ.h"
#include "insect.cpp"
#include <SOIL/SOIL.h>

using namespace std;

float luz_x=0.0, luz_z=0.0, luz_y=10.0;  // posição da luz
unsigned char *textura; 
GLuint *texturas;
float DX,DY,DZ,D;

Drone drone;
Asteroide asteroide;
Ball ball;
// std::vector<Ball*> balls;
Minhoca minhoca;
Insect insect;

void luz();
void camera();
void resize(int w, int h);
void animacao(int value);
void colision();
void Keyboard(unsigned char key, int x, int y);

void colision(){
    DX = drone.PPX - asteroide.PX;
    DZ = (drone.PPZ+abs(drone.X)) - asteroide.PZ;
    D = sqrt((DX*DX) + (DZ*DZ));
    if(D <= 3)   asteroide.hit();
    
    DX = drone.PPX - ball.PX;
    DZ = (drone.PPZ+abs(drone.X)) - ball.PZ;
    D = sqrt((DX*DX) + (DZ*DZ));
    if(D <= 3)   ball.hit();
    
    DX = ball.PPX - drone.PX;
    DZ = (ball.PPZ-ball.X) - drone.PZ;
    D = sqrt((DX*DX) + (DZ*DZ));
    if(D <= 3)   drone.hit();
}

void display(void) {
    //Limpa os buffers de cor e profundidade
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //Seleciona matriz de modelagem
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    camera();
    luz();
//     colision();

    glPushMatrix();
    glRotatef(90,0.0,1.0,0.0);
    insect.Desenha();
    insect.atualiza_insect();
    insect.calcula_velocidade_insect();
    glPopMatrix();
    
    drone.calcula_velocidade();
    drone.atualiza_drone();
    if(drone.ATIRANDO)
        drone.atirando();
    drone.Desenha();
//     luz_x = drone.PX;
//     luz_z = drone.PZ;
//     
    minhoca.atualiza_minhoca();
    minhoca.calcula_velocidade();
    if((minhoca.hit(drone.PPX-1.3, drone.PPZ, drone.PPY, drone.X)) or       (minhoca.hit(drone.PPX+1.3, drone.PPZ, drone.PPY, drone.X)) or (minhoca.hit(drone.PPX, drone.PPZ, drone.PPY, drone.X)) or (minhoca.hit(drone.PPX+2.5, drone.PPZ, drone.PPY, drone.X)) or (minhoca.hit(drone.PPX-2.5, drone.PPZ, drone.PPY, drone.X))){
        if(drone.X == 0)
            drone.hit();
//         drone.STOP = true;
//         drone.ATIRANDO = false;
//         drone.X = 0;
    }else{
//         drone.STOP = false;
    }
    
    glPushMatrix();
    glRotatef(90,0.0,1.0,0.0);
    minhoca.Desenha();
    glPopMatrix();
    
//     asteroide.calcula_velocidade();
//     asteroide.atualiza_asteroide();
//     asteroide.Desenha();
//     
//     ball.calcula_velocidade();
//     ball.atualiza_ball();
//     ball.atirando();
//     ball.Desenha();
    
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texturas[0]);
    glEnable(GL_COLOR_MATERIAL);
    glBegin(GL_POLYGON);
    glNormal3f(0.0,1.0,0.0);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(-MAX_AREA,0.0,MAX_AREA);
    glTexCoord2f(1.0, 0.0);
    glVertex3f(MAX_AREA,0.0,MAX_AREA);
    glTexCoord2f(1.0, 1.0);
    glVertex3f(MAX_AREA,0.0,-MAX_AREA);
    glTexCoord2f(0.0, 1.0);
    glVertex3f(-MAX_AREA,0.0,-MAX_AREA);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_COLOR_MATERIAL);
    
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texturas[1]);
    glEnable(GL_COLOR_MATERIAL);
    glBegin(GL_POLYGON);
    glNormal3f(0.0,0.0,1.0);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(-MAX_AREA,MAX_AREA-10,MAX_AREA);
    glTexCoord2f(1.0, 0.0);
    glVertex3f(MAX_AREA,MAX_AREA-10,MAX_AREA);
    glTexCoord2f(1.0, 1.0);
    glVertex3f(MAX_AREA,0.0,MAX_AREA);
    glTexCoord2f(0.0, 1.0);
    glVertex3f(-MAX_AREA,0.0,MAX_AREA);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_COLOR_MATERIAL);
    
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texturas[1]);
    glEnable(GL_COLOR_MATERIAL);
    glBegin(GL_POLYGON);
    glNormal3f(1.0,0.0,0.0);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(MAX_AREA,MAX_AREA-10,MAX_AREA);
    glTexCoord2f(1.0, 0.0);
    glVertex3f(MAX_AREA,MAX_AREA-10,-MAX_AREA);
    glTexCoord2f(1.0, 1.0);
    glVertex3f(MAX_AREA,0.0,-MAX_AREA);
    glTexCoord2f(0.0, 1.0);
    glVertex3f(MAX_AREA,0.0,MAX_AREA);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_COLOR_MATERIAL);
    
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texturas[1]);
    glEnable(GL_COLOR_MATERIAL);
    glBegin(GL_POLYGON);
    glNormal3f(1.0,0.0,0.0);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(-MAX_AREA,MAX_AREA-10,MAX_AREA);
    glTexCoord2f(1.0, 0.0);
    glVertex3f(-MAX_AREA,MAX_AREA-10,-MAX_AREA);
    glTexCoord2f(1.0, 1.0);
    glVertex3f(-MAX_AREA,0.0,-MAX_AREA);
    glTexCoord2f(0.0, 1.0);
    glVertex3f(-MAX_AREA,0.0,MAX_AREA);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_COLOR_MATERIAL);
    
    glutSwapBuffers();
}

void Keyboard (unsigned char key, int x, int y) {
    switch (key) {
        case 'd':   drone.DIREITA = true;     break;
        case 'a':   drone.ESQUERDA = true;    break;
        case 'w':   drone.FRENTE = true;      break;
        case 's':   drone.TRAS = true;        break;
        case ' ':   drone.ATIRANDO = true;    break;
        default:                              break;
    }
}

void KeyboardUP (unsigned char key, int x, int y) {
    switch (key) {
        case 'd':   drone.DIREITA = false;    break;
        case 'a':   drone.ESQUERDA = false;   break;
        case 'w':   drone.FRENTE = false;     break;
        case 's':   drone.TRAS = false;       break;
        case ' ':   drone.ATIRANDO = false;   break;
        default:                              break;
    }
}

void resize(int w, int h) {
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(65.0, (GLdouble) w/h,1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
//     gluLookAt(0.0, 7.0, 10.0,
//         0.0, 0.0, 0.0,
//         0.0, 1.0, 0.0);
}

void animacao(int value) {
    if((drone.COG += 10) >= 360){
        drone.COG = 0;
    };
    if((abs(drone.HELICE -= 10)) >= 360){
        drone.HELICE = 0;
    };
    glutPostRedisplay();
    glutTimerFunc(30, animacao,1);
}

void init (void) {
    glClearColor (0.0, 0.0, 0.0, 0.0);
    glEnable( GL_DEPTH_TEST );
    glDepthFunc(GL_LESS);
    glEnable(GL_LIGHTING);		//Liga iluminação
    glEnable( GL_LIGHT0 );		//Liga luz 0
    glShadeModel( GL_SMOOTH );		//Suaviza normais
    glEnable(GL_NORMALIZE);
    
    texturas = new GLuint[3];
    glGenTextures(3, texturas);
    int width = 512, height = 512;
    
    textura = SOIL_load_image("floor.jpg", &width, &height, 0, SOIL_LOAD_RGB);
    
    glBindTexture(GL_TEXTURE_2D, texturas[0]);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, textura);
    
    textura = SOIL_load_image("front.jpg", &width, &height, 0, SOIL_LOAD_RGB);
    glBindTexture(GL_TEXTURE_2D, texturas[1]);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, textura);
    
    
    GLfloat p[4] = {1.0, 1.0, 0.0, 1.0};
    glTexGenfv(GL_S, GL_OBJECT_PLANE, p);
    glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
    glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
    
}

void luz(){
//     GLfloat desligado[] = { 0.0, 0.0, 0.0, 1.0};
    GLfloat amb_light[] = { 0.3, 0.3, 0.3, 1.0 };
    GLfloat diffuse[] = { 0.9, 0.9, 0.9, 1.0 };
    GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_position[] = {luz_x, luz_y, luz_z, 1.0};
    glLightModelfv( GL_LIGHT_MODEL_AMBIENT, amb_light );
    glLightfv( GL_LIGHT0, GL_AMBIENT, amb_light );
    glLightfv( GL_LIGHT0, GL_DIFFUSE, diffuse );
    glLightfv( GL_LIGHT0, GL_SPECULAR, specular );
    glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.01);
    glLightfv( GL_LIGHT0, GL_POSITION, light_position);
    
//     GLfloat light_position1[] = {drone.PX, 5.0, drone.PZ, 1.0};
//     glLightModelfv( GL_LIGHT_MODEL_AMBIENT, amb_light );
//     glLightfv( GL_LIGHT1, GL_AMBIENT, amb_light );
//     glLightfv( GL_LIGHT1, GL_DIFFUSE, diffuse );
//     glLightfv( GL_LIGHT1, GL_SPECULAR, specular );
//     glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.01);
//     glLightfv( GL_LIGHT1, GL_POSITION, light_position1);
   
}

void camera(){
    gluLookAt(  drone.PX, 3.0, -8.0+drone.PZ,
                drone.PX, drone.PY, drone.PZ,
                0.0, 1.0, 0.0           );
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize (1000, 500); 
    glutInitWindowPosition (500, 500);
    glutCreateWindow ("The Game");
    init ();    luz ();
    glEnable(GL_DEPTH_TEST);
    glutDisplayFunc(display); 
    glutReshapeFunc(resize);
    glutTimerFunc(30,animacao,1);
    glutKeyboardFunc(Keyboard);
    glutKeyboardUpFunc(KeyboardUP);

    srand (time(NULL));

    glutMainLoop();

    return 0;
}
