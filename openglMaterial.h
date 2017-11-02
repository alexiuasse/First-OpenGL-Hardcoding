#define POINTS_PER_VERTEX 3
#define TOTAL_FLOATS_IN_TRIANGLE 9
#define GRAVIDADE 0.01
#define VELOCIDADE 0.1
#define RESISTENCIA 1.4
#define F_RESISTENCIA 0.3
#define F_RESISTENCIA_AR 0.05
#define PI 3.14159265359
#define MOV_FT 0.2                     // maximo movimento frente tras
#define MOV_EQ 2.0                     // maximo movimento esquerda direita 
#define MOV_SD 0.1                     // maximo movimento subir descer
#define MAX_GIRO 50.0                  // giro a aumentar nas helices
#define MAX_ANGULO 20.0                // angulo maximo
#define MIN_ANGULO 0.0                 // angulo minimo
#define ANGULO 2.5                     // angulo que vai aumentar ou diminuir
#define D_ANGULO ANGULO/3              // angulo que vai voltar ao normal os motores
#define MAX_AREA 25.0                  // area maxima

GLfloat ouro_amb[4] = {0.24725, 0.1995, 0.0745, 1.0};
GLfloat ouro_dif[4] = {0.75164, 0.60648, 0.22648, 1.0};
GLfloat ouro_spe[4] = {0.628281, 0.555802, 0.366065, 1.0};
GLfloat ouro_shi = 0.4*128.0;

GLfloat chrome_amb[4] = {0.25, 0.25, 0.25, 1.0};
GLfloat chrome_dif[4] = {0.4, 0.4, 0.4, 1.0};
GLfloat chrome_spe[4] = {0.774597, 0.774597, 0.774597, 1.0};
GLfloat chrome_shi = 0.1*128.0;

GLfloat rubi_amb[4] = {0.1745, 0.01175, 0.01175, 1.0};
GLfloat rubi_dif[4] = {0.61424, 0.04136, 0.04136, 1.0};
GLfloat rubi_spe[4] = {0.727811, 0.626959, 0.626959, 1.0};
GLfloat rubi_shi = 0.6*128.0;

GLfloat black_rubber_amb[4] = {0.02, 0.02, 0.02, 1.0};
GLfloat black_rubber_dif[4] = {0.01, 0.01, 0.01, 1.0};
GLfloat black_rubber_spe[4] = {0.4, 0.4, 0.4, 1.0};
GLfloat black_rubber_shi = 0.078125*128.0;

GLfloat cyan_amb[4] = {0.0, 0.1, 0.06, 1.0};
GLfloat cyan_dif[4] = {0.0, 0.50980392, 0.50980392, 1.0};
GLfloat cyan_spe[4] = {0.50196078, 0.50196078, 0.50196078, 1.0};
GLfloat cyan_shi = 0.25*128.0;

GLfloat scyan_amb[4] = {0.0, 1000, 1000, 1.0};
GLfloat scyan_dif[4] = {0.0, 1000, 1000, 1.0};
GLfloat scyan_spe[4] = {0.0, 1000, 1000, 1.0};
GLfloat scyan_shi = 1000;

GLfloat srubi_amb[4] = {1000, 1000, 0.0, 1.0};
GLfloat srubi_dif[4] = {1000, 1000, 0.0, 1.0};
GLfloat srubi_spe[4] = {1000, 1000, 0.0, 1.0};
GLfloat srubi_shi = 1000;

GLfloat crubi_amb[4] = {0.1745, 0.01175, 0.01175, 1.0};
GLfloat crubi_dif[4] = {0.61424, 0.04136, 0.04136, 1.0};
GLfloat crubi_spe[4] = {0.727811, 0.626959, 0.626959, 1.0};
GLfloat crubi_shi = 0.6*128.0;

GLfloat copper_amb[4] = {0.19125, 0.0735, 0.0225, 1.0};
GLfloat copper_dif[4] = {0.7038, 0.27048, 0.0828, 1.0};
GLfloat copper_spe[4] = {0.256777, 0.137622, 0.086014, 1.0};
GLfloat copper_shi = 0.1*128.0;

GLfloat bronze_amb[4] = {0.2125, 0.1275, 0.054, 1.0};
GLfloat bronze_dif[4] = {0.714, 0.4284, 0.18144, 1.0};
GLfloat bronze_spe[4] = {0.393548, 0.271906, 0.166721, 1.0};
GLfloat bronze_shi = 0.2*128.0;

GLfloat yellow_amb[4] = {0.05, 0.05, 0.0, 1.0};
GLfloat yellow_dif[4] = {0.5, 0.5, 0.4, 1.0};
GLfloat yellow_spe[4] = {0.7, 0.7, 0.04, 1.0};
GLfloat yellow_shi = 0.078125*128.0;
