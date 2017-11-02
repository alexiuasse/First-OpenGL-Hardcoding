#include "Model_OBJ.h"
#include <time.h>
#include <iostream>

using namespace std;

class Asteroide {
public:
    double YAW = 0.0, PITCH = 0.0, ROLL = 0.0;
    double VROLL = 0.0, VPITCH = 0.0, VYAW = 0.0;
    double VX = 0.0, VY = 0.0, VZ = 0.0;
    float PX = 0.0, PY = 2.0, PZ = 0.0;
    double RX=0.0, RZ=0.0, RY=0.0;
    
    Model_OBJ core;
    
    Asteroide();
    void Desenha();
    void atualiza_asteroide();
    void calcula_velocidade();
    void hit();
};

Asteroide::Asteroide(){
    srand (time(NULL));
    PX = (rand()%40)-20; PZ = 25; PY = 2.0;
    core.Load("obejetos/core.obj");
}

void Asteroide::hit(){
    PX = (rand()%40)-20; PZ = 25; PY = 2.0;
    VZ = 0.0;
}
void Asteroide::Desenha() {
    glPushMatrix();
    glTranslatef(PX, PY, PZ);
    glRotatef(YAW, 0.0, 1.0, 0.0);
    glRotatef(ROLL, 0.0, 0.0, 1.0);
    glRotatef(PITCH, 1.0, 0.0, 0.0);
    glMaterialfv(GL_FRONT,GL_AMBIENT, rubi_amb);
    glMaterialfv(GL_FRONT,GL_DIFFUSE, rubi_dif);
    glMaterialfv(GL_FRONT,GL_SPECULAR, rubi_spe);
    glMaterialf(GL_FRONT,GL_SHININESS, rubi_shi);
    glScalef(5.0,5.0,5.0);
    core.Draw();
    glPopMatrix();
}

void Asteroide::atualiza_asteroide(){
    srand (time(NULL));
    PX += VX;   PY += VY;   PZ += VZ;
    ROLL += VROLL;
    PITCH += VPITCH;
    YAW += VYAW;

    if(!(abs(PX)<=25.0))
        PX -= VX;
    
    if(!(abs(PZ)<=25.0))
        PZ -= VZ;
    
    if(PZ <= -24.0){
        PX = (rand()%40)-20; PY = 2.0; PZ = 25.0;
        VZ = 0.0;
    }
    
//     printf("%f // %f // %f\n",PX,PY,PZ);
//     printf("%f // %f // %f\n",VX,VY,VZ);
    
}

void Asteroide::calcula_velocidade() {
//     srand((unsigned)time(0));
//     srand (static_cast <unsigned> (time(0)));
    VZ -= 0.002;
//     srand (time(NULL));
//     int t;
//     t = (rand() % 1);
//     if( t < 3 ) {
//         VZ -= 0.001;
//     }else if( t >= 3 and t < 5){
//         VX -= 0.001;
//     }else if( t >= 5 and t < 7){
//         VZ += 0.001;
//     }else if( t >= 7 and t < 9){
//         VX += 0.001;
//     }
//     
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
