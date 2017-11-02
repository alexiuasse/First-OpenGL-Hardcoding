// #include "Model_OBJ.h"
#include <iostream>
#define PI 3.14159265359
#define VL 2.0
#define C 0.08

class ParticulaI{
public:
    float PX,PY,PZ;
    float VY = 0.0, VZ = 0.0, VX = 0.0;
    bool REVERSE;
    Model_OBJ particula;
    ParticulaI(float X, float Y, float Z);
    void Desenha();
};

ParticulaI::ParticulaI(float X, float Y, float Z){
    this->PX = X;
    this->PY = Y;
    this->PZ = Z;
//     printf("%f // %f // %f\n", PX,PY,PZ);
    particula.Load("obejetos/particula2.obj");
}

void ParticulaI::Desenha(){
    glPushMatrix();
//     printf("%f // %f // %f\n", PX,PY,PZ);
    glTranslatef(this->PX, this->PY, this->PZ);
    glScalef(0.4,0.4,0.9);
    particula.Draw();
    glPopMatrix();
}

class Insect{
public:
    float PX, PY, PZ;
    double VX = 0.0, VY = 0.0, VZ = 0.0;
    double RX = 0.0, RZ = 0.0, RY = 0.0;
    int P = 100;
    std::vector<ParticulaI*> particula;
    Insect();
    void Desenha();
    void atualiza_insect();
    void calcula_velocidade();
    void calcula_velocidade_insect();
};

Insect::Insect(){
    srand (time(NULL));
    for(int i = 0; i < P; i++){
        int OI = rand()%50 + (-25);
        int OI2 = rand()%7 + 1;
        int OI3 = rand()%50 + (-20);
        particula.push_back(new ParticulaI(OI,OI2,OI3));
    }
}

/*
 * NOSIÇÃO INICIAL DOS NROJETEIS E DIVIDR A QUANTIDADE EM 2
 * FLUIR DE UM LADO NARA OUTRO
 */
void Insect::Desenha(){
    for(int i = 0; i < P; i++){
        if(i%2 == 0) {
            glMaterialfv(GL_FRONT,GL_AMBIENT, srubi_amb);
            glMaterialfv(GL_FRONT,GL_DIFFUSE, srubi_dif);
            glMaterialfv(GL_FRONT,GL_SPECULAR, srubi_spe);
            glMaterialf(GL_FRONT,GL_SHININESS, srubi_shi);
        }else{
            glMaterialfv(GL_FRONT,GL_AMBIENT,scyan_amb);
            glMaterialfv(GL_FRONT,GL_DIFFUSE,scyan_dif);
            glMaterialfv(GL_FRONT,GL_SPECULAR,scyan_spe);
            glMaterialf(GL_FRONT,GL_SHININESS,scyan_shi);
        }
        particula.at(i)->Desenha();
    }
}

void Insect::atualiza_insect(){
    for(int i = 0; i < P; i++){
        if(particula.at(i)->PZ <= -26 or particula.at(i)->PX <= -26){
            particula.at(i)->REVERSE = true;
        }else if(particula.at(i)->PZ >= 26 or particula.at(i)->PX >= 26){
            particula.at(i)->REVERSE = false;
        }
        if(particula.at(i)->REVERSE){
            particula.at(i)->PZ += particula.at(i)->VZ;
            particula.at(i)->PY += particula.at(i)->VY;
            particula.at(i)->PX += particula.at(i)->VX;
        }else{
            particula.at(i)->PZ -= particula.at(i)->VZ;
            particula.at(i)->PY -= particula.at(i)->VY;
            particula.at(i)->PX -= particula.at(i)->VX;
        }
        if(particula.at(i)->PY < 0.0){
            particula.at(i)->PY = 0.0;
        }
//         printf("%f // %f\n", particula.at(i)->VY,particula.at(i)->PY);
    }
}

void Insect::calcula_velocidade_insect(){
    for(int i = 0; i < P; i++){
        particula.at(i)->VY = 0.01 * sin(1000 + i / PI );
        particula.at(i)->VZ = VL/(i+10);
        particula.at(i)->VX = VL/(i+10);
    }
}
