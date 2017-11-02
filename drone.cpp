#include "Model_OBJ.h"
#include "raio.cpp"
#include <iostream>

#define PROJETIL 0.5
#define POX 0.6
#define POY 1.0
using namespace std;

class Drone {
public:
    bool DIREITA = false, ESQUERDA = false; // mover direita esqerda
    bool FRENTE = false , TRAS = false;     // mover frente tras
    bool BARRELROLL = false;
    float HELICE = 0.0;                     // fazer helice girar
    float COG = 0.0;                        // fazer cog girar
    float MOTOR_DIREITO = 0.0;              // rotacionar motor direito
    float MOTOR_ESQUERDO = 0.0;             // rotacionar motor esquerdo
    float MOTOR_TRASEIRO = 0.0;             // rotacionar motor tras
    float VMOTOR_DIREITO = 0.0;              // rotacionar motor direito
    float VMOTOR_ESQUERDO = 0.0;             // rotacionar motor esquerdo
    float VMOTOR_TRASEIRO = 0.0;             // rotacionar motor tras
    double YAW = 0.0, PITCH = 0.0, ROLL = 0.0;    // rotação
    double PYAW = 0.0, PPITCH = 0.0, PROLL = 0.0;    // rotação
    double VROLL = 0.0;
    double VX = 0.0, VY = 0.0, VZ = 0.0;    // velocidade para armazenar posição
    float PX = 0.0, PY = 0.0, PZ = 0.0;
    float PPX = 100.0, PPY = 1.0, PPZ = 100.0;
    double RX=0.0, RZ=0.0, RY=0.0;
    bool ATIRANDO = false, STOP = false;
    float X = 0.0;
    
    Raio raio;
    
    Model_OBJ helice;
    Model_OBJ motor;
    Model_OBJ cockpit;
    Model_OBJ cog;
    Model_OBJ core;
    Model_OBJ arma;
    
    Drone();
    void Desenha();
    void desenha_cog3(float X, float Y, float Z);
    void desenha_cog2(float X, float Y, float Z);
    void desenha_cog1(float X, float Y, float Z);
    void desenha_cog(float X, float Y, float Z);
    void atualiza_drone();
    void calcula_velocidade();
    void atirando();
    void hit();
};

Drone::Drone(){
    helice.Load("obejetos/helice.obj");
    motor.Load("obejetos/motor.obj");
    cockpit.Load("obejetos/cockpit.obj");
    cog.Load("obejetos/cog1.obj");
    core.Load("obejetos/core.obj");
    arma.Load("obejetos/arma.obj");
}

void Drone::desenha_cog3(float X, float Y, float Z) {
    glPushMatrix();
    glTranslatef(X, Y, Z);
    glRotatef(90,1.0,0.0,0.0);
    glRotatef(COG,1.0,0.0,0.0);
    cog.Draw();
    glPopMatrix();
}

void Drone::desenha_cog2(float X, float Y, float Z) {
    glPushMatrix();
    glTranslatef(X, Y, Z);
    glRotatef(COG,0.0,1.0,1.0);
    cog.Draw();
    glPopMatrix();
}

void Drone::desenha_cog1(float X, float Y, float Z) {
    glPushMatrix();
    glTranslatef(X, Y, Z);
    glRotatef(COG,0.0,0.0,1.0);
    cog.Draw();
    glPopMatrix();
}

void Drone::desenha_cog(float X, float Y, float Z) {
    desenha_cog1(X,Y,Z);
    desenha_cog2(X,Y,Z);
    desenha_cog3(X,Y,Z);
}

void Drone::Desenha() {
    glPushMatrix();
    
    glTranslatef(PX, PY, PZ);
    glRotatef(YAW, 0.0, 1.0, 0.0);
    glRotatef(ROLL, 0.0, 0.0, 1.0);
    
    glMaterialfv(GL_FRONT,GL_AMBIENT,scyan_amb);
    glMaterialfv(GL_FRONT,GL_DIFFUSE,scyan_dif);
    glMaterialfv(GL_FRONT,GL_SPECULAR,scyan_spe);
    glMaterialf(GL_FRONT,GL_SHININESS,scyan_shi);
    
    glPushMatrix();
    glTranslatef(1.2,POY,0.8);
    glRotatef(90,0.0,1.0,0.0);
    glRotatef(COG,1.0,0.0,0.0);
    glScalef(4.5,0.6,0.5);
    core.Draw();
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(-1.2,POY,0.8);
    glRotatef(-90,0.0,1.0,0.0);
    glRotatef(COG,1.0,0.0,0.0);
    glScalef(4.5,0.6,0.5);
    core.Draw();
    glPopMatrix();
    
    glMaterialfv(GL_FRONT,GL_AMBIENT, chrome_amb);
    glMaterialfv(GL_FRONT,GL_DIFFUSE, chrome_dif);
    glMaterialfv(GL_FRONT,GL_SPECULAR, chrome_spe);
    glMaterialf(GL_FRONT,GL_SHININESS, chrome_shi);
    
    glPushMatrix();
    glTranslatef(1.2,POY,1.0);
    glRotatef(-90,0.0,1.0,0.0);
    glRotatef(COG,1.0,0.0,0.0);
    arma.Draw();
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(-1.2,POY,1.0);
    glRotatef(-90,0.0,1.0,0.0);
    glRotatef(COG,1.0,0.0,0.0);
    arma.Draw();
    glPopMatrix();
    
    glRotatef(PITCH, 1.0, 0.0, 0.0);
    
    glPushMatrix();
    glTranslatef(-2.5,POY,0.0);
    glRotatef(MOTOR_DIREITO,1.0,0.0,0.0);
    motor.Draw();
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(2.5,POY,0.0);
    glRotatef(MOTOR_ESQUERDO,1.0,0.0,0.0);
    motor.Draw();
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0.0,POY,-2.5);
    glRotatef(MOTOR_TRASEIRO,0.0,0.0,1.0);
    motor.Draw();
    glPopMatrix();
    
    glMaterialfv(GL_FRONT,GL_AMBIENT, rubi_amb);
    glMaterialfv(GL_FRONT,GL_DIFFUSE, rubi_dif);
    glMaterialfv(GL_FRONT,GL_SPECULAR, rubi_spe);
    glMaterialf(GL_FRONT,GL_SHININESS, rubi_shi);
    
    glPushMatrix();
    glTranslatef(-2.5,POY,0.0);
    glRotatef(HELICE,0.0,1.0,0.0);
    helice.Draw();
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(2.5,POY,0.0);
    glRotatef(HELICE,0.0,1.0,0.0);
    helice.Draw();
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0.0,POY,-2.5);
    glRotatef(HELICE,0.0,1.0,0.0);
    helice.Draw();
    glPopMatrix();

    glMaterialfv(GL_FRONT,GL_AMBIENT, rubi_amb);
    glMaterialfv(GL_FRONT,GL_DIFFUSE, rubi_dif);
    glMaterialfv(GL_FRONT,GL_SPECULAR, rubi_spe);
    glMaterialf(GL_FRONT,GL_SHININESS, rubi_shi);
    
    glPushMatrix();
    glTranslatef(0.0, POY, 0.0);
    cockpit.Draw();
    glPopMatrix(); 
    
    glMaterialfv(GL_FRONT,GL_AMBIENT, ouro_amb);
    glMaterialfv(GL_FRONT,GL_DIFFUSE, ouro_dif);
    glMaterialfv(GL_FRONT,GL_SPECULAR, ouro_spe);
    glMaterialf(GL_FRONT,GL_SHININESS, ouro_shi);
    desenha_cog(0.0,POY,0.0);
    
    glMaterialfv(GL_FRONT,GL_AMBIENT, crubi_amb);
    glMaterialfv(GL_FRONT,GL_DIFFUSE, crubi_dif);
    glMaterialfv(GL_FRONT,GL_SPECULAR, crubi_spe);
    glMaterialf(GL_FRONT,GL_SHININESS, crubi_shi);
    glPushMatrix();
    glTranslatef(0.0, POY, 0.0);
    core.Draw();
    glPopMatrix();
    
    glMaterialfv(GL_FRONT,GL_AMBIENT,scyan_amb);
    glMaterialfv(GL_FRONT,GL_DIFFUSE,scyan_dif);
    glMaterialfv(GL_FRONT,GL_SPECULAR,scyan_spe);
    glMaterialf(GL_FRONT,GL_SHININESS,scyan_shi);
    
//     glPushMatrix();
//     glRotatef(-90,0.0,1.0,0.0);
//     glRotatef(COG,0.0,1.0,0.0);
//     glTranslatef(-0.2,POY,1.0);
//     glScalef(0.3,0.3,0.3);
//     core.Draw();
//     glPopMatrix();
//     
//     glPushMatrix();
//     glRotatef(90,0.0,1.0,0.0);
//     glRotatef(COG,0.0,1.0,0.0);
//     glTranslatef(0.2,POY,1.0);
//     glScalef(0.3,0.3,0.3);
//     core.Draw();
//     glPopMatrix();
//     
//     glPushMatrix();
//     glTranslatef(-2.5,POY,0.0);
//     glScalef(0.3,0.3,0.3);
//     core.Draw();
//     glPopMatrix();
//     
//     glPushMatrix();
//     glTranslatef(2.5,POY,0.0);
//     glScalef(0.3,0.3,0.3);
//     core.Draw();
//     glPopMatrix();
//     
//     glPushMatrix();
//     glTranslatef(0.0,POY,-2.5);
//     glScalef(0.3,0.3,0.3);
//     core.Draw();
//     glPopMatrix();
    
    glPopMatrix();
}

void Drone::hit(){
    PX = 0.0, PZ = 0.0;
    VX = 0.0; VZ = 0.0;
}

void Drone::atualiza_drone(){
    PX += VX;   PY += VY;   PZ += VZ;
    MOTOR_DIREITO  += VMOTOR_DIREITO;
    MOTOR_ESQUERDO += VMOTOR_ESQUERDO;
    MOTOR_TRASEIRO += VMOTOR_TRASEIRO;
    ROLL += VROLL;
    
    if(!(abs(PX) <= MAX_AREA-5))      PX -= VX;
    if(!(abs(PZ) <= MAX_AREA-5))      PZ -= VZ;
    
    if(ROLL >= MAX_ANGULO){
        ROLL = MAX_ANGULO;
        VROLL = 0.0;
    }
    if(ROLL <= -MAX_ANGULO){
        ROLL = -MAX_ANGULO;
        VROLL = 0.0;
    }
    
    if(MOTOR_DIREITO >= MAX_ANGULO){
        MOTOR_DIREITO = MAX_ANGULO;
        VMOTOR_DIREITO = 0.0;
    }
    if(MOTOR_DIREITO <= -MAX_ANGULO){
        MOTOR_DIREITO = -MAX_ANGULO;
        VMOTOR_DIREITO = 0.0;
    }
    if(MOTOR_ESQUERDO >= MAX_ANGULO){
        MOTOR_ESQUERDO = MAX_ANGULO;
        VMOTOR_ESQUERDO = 0.0;
    }
    if(MOTOR_ESQUERDO <= -MAX_ANGULO){
        MOTOR_ESQUERDO = -MAX_ANGULO;
        VMOTOR_ESQUERDO = 0.0;
    }
    if(MOTOR_TRASEIRO >= MAX_ANGULO*1.5){
        MOTOR_TRASEIRO = MAX_ANGULO*1.5;
        VMOTOR_TRASEIRO = 0.0;
    }
    if(MOTOR_TRASEIRO <= -MAX_ANGULO*1.5){
        MOTOR_TRASEIRO = -MAX_ANGULO*1.5;
        VMOTOR_TRASEIRO = 0.0;
    }
    
    if(ROLL > 0)            ROLL -= 1;
    if(ROLL < 0)            ROLL += 1;
    if(MOTOR_ESQUERDO > 0)  MOTOR_ESQUERDO -= 1;
    if(MOTOR_ESQUERDO < 0)  MOTOR_ESQUERDO += 1;
    if(MOTOR_DIREITO > 0)   MOTOR_DIREITO  -= 1;
    if(MOTOR_DIREITO < 0)   MOTOR_DIREITO  += 1;
    if(MOTOR_TRASEIRO > 0)  MOTOR_TRASEIRO -= 1;
    if(MOTOR_TRASEIRO < 0)  MOTOR_TRASEIRO += 1;
    
    if(!STOP){
        
        if(X == 0){
            PPX = PX; PPY = PY; PPZ = PZ;
            PROLL = ROLL; PYAW = YAW; PPITCH = PITCH;
        }
        
        if(!ATIRANDO and abs(X) > 0){
            ATIRANDO = true;
//             if(X <= -20) {
//                 PPX = PX; PPY = PY; PPZ = PZ;
//                 PROLL = ROLL; PYAW = YAW; PPITCH = PITCH;
//                 X = 0.0;
//                 ATIRANDO = false;
//             } else {
//                 X -= PROJETIL;
//             }
        }
        
        if(ATIRANDO){
            if(X <= -20) {
                PPX = PX; PPY = PY; PPZ = PZ;
                PROLL = ROLL; PYAW = YAW; PPITCH = PITCH;
                X = 0.0;
                ATIRANDO = false;
            } else {
                X -= PROJETIL;
            }
        }
    }
    
//     printf("%f // %f // %f\n", ROLL,YAW,PITCH);
}

void Drone::calcula_velocidade() {
    if(PY == 0.0){
        if(FRENTE){
            HELICE -= 20;
            VZ += cos(YAW * 3.14159/180.0)*VELOCIDADE;
            if(VMOTOR_DIREITO < MAX_ANGULO)      VMOTOR_DIREITO += ANGULO;
            if(VMOTOR_ESQUERDO < MAX_ANGULO)     VMOTOR_ESQUERDO += ANGULO;
            FRENTE = true;
        }else if(TRAS){
            HELICE -= 20;
            VZ += - cos(YAW * 3.14159/180.0)*VELOCIDADE;
            if(VMOTOR_DIREITO > -MAX_ANGULO)     VMOTOR_DIREITO -= ANGULO; 
            if(VMOTOR_ESQUERDO > -MAX_ANGULO)    VMOTOR_ESQUERDO -= ANGULO;
            FRENTE = false;
        }else if(DIREITA) {
            HELICE -= 20;
            if(VMOTOR_TRASEIRO < MAX_ANGULO)     VMOTOR_TRASEIRO += ANGULO;
            if(VROLL < MAX_ANGULO)               VROLL += MOV_EQ;
            VX += -sin(ROLL * 3.14159/360.0);
        }else if(ESQUERDA) {
            HELICE -= 20;
            if(VMOTOR_TRASEIRO > -MAX_ANGULO)    VMOTOR_TRASEIRO -= ANGULO;
            if(VROLL > -MAX_ANGULO)              VROLL -= MOV_EQ;
            VX += -sin(ROLL * 3.14159/360.0);
        }
        RX = (pow(RESISTENCIA,abs(VX))-1.0)*F_RESISTENCIA;
        RZ = (pow(RESISTENCIA,abs(VZ))-1.0)*F_RESISTENCIA;
    }else{
        RX = (pow(RESISTENCIA,abs(VX))-1.0)*F_RESISTENCIA_AR;
        RZ = (pow(RESISTENCIA,abs(VZ))-1.0)*F_RESISTENCIA_AR;
    }
    
    if(VX>RX)           VX -= RX;
    else if(VX<-RX)     VX += RX;
    else if(abs(VZ)<RX){
        if(abs(VX)>0)   printf("Parou\n");
        VX = 0.0;       VZ = 0.0;
    }
    
    if(VZ>RZ)          VZ -= RZ;
    else if(VZ<-RZ)    VZ += RZ;
    else if(abs(VX)<RZ){
        if(abs(VZ)>0)  printf("Parou\n");
        VZ = 0.0;      VX = 0.0;
    }
    
    if(FRENTE){if(PITCH < MAX_ANGULO/3)   PITCH += 10*sqrt(pow(VX,2)+pow(VZ,2));}
    else{if(PITCH >= 0)                   PITCH -= 10*sqrt(pow(VX,2)+pow(VZ,2));}
    
    if(TRAS){if(PITCH > -MAX_ANGULO/3)    PITCH -= 10*sqrt(pow(VX,2)+pow(VZ,2));}
    else{if(PITCH <= 0)                   PITCH += 10*sqrt(pow(VX,2)+pow(VZ,2));}
    
    if(PY > 0.0)       HELICE -= 20;
    
//     printf("Vx: %f // Vz: %f // Vy: %f\n", VX, VZ, VY);
    
}

void Drone::atirando(){
    glPushMatrix();
    glTranslatef(PPX, PPY, PPZ);
    glRotatef(PYAW, 0.0, 1.0, 0.0);
    glRotatef(PROLL, 0.0, 0.0, 1.0);
    
    glPushMatrix();
    glRotatef(90,0.0,1.0,0.0);
    
    glMaterialfv(GL_FRONT,GL_AMBIENT, chrome_amb);
    glMaterialfv(GL_FRONT,GL_DIFFUSE, chrome_dif);
    glMaterialfv(GL_FRONT,GL_SPECULAR, chrome_spe);
    glMaterialf(GL_FRONT,GL_SHININESS, chrome_shi);
    
    glPushMatrix();
    glTranslatef(X,POY,-1.3);
    glScalef(POX,POX,POX);
    core.Draw();
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(X,POY,1.3);
    glScalef(POX,POX,POX);
    core.Draw();
    glPopMatrix();
    
    if(X <= -1.8){
        raio.Desenha();
        raio.atualiza_raio(X);
        raio.calcula_velocidade();
    }
    
    glPopMatrix();
    
    glPopMatrix();
}
