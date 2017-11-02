#include "Model_OBJ.h"
#include <time.h>
#include <iostream>
#define PI 3.14159265359
#define N 10
using namespace std;

class Vertebra {
public:
    float PX, PY, PZ;
    double YAW = 0.0, PITCH = 0.0, ROLL = 0.0;
    double VROLL = 0.0, VPITCH = 0.0, VYAW = 0.0;
    double VX = 0.0, VY = 0.0, VZ = 0.0;
    double RX = 0.0, RZ = 0.0, RY = 0.0;
    bool HIT = false, AR, HEAD = false;
    bool UP = true, DOWN = false;
    Model_OBJ core;
    Model_OBJ head;
    Vertebra(float X, float Y, float Z, bool H);
    void desenha();
};

Vertebra::Vertebra(float X, float Y, float Z, bool H){
    this->PX = X;
    this->PY = Y;
    this->PZ = Z;
    if(H){
        this->HEAD = H;
        head.Load("obejetos/head.obj");
    }else{
        core.Load("obejetos/particula.obj");
    }
}

void Vertebra::desenha(){
    if(!HIT){
        glPushMatrix();
        glTranslatef(PX, PY, PZ);
        if(!HEAD){
            glRotatef(YAW, 0.0, 1.0, 0.0);
            glRotatef(ROLL, 0.0, 0.0, 1.0);
            glRotatef(PITCH, 1.0, 0.0, 0.0);
        }
        if(HEAD){
            glMaterialfv(GL_FRONT,GL_AMBIENT, ouro_amb);
            glMaterialfv(GL_FRONT,GL_DIFFUSE, ouro_dif);
            glMaterialfv(GL_FRONT,GL_SPECULAR, ouro_spe);
            glMaterialf(GL_FRONT,GL_SHININESS, ouro_shi);
            head.Draw();
        }else{
            core.Draw();
        }
        glPopMatrix();
    }
}

class Minhoca {
public:
    float PX = 0, PY = 0.0, PZ = (rand()%40)-20;
    double VX = 0.0, VY = 0.0, VZ = 0.0;
    double RX = 0.0, RZ = 0.0, RY = 0.0;
    float DX,DY,DZ,D;
    int X = 0, cont = 0, ht = 0;
    bool MV = false;
    float VELO = 0.1;
    std::vector<Vertebra*> vertebra;
//     Ball ball;
    void Desenha();
    void Rdesenha(bool oi);
    void atualiza_minhoca();
    void calcula_velocidade();
    Minhoca();
    bool hit(float X, float Z, float Y, float P);
};

Minhoca::Minhoca(){
    for(int i = 0; i < N; i++){
        if(i == N-1){
            vertebra.push_back(new Vertebra(i-N-25,1.0,2.0,true));
        }else{
            vertebra.push_back(new Vertebra(i-N-25,1.0,2.0,false));
        }
    }
};

bool Minhoca::hit(float X, float Z, float Y, float P){
    for(int i = 0; i < N; i++){
        DX = vertebra.at(i)->PX + (Z+abs(P));
        DZ = vertebra.at(i)->PZ - X;
//         DY = vertebra.at(i)->PY - Y;
        D = sqrt((DX*DX) + (DZ*DZ) /*+ (DY*DY)*/);
        if(D <= 1){
            ht ++;
            vertebra.at(abs(i-ht+1))->HIT = true;
            if(ht >= N){
                if(VELO <= 0.5) VELO += 0.1;
                else VELO = 0.1;
                Rdesenha(true);
                ht = 0;
            }
            return true;
        }
        DX = DZ = D = 0;
    }
    return false;
}

void Minhoca::Desenha() {
    for(int i = 0; i < N; i++){
        if(i%2 == 0){
            glMaterialfv(GL_FRONT,GL_AMBIENT,cyan_amb);
            glMaterialfv(GL_FRONT,GL_DIFFUSE,cyan_dif);
            glMaterialfv(GL_FRONT,GL_SPECULAR,cyan_spe);
            glMaterialf(GL_FRONT,GL_SHININESS,cyan_shi);
            vertebra.at(i)->desenha();
        }else{
            glMaterialfv(GL_FRONT,GL_AMBIENT, rubi_amb);
            glMaterialfv(GL_FRONT,GL_DIFFUSE, rubi_dif);
            glMaterialfv(GL_FRONT,GL_SPECULAR, rubi_spe);
            glMaterialf(GL_FRONT,GL_SHININESS, rubi_shi);
            vertebra.at(i)->desenha();
        }
    }
}

void Minhoca::Rdesenha(bool oi){
    PZ = (rand()%40)-20;
    X = 0;
    for(int i = 0; i < N; i++){
        vertebra.at(i)->PX = i-N-25;
        vertebra.at(i)->PZ = PZ;
        vertebra.at(i)->VY = 0.0;
        vertebra.at(i)->VZ = 0.0;
        vertebra.at(i)->PY = 1.0;
        if(oi){vertebra.at(i)->HIT = false;}
        if(rand()%2){
            MV = true;
        }else{ 
            MV = false;
        }
    }
}

void Minhoca::atualiza_minhoca(){
    for(int i = 0; i < N; i++){
        if(vertebra.at(i)->PX >= MAX_AREA){
            if(cont++ >= N){
                Rdesenha(false);
                cont = 0;
            }
        }else{
            vertebra.at(i)->PX += vertebra.at(i)->VX;
            vertebra.at(i)->PY += vertebra.at(i)->VY/10;
            vertebra.at(i)->PZ += vertebra.at(i)->VZ/10;
            vertebra.at(i)->ROLL +=  vertebra.at(i)->VROLL;
            vertebra.at(i)->PITCH +=  vertebra.at(i)->VPITCH;
            vertebra.at(i)->YAW +=  vertebra.at(i)->VYAW;
        }
    }
}

void Minhoca::calcula_velocidade() {
    for(int i = 0; i < N; i++){
        X++;
        vertebra.at(i)->VX = VELO;
        if(MV)
            vertebra.at(i)->VZ = sin(X * PI / 100 + i);
        else
            vertebra.at(i)->VY = cos(X * PI / 100 + i);

        if(vertebra.at(i)->VROLL>10)     vertebra.at(i)->VROLL -= 0.1;
        else             vertebra.at(i)->VROLL += 0.1;

        if(vertebra.at(i)->VYAW>10)      vertebra.at(i)->VYAW -= 0.1;
        else             vertebra.at(i)->VYAW += 0.1;
    }
}
