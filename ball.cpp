#include "Model_OBJ.h"
#include <time.h>
#include <iostream>

using namespace std;

class Ball {
public:
    double YAW = 0.0, PITCH = 0.0, ROLL = 0.0;
    double VROLL = 0.0, VPITCH = 0.0, VYAW = 0.0;
    double VX = 0.0, VY = 0.0, VZ = 0.0;
    float PX = 0.0, PY = 0.0, PZ = 0.0;
    float PPX = 0.0, PPY = 0.0, PPZ = 0.0;
    double RX=0.0, RZ=0.0, RY=0.0;
    float HELICE;
    bool ATIRANDO = true;
    float X = 0.0;
    
    Model_OBJ zepilin;
    Model_OBJ arma;
    Model_OBJ helice;
    Model_OBJ core;
    
    Ball();
    void Desenha();
    void atualiza_ball();
    void calcula_velocidade();
    void atirando();
    void hit();
};

Ball::Ball(){
    PX = (rand()%40)-20; PZ = 25;
    zepilin.Load("obejetos/zepilin.obj");
    arma.Load("obejetos/arma.obj");
    helice.Load("obejetos/helice.obj");
    core.Load("obejetos/core.obj");
}

void Ball::hit(){
    PX = (rand()%40)-20; PZ = 25;
    VZ = 0.0;
}

void Ball::Desenha() {
    glPushMatrix();
    glTranslatef(PX, PY, PZ);
    
    glPushMatrix();
    glMaterialfv(GL_FRONT,GL_AMBIENT, copper_amb);
    glMaterialfv(GL_FRONT,GL_DIFFUSE, copper_dif);
    glMaterialfv(GL_FRONT,GL_SPECULAR, copper_spe);
    glMaterialf(GL_FRONT,GL_SHININESS, copper_shi);
    glRotatef(90,0.0,1.0,0.0);
    glTranslatef(1.0,2.0,-1.3);
    arma.Draw();
    glPopMatrix();
    
    glPushMatrix();
    glMaterialfv(GL_FRONT,GL_AMBIENT, copper_amb);
    glMaterialfv(GL_FRONT,GL_DIFFUSE, copper_dif);
    glMaterialfv(GL_FRONT,GL_SPECULAR, copper_spe);
    glMaterialf(GL_FRONT,GL_SHININESS, copper_shi);
    glRotatef(90,0.0,1.0,0.0);
    glTranslatef(1.0,2.0,1.3);
    arma.Draw();
    glPopMatrix();
    
    glPushMatrix();
    glMaterialfv(GL_FRONT,GL_AMBIENT,cyan_amb);
    glMaterialfv(GL_FRONT,GL_DIFFUSE,cyan_dif);
    glMaterialfv(GL_FRONT,GL_SPECULAR,cyan_spe);
    glMaterialf(GL_FRONT,GL_SHININESS,cyan_shi);
    glTranslatef(0.0,2.0,0.0);
    zepilin.Draw();
    glPopMatrix();
    
    glPushMatrix();
    glMaterialfv(GL_FRONT,GL_AMBIENT,black_rubber_amb);
    glMaterialfv(GL_FRONT,GL_DIFFUSE,black_rubber_dif);
    glMaterialfv(GL_FRONT,GL_SPECULAR,black_rubber_spe);
    glMaterialf(GL_FRONT,GL_SHININESS,black_rubber_shi);
    glTranslatef(0.0,3.0,0.0);
    glScalef(4.0,2.0,4.0);
    glRotatef(HELICE,0.0,1.0,0.0);
    helice.Draw();
    glPopMatrix();
    
    glPopMatrix();
}

void Ball::atualiza_ball(){
    srand (time(NULL)+10);
    PX += VX;   PY += VY;   PZ += VZ;
    ROLL += VROLL;
    PITCH += VPITCH;
    YAW += VYAW;

    if(!(abs(PX)<25.0))
        PX -= VX;
    
    if(!(abs(PZ)<25.0))
        PZ -= VZ;
    
    HELICE += 30;
    
    if(PZ <= -24.0){
        PX = (rand()%20); PZ = 25.0;
        VZ = 0.0;
    }
    
    if(X == 0){
        PPX = PX; PPY = PY; PPZ = PZ;
    }
    
    if(ATIRANDO){
        if(X >= 20) {
            PPX = PX; PPY = PY; PPZ = PZ;
            X = 0.0;
        } else {
            X += 0.6;
        }
    }
}

void Ball::calcula_velocidade() {
    VZ -= 0.001;
    
    RX = (pow(RESISTENCIA,abs(VX))-1.0)*F_RESISTENCIA_AR;
    RZ = (pow(RESISTENCIA,abs(VZ))-1.0)*F_RESISTENCIA_AR;
    
    if(VROLL>10)    VROLL -= 0.1;
    else            VROLL += 0.1;
    
    if(VYAW>10)     VYAW -= 0.1;
    else            VYAW += 0.1;
    
    if(VX>RX)           VX -= RX;
    else if(VX<-RX)     VX += RX;
    
    if(VZ>RZ)          VZ -= RZ;
    else if(VZ<-RZ)    VZ += RZ;

}

void Ball::atirando(){
    glPushMatrix();
    glMaterialfv(GL_FRONT,GL_AMBIENT, copper_amb);
    glMaterialfv(GL_FRONT,GL_DIFFUSE, copper_dif);
    glMaterialfv(GL_FRONT,GL_SPECULAR, copper_spe);
    glMaterialf(GL_FRONT,GL_SHININESS, copper_shi);
    glTranslatef(PPX, PPY, PPZ);
    
    glPushMatrix();
    glRotatef(90,0.0,1.0,0.0);
    glTranslatef(X,2.0,-1.3);
    core.Draw();
    glPopMatrix();
    
    glPushMatrix();
    glRotatef(90,0.0,1.0,0.0);
    glTranslatef(X,2.0,1.3);
    core.Draw();
    glPopMatrix();
    
    glPopMatrix();
}

