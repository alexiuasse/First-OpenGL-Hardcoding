// #include "Model_OBJ.h"
#include <iostream>
#define PI 3.14159265359
#define VL 2.0
#define C 0.08

class Particula{
public:
    float PX,PY,PZ;
    float VY = 0.0, VZ = 0.0;
    bool REVERSE;
    Model_OBJ particula;
    Particula(float X, float Y, float Z);
    void Desenha();
};

Particula::Particula(float X, float Y, float Z){
    this->PX = X;
    this->PY = Y;
    this->PZ = Z;
    particula.Load("obejetos/particula2.obj");
}

void Particula::Desenha(){
    glPushMatrix();
    glTranslatef(PX, PY, PZ);
    glScalef(0.5,0.5,0.9);
    particula.Draw();
    glPopMatrix();
}

class Raio{
public:
    float PX, PY, PZ;
    double VX = 0.0, VY = 0.0, VZ = 0.0;
    double RX = 0.0, RZ = 0.0, RY = 0.0;
    int P = 1000;
    float XI = 0.0, X = 0.0;
    std::vector<Particula*> particula;
    Raio();
    void Desenha();
    void atualiza_raio(float PX);
    void calcula_velocidade();
};

Raio::Raio(){
    for(int i = 0; i < P; i++){
        if(i%2 == 0){
            particula.push_back(new Particula(0.0,1.0,0.0));
            particula.at(i)->REVERSE = true;
        }else{
             particula.push_back(new Particula(0.0,1.0,0.0));
            particula.at(i)->REVERSE = false;
        }
    }
}

/*
 * NOSIÇÃO INICIAL DOS NROJETEIS E DIVIDR A QUANTIDADE EM 2
 * FLUIR DE UM LADO NARA OUTRO
 */
void Raio::Desenha(){
    for(int i = 0; i < P; i++){
        glMaterialfv(GL_FRONT,GL_AMBIENT,scyan_amb);
        glMaterialfv(GL_FRONT,GL_DIFFUSE,scyan_dif);
        glMaterialfv(GL_FRONT,GL_SPECULAR,scyan_spe);
        glMaterialf(GL_FRONT,GL_SHININESS,scyan_shi);
        particula.at(i)->Desenha();
    }
}

void Raio::atualiza_raio(float PX){
    if(PX == 0) X = 0.0;
    for(int i = 0; i < P; i++){
        particula.at(i)->PX = PX;
        if(particula.at(i)->PZ <= -1.0){
            particula.at(i)->REVERSE = true;
        }else if(particula.at(i)->PZ >= 1.0){
            particula.at(i)->REVERSE = false;
        }
        if(particula.at(i)->REVERSE){
            particula.at(i)->PZ += particula.at(i)->VZ;
        }else{
            particula.at(i)->PZ -= particula.at(i)->VZ;
        }
        particula.at(i)->PY += particula.at(i)->VY;
    }
}

void Raio::calcula_velocidade(){
    for(int i = 0; i < P; i++){
        X += 0.5;
        particula.at(i)->VY = 0.005* cos(X * PI / 1000 + i);
        particula.at(i)->VZ = VL/(i+5);
    }
}
