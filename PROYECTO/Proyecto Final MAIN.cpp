/*PROYECTO FINAL
 
Alumnos:
Barragan Pilar Diana			318147981
Medrano Miranda Daniel Ulises	318045351
Uriarte Ortiz Enrique Yahir		318234757
*/

#define STB_IMAGE_IMPLEMENTATION

#include <stdio.h>
#include <string.h>
#include <cmath>
#include <vector>
#include <math.h>
#include <glew.h>
#include <glfw3.h>
#include <glm.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>
#include "Window.h"
#include "Mesh.h"
#include "Shader_light.h"
#include "Camera.h"
#include "Texture.h"
#include "Sphere.h"
#include "Model.h"
#include "Skybox.h"
#include "CommonValues.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "Material.h"

const float toRadians = 3.14159265f / 180.0f;

// Variables para rotacion de los Dados.
float movDado, movOffsetDado;
float RotacionX4, RotacionZ4, RotacionX8, RotacionZ8;
bool DadoRotando, DadoPiso;

// Variables para movimiento en el Tablero.
int Posicion;
float movX, movZ, giro, avance;
float movOffsetHeli, V_Rot_Helice;
float UbiCesq1, UbiCesq2, new_pos;
bool Cas1, Cas2, Cas3, Cas4, Continuar, PuedeSubir;
char casilla_Activacion[3];

bool PerPrincipal1, PerPrincipal2, PerPrincipal3;

// Variables para la Interacion de los modelos por movimiento.
float ultimaActivacion;	bool avanza2;
float rotA1 = 0.0f, rotA2 = 0.0f, rotA3 = 0.0f, rotA4 = 0.0f, rotA5 = 0.0f, rotA6 = 0.0f, rotA7 = 0.0f, rotA8 = 0.0f, rotA9 = 0.0f, rotS1 = 0.0f;
float rotB1 = 0.0f, rotB2 = 0.0f, rotB3 = 0.0f, rotB4 = 0.0f, rotB5 = 0.0f, rotB6 = 0.0f, rotB7 = 0.0f, rotB8 = 0.0f, rotB9 = 0.0f, rotS2 = 0.0f;
float rotC1 = 0.0f, rotC2 = 0.0f, rotC3 = 0.0f, rotC4 = 0.0f, rotC5 = 0.0f, rotC6 = 0.0f, rotC7 = 0.0f, rotC8 = 0.0f, rotC9 = 0.0f, rotS3 = 0.0f;
float rotD1 = 0.0f, rotD2 = 0.0f, rotD3 = 0.0f, rotD4 = 0.0f, rotD5 = 0.0f, rotD6 = 0.0f, rotD7 = 0.0f, rotD8 = 0.0f, rotD9 = 0.0f;

// --- Casillas de la CHICAS SUPERPODEROSAS ---
float  movYA1, movYA2, movYA3, movYA4, movYA5, movYA6, movYA7, movYA8, movYA9, movYS1, movYB1, movYB2, movYB3; 
static char ultimaCasillaGato[3] = "";			bool avanzaGato = true;			float ultimaActivacionGato = 0.0f;
static char ultimaCasillaOcti[3] = "";			bool avanzaOcti = true;			float ultimaActivacionOcti = 0.0f;
static char ultimaCasillaArbol[3] = "";			bool avanzaArbol = true;		float ultimaActivacionArbol = 0.0f;
static char ultimaCasillaBurbuja[3] = "";		bool avanzaBurbuja = true;		float ultimaActivacionBurbuja = 0.0f;
static char ultimaCasillaBellota[3] = "";		bool avanzaBellota = true;		float ultimaActivacionBellota = 0.0f;
static char ultimaCasillaMojoJojo[3] = "";		bool avanzaMojoJojo = true;		float ultimaActivacionMojoJojo = 0.0f;
static char ultimaCasillaPeludito[3] = "";		bool avanzaPeludito = true;		float ultimaActivacionPeludito = 0.0f;
static char ultimaCasillaPrincesa[3] = "";		bool avanzaPrincesa = true;		float ultimaActivacionPrincesa = 0.0f;
static char ultimaCasillaProfesor[3] = "";		bool avanzaProfesor = true;		float ultimaActivacionProfesor = 0.0f;
static char ultimaCasillaSedusa[3] = "";		bool avanzaSedusa = true;		float ultimaActivacionSedusa = 0.0f;
static char ultimaCasillaCasaCSP[3] = "";		bool avanzaCasaCSP = true;		float ultimaActivacionCasaCSP = 0.0f;
static char ultimaCasillaEdificioCSP[3] = "";	bool avanzaEdificioCSP = true;	float ultimaActivacionEdificioCSP = 0.0f;
static char ultimaCasillaAlcaldia[3] = "";		bool avanzaAlcaldia = true;		float ultimaActivacionAlcaldia = 0.0f;

// --- Casillas de BIG HERO 6 ---
float  movYB4, movYB5, movYB6, movYB7, movYB8, movYB9, movYS2, movYC1, movYC2, movYC3, movYC4, movYC5, movYC6;
static char ultimaCasillaHiroHamada_M[3] = "";				bool avanzaHiroHamada_M = true;				float ultimaActivacionHiroHamada_M = 0.0f;
static char ultimaCasillaPlanta1_M[3] = "";					bool avanzaPlanta1_M = true;				float ultimaActivacionPlanta1_M = 0.0f;
static char ultimaCasillaAutoChico_M[3] = "";				bool avanzaAutoChico_M = true;				float ultimaActivacionAutoChico_M = 0.0f;
static char ultimaCasillaGogoTomago_M[3] = "";				bool avanzaGogoTomago_M = true;				float ultimaActivacionGogoTomago_M = 0.0f;
static char ultimaCasillaMotocicleta_M[3] = "";				bool avanzaMotocicleta_M = true;			float ultimaActivacionMotocicleta_M = 0.0f;
static char ultimaCasillaGoldenGate_M[3] = "";				bool avanzaGoldenGate_M = true;				float ultimaActivacionGoldenGate_M = 0.0f;
static char ultimaCasillaPlanta2_M[3] = "";					bool avanzaPlanta2_M = true;				float ultimaActivacionPlanta2_M = 0.0f;
static char ultimaCasillaBaymaxSuperArmadura_M[3] = "";		bool avanzaBaymaxSuperArmadura_M = true;	float ultimaActivacionBaymaxSuperArmadura_M = 0.0f;
static char ultimaCasillaAutoGrande_M[3] = "";				bool avanzaAutoGrande_M = true;				float ultimaActivacionAutoGrande_M = 0.0f;
static char ultimaCasillaFred_M[3] = "";					bool avanzaFred_M = true;					float ultimaActivacionFred_M = 0.0f;
static char ultimaCasillaPlanta3_M[3] = "";					bool avanzaPlanta3_M = true;				float ultimaActivacionPlanta3_M = 0.0f;
static char ultimaCasillaCasaHiro_M[3] = "";				bool avanzaCasaHiro_M = true;				float ultimaActivacionCasaHiro_M = 0.0f;
static char ultimaCasillaMegabot_M[3] = "";							bool avanzaMegabot_M = true;				float ultimaActivacionMegabot_M = 0.0f;

// --- Casillas de PHINEAS Y FERB ---
float  movYC7, movYC8, movYC9, movYS3, movYD1, movYD2, movYD3, movYD4, movYD5, movYD6, movYD7, movYD8, movYD9; 
static char ultimaCasillaPhineas[3] = "";			bool avanzaPhineas = true;			float ultimaActivacionPhineas = 0.0f;
static char ultimaCasillaOrnitocyborg[3] = "";		bool avanzaOrnitocyborg = true;		float ultimaActivacionOrnitocyborg = 0.0f;
static char ultimaCasillaIsabella[3] = "";			bool avanzaIsabella = true;			float ultimaActivacionIsabella = 0.0f;
static char ultimaCasillaEDoofenshmirtz[3] = "";	bool avanzaEDoofenshmirtz = true;	float ultimaActivacionEDoofenshmirtz = 0.0f;
static char ultimaCasillaPeterPanda[3] = "";		bool avanzaPeterPanda = true;		float ultimaActivacionPeterPanda = 0.0f;
static char ultimaCasillaDoofenshmirtz[3] = "";		bool avanzaDoofenshmirtz = true;	float ultimaActivacionDoofenshmirtz = 0.0f;
static char ultimaCasillaTerryTortuga[3] = "";		bool avanzaTerryTortuga = true;		float ultimaActivacionTerryTortuga = 0.0f;
static char ultimaCasillaCandace[3] = "";			bool avanzaCandace = true;			float ultimaActivacionCandace = 0.0f;
static char ultimaCasillaDoofenshmirtz2D[3] = "";	bool avanzaDoofenshmirtz2D = true;	float ultimaActivacionDoofenshmirtz2D = 0.0f;
static char ultimaCasillaBuford[3] = "";			bool avanzaBuford = true;			float ultimaActivacionBuford = 0.0f;
static char ultimaCasillaPinkyChihuahua[3] = "";	bool avanzaPinkyChihuahua = true;	float ultimaActivacionPinkyChihuahua = 0.0f;
static char ultimaCasillaCarl[3] = "";				bool avanzaCarl = true;				float ultimaActivacionCarl = 0.0f;
static char ultimaCasillaFerb[3] = "";				bool avanzaFerb = true;				float ultimaActivacionFerb = 0.0f;

// --- Iluminacion ---
float T_Transcurrido;	bool FASE_01;
const float TIEMPO_CAMBIO = 1000.0f;

Window mainWindow;
std::vector<Mesh*> meshList;	std::vector<Shader> shaderList;
Camera camera;

// Texturas de Tablero
Texture pisoTexture, pisoTexture2;
Texture CentroTexture;
Texture Casilla1, Casilla4, Csl2, Csl3, Casilla1_D, Casilla4_D, Csl2_D, Csl3_D, Casilla1_N, Casilla4_N, Csl2_N, Csl3_N;
Texture A1, A2, A3, A4, A5, A6, A7, A8, A9, B1, B2, B3, B4, B5, B6, B7, B8, B9, C1, C2, C3, C4, C5, C6, C7, C8, C9, D1, D2, D3, D4, D5, D6, D7, D8, D9;
Texture A1_D, A2_D, A3_D, A4_D, A5_D, A6_D, A7_D, A8_D, A9_D, B1_D, B2_D, B3_D, B4_D, B5_D, B6_D, B7_D, B8_D, B9_D, C1_D, C2_D, C3_D, C4_D, C5_D, C6_D, C7_D, C8_D, C9_D, D1_D, D2_D, D3_D, D4_D, D5_D, D6_D, D7_D, D8_D, D9_D;
Texture A1_N, A2_N, A3_N, A4_N, A5_N, A6_N, A7_N, A8_N, A9_N, B1_N, B2_N, B3_N, B4_N, B5_N, B6_N, B7_N, B8_N, B9_N, C1_N, C2_N, C3_N, C4_N, C5_N, C6_N, C7_N, C8_N, C9_N, D1_N, D2_N, D3_N, D4_N, D5_N, D6_N, D7_N, D8_N, D9_N;

// Texturas de Dados
Texture Dado4_1;	Texture Dado4_2;	Texture Dado8;

//// Modelos de Personajes Principales
//Model Perry, Bombon, BaymaxBlanco_M;

// Modelos de Personajes Principales
Model Perry, Bombon, BaymaxBlanco_M, BrazoDerechoBaymax, ManoBaymax, DedoIzquierdoBaymax, DedoDerechoBaymax, DedoMedioBaymax, DedoGordoBaymax;


// Modelos alrededor del tablero
Model Gato, Octi, Arbol, Burbuja, Bellota, Mojo, Peludito, Princesa, Profesor, Sedusa, Casa, Edificio, Alcaldia, Phineas, Ornitocyborg, 
	  Isabella, PeterPanda, Doofenshmirtz, TerryTortuga, Candace, Doofenshmirtz2D, Buford, PinkyChihuahua, Carl, Ferb,
	  HiroHamada_M, Planta1_M, AutoChico_M, GogoTomago_M, Motocicleta_M, GoldenGate_M, Planta2_M, BaymaxSuperArmadura_M, AutoGrande_M,
	  Fred_M, Planta3_M, CasaHiro_M, Megabot_M, Lampara, Lampara2, esf;

// Modelos ciudad
Model Edificio1, Edificio2, Edificio3, Edificio4, Edificio5, Edificio6;
Model Casa2, Doof, Edificio7, Edificio8, Edificio9, Edificio10, Edificio11, Edificio12, Edificio13, Edificio14;
Model Edificio15, Edificio16, Edificio17, Edificio18, Torre, Puente;

// VARIABLES PARA LA DE BONBON
float movBx, movBy, movBz, rotB;
float movOffset, movOffsetp, movOffsetb;
float rotbombonOffset, rotbrazobomOffset;
float t, deltaT;
float ciclo, subiry, rotbrazo, bajarbrazo;

// DATOS PARA ANIMACIÓN DEL SEGUNDO BAYMAX
float giroBrazo = 0.0, giraMano = 0.0, giraDedos = 0.0;
float giroBrazoOffset = 0.3, giraManoOffset = 0.3, giraDedosOffset = 0.3;
bool mueveBrazo = true, mueveMano = false, mueveBrazo2 = false;

Model Bombon2, BrazoI, PiernaD;

Skybox skyboxDia;
Skybox skyboxNoche;
Material Material_brillante;	Material Material_opaco;
GLfloat deltaTime = 0.0f;	GLfloat lastTime = 0.0f;
DirectionalLight LightDAY, LightNIGHT;
PointLight pointLights[MAX_POINT_LIGHTS];
SpotLight spotLights[MAX_SPOT_LIGHTS];

static double limitFPS = 1.0 / 60.0;
static const char* vShader = "shaders/shader_light.vert";
static const char* fShader = "shaders/shader_light.frag";
 
void calcAverageNormals(unsigned int* indices, unsigned int indiceCount, GLfloat* vertices, unsigned int verticeCount,unsigned int vLength, unsigned int normalOffset){
	for (size_t i = 0; i < indiceCount; i += 3){
		unsigned int in0 = indices[i] * vLength;
		unsigned int in1 = indices[i + 1] * vLength;
		unsigned int in2 = indices[i + 2] * vLength;
		glm::vec3 v1(vertices[in1] - vertices[in0], vertices[in1 + 1] - vertices[in0 + 1], vertices[in1 + 2] - vertices[in0 + 2]);
		glm::vec3 v2(vertices[in2] - vertices[in0], vertices[in2 + 1] - vertices[in0 + 1], vertices[in2 + 2] - vertices[in0 + 2]);
		glm::vec3 normal = glm::cross(v1, v2);
		normal = glm::normalize(normal);

		in0 += normalOffset; in1 += normalOffset; in2 += normalOffset;
		vertices[in0] += normal.x; vertices[in0 + 1] += normal.y; vertices[in0 + 2] += normal.z;
		vertices[in1] += normal.x; vertices[in1 + 1] += normal.y; vertices[in1 + 2] += normal.z;
		vertices[in2] += normal.x; vertices[in2 + 1] += normal.y; vertices[in2 + 2] += normal.z;
	}
	for (size_t i = 0; i < verticeCount / vLength; i++){
		unsigned int nOffset = i * vLength + normalOffset;
		glm::vec3 vec(vertices[nOffset], vertices[nOffset + 1], vertices[nOffset + 2]);
		vec = glm::normalize(vec);
		vertices[nOffset] = vec.x; vertices[nOffset + 1] = vec.y; vertices[nOffset + 2] = vec.z;
	}
}

void CreateObjects(){
	unsigned int indices[] = {0,3,1,	1,3,2,	2,3,0,	0,1,2};
	GLfloat vertices[] = {
		//	x      y      z			u	  v			nx	  ny    nz
			-1.0f, -1.0f, -0.6f,	0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
			0.0f, -1.0f, 1.0f,		0.5f, 0.0f,		0.0f, 0.0f, 0.0f,
			1.0f, -1.0f, -0.6f,		1.0f, 0.0f,		0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f,		0.5f, 1.0f,		0.0f, 0.0f, 0.0f};

	unsigned int floorIndices[] = {0,2,1,	1,2,3};
	GLfloat floorVertices[] = {
		-10.0f, 0.0f, -10.0f,	0.0f, 0.0f,		0.0f, -1.0f, 0.0f,
		10.0f, 0.0f, -10.0f,	10.0f, 0.0f,	0.0f, -1.0f, 0.0f,
		-10.0f, 0.0f, 10.0f,	0.0f, 10.0f,	0.0f, -1.0f, 0.0f,
		10.0f, 0.0f, 10.0f,		10.0f, 10.0f,	0.0f, -1.0f, 0.0f};

	unsigned int vegetacionIndices[] = {0,1,2,	0,2,3,	4,5,6,	4,6,7};
	GLfloat vegetacionVertices[] = {
		-0.5f, -0.5f, 0.0f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.5f, -0.5f, 0.0f,		1.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.5f, 0.5f, 0.0f,		1.0f, 1.0f,		0.0f, 0.0f, 0.0f,
		-0.5f, 0.5f, 0.0f,		0.0f, 1.0f,		0.0f, 0.0f, 0.0f,
		0.0f, -0.5f, -0.5f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.0f, -0.5f, 0.5f,		1.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.0f, 0.5f, 0.5f,		1.0f, 1.0f,		0.0f, 0.0f, 0.0f,
		0.0f, 0.5f, -0.5f,		0.0f, 1.0f,		0.0f, 0.0f, 0.0f,};
	
	Mesh *obj1 = new Mesh();
	obj1->CreateMesh(vertices, indices, 32, 12);
	meshList.push_back(obj1);

	Mesh *obj2 = new Mesh();
	obj2->CreateMesh(vertices, indices, 32, 12);
	meshList.push_back(obj2);

	Mesh *obj3 = new Mesh();
	obj3->CreateMesh(floorVertices, floorIndices, 32, 6);
	meshList.push_back(obj3);

	Mesh* obj4 = new Mesh();
	obj4->CreateMesh(vegetacionVertices, vegetacionIndices, 64, 12);
	meshList.push_back(obj4);

	calcAverageNormals(indices, 12, vertices, 32, 8, 5);
	calcAverageNormals(vegetacionIndices, 12, vegetacionVertices, 64, 8, 5);}

void CreateShaders(){
	Shader *shader1 = new Shader();
	shader1->CreateFromFiles(vShader, fShader);
	shaderList.push_back(*shader1);}

void Casillas_Esquina() {
	unsigned int Casillas1_indices[] = {
		0,1,2, 0,2,3,	//Up
		4,5,6, 4,6,7,	//Down
		8,9,11, 8,10,11,	//Lateral_01
		12,13,15, 12,14,15,	//Lateral_02
		16,17,18, 17,18,19,	//Lateral_03
		20,21,22, 21,22,23,	//Lateral_04
	};
	GLfloat Casillas1_vertices[] = {
		//Up
		1.0f, 0.2f, 1.0f, 0.00f, 1.0f, 0.0f,-1.0f,0.0f,	//A - 0
		1.0f, 0.2f,-1.0f, 0.00f, 0.0f, 0.0f,-1.0f,0.0f,	//B - 1
	   -1.0f, 0.2f,-1.0f, 0.79f, 0.0f, 0.0f,-1.0f,0.0f,	//C - 2
	   -1.0f, 0.2f, 1.0f, 0.79f, 1.0f, 0.0f,-1.0f,0.0f,	//D - 3

	   //Down
		1.0f, 0.0f, 1.0f, 0.79f,1.0f, 0.0f,1.0f,0.0f,	//E - 4
		1.0f, 0.0f,-1.0f, 0.79f,0.0f, 0.0f,1.0f,0.0f,	//F - 5
	   -1.0f, 0.0f,-1.0f, 0.99f,0.0f, 0.0f,1.0f,0.0f,	//G - 6
	   -1.0f, 0.0f, 1.0f, 0.99f,1.0f, 0.0f,1.0f,0.0f,	//H - 7

	   //Lateral_01
		1.0f, 0.2f, 1.0f, 0.795f,1.0f, 0.0f,-1.0f,0.0f,	//A - 8
		1.0f, 0.2f,-1.0f, 0.985f,1.0f, 0.0f,-1.0f,0.0f,	//B - 9
		1.0f, 0.0f, 1.0f, 0.795f,0.0f, 0.0f,-1.0f,0.0f,	//E - 10
		1.0f, 0.0f,-1.0f, 0.985f,0.0f, 0.0f,-1.0f,0.0f,	//F - 11

	   //Lateral_02
		1.0f, 0.2f,-1.0f, 0.795f,1.0f, 0.0f,-1.0f,0.0f,	//B - 12
	   -1.0f, 0.2f,-1.0f, 0.985f,1.0f, 0.0f,-1.0f,0.0f,	//C - 13
		1.0f, 0.0f,-1.0f, 0.795f,0.0f, 0.0f,-1.0f,0.0f,	//F - 14
	   -1.0f, 0.0f,-1.0f, 0.985f,0.0f, 0.0f,-1.0f,0.0f,	//G - 15

	   //Lateral_03
	    1.0f, 0.2f, 1.0f, 0.795f,1.0f, 0.0f,-1.0f,0.0f,	//A - 16
	   -1.0f, 0.2f, 1.0f, 0.985f,1.0f, 0.0f,-1.0f,0.0f,	//D - 17
		1.0f, 0.0f, 1.0f, 0.795f,0.0f, 0.0f,-1.0f,0.0f,	//E - 18
	   -1.0f, 0.0f, 1.0f, 0.985f,0.0f, 0.0f,-1.0f,0.0f,	//H - 19

	   //Lateral_04
	   -1.0f, 0.2f,-1.0f, 0.795f,1.0f, 0.0f,-1.0f,0.0f,	//C - 20
	   -1.0f, 0.2f, 1.0f, 0.985f,1.0f, 0.0f,-1.0f,0.0f,	//D - 21
	   -1.0f, 0.0f,-1.0f, 0.795f,0.0f, 0.0f,-1.0f,0.0f,	//G - 22
	   -1.0f, 0.0f, 1.0f, 0.985f,0.0f, 0.0f,-1.0f,0.0f,	//H - 23

	};
	Mesh* Casillas1 = new Mesh();
	Casillas1->CreateMesh(Casillas1_vertices, Casillas1_indices, 192, 36);
	meshList.push_back(Casillas1);
}

void Casillas_Inter() {
	unsigned int Casillas2_indices[] = {
		0,1,2, 0,2,3,	//Up
		4,5,6, 4,6,7,	//Down
		8,9,11, 8,10,11,	//Lateral_01
		12,13,15, 12,14,15,	//Lateral_02
		16,17,18, 17,18,19,	//Lateral_03
		20,21,22, 21,22,23,	//Lateral_04
		8,9,11, 8,10,11,	//Lateral_01
		12,13,15, 12,14,15,	//Lateral_02
		16,17,18, 17,18,19,	//Lateral_03
		20,21,22, 21,22,23,	//Lateral_04
	};
	GLfloat Casillas2_vertices[] = {
		//Up
		1.0f, 0.2f, 0.5f, 0.00f,0.0f, 0.0f,-1.0f,0.0f,	//A - 0
		1.0f, 0.2f,-0.5f, 0.72f,0.0f, 0.0f,-1.0f,0.0f,	//B - 1
	   -1.0f, 0.2f,-0.5f, 0.72f,1.0f, 0.0f,-1.0f,0.0f,	//C - 2
	   -1.0f, 0.2f, 0.5f, 0.00f,1.0f, 0.0f,-1.0f,0.0f,	//D - 3

	   //Down
		1.0f, 0.0f, 0.5f, 0.75f,1.0f, 0.0f,1.0f,0.0f,	//E - 4
		1.0f, 0.0f,-0.5f, 0.75f,0.0f, 0.0f,1.0f,0.0f,	//F - 5
	   -1.0f, 0.0f,-0.5f, 0.99f,0.0f, 0.0f,1.0f,0.0f,	//G - 6
	   -1.0f, 0.0f, 0.5f, 0.99f,1.0f, 0.0f,1.0f,0.0f,	//H - 7

	   //Lateral_01
		1.0f, 0.2f, 0.5f, 0.75f,1.0f,  0.0f,-1.0f,0.0f,	//A - 8
		1.0f, 0.2f,-0.5f, 0.985f,1.0f, 0.0f,-1.0f,0.0f,	//B - 9
		1.0f, 0.0f, 0.5f, 0.75f,0.0f,  0.0f,-1.0f,0.0f,	//E - 10
		1.0f, 0.0f,-0.5f, 0.985f,0.0f, 0.0f,-1.0f,0.0f,	//F - 11

		//Lateral_02
		 1.0f, 0.2f,-0.5f, 0.75f,1.0f,  0.0f,-1.0f,0.0f,	//B - 12
		-1.0f, 0.2f,-0.5f, 0.985f,1.0f, 0.0f,-1.0f,0.0f,	//C - 13
		 1.0f, 0.0f,-0.5f, 0.75f,0.0f,  0.0f,-1.0f,0.0f,	//F - 14
		-1.0f, 0.0f,-0.5f, 0.985f,0.0f, 0.0f,-1.0f,0.0f,	//G - 15

		//Lateral_03
		 1.0f, 0.2f, 0.5f, 0.75f,1.0f,  0.0f,-1.0f,0.0f,	//A - 16
		-1.0f, 0.2f, 0.5f, 0.985f,1.0f, 0.0f,-1.0f,0.0f,	//D - 17
		 1.0f, 0.0f, 0.5f, 0.75f,0.0f,  0.0f,-1.0f,0.0f,	//E - 18
		-1.0f, 0.0f, 0.5f, 0.985f,0.0f, 0.0f,-1.0f,0.0f,	//H - 19

		//Lateral_04
		-1.0f, 0.2f,-0.5f, 0.75f,1.0f,  0.0f,-1.0f,0.0f,	//C - 20
		-1.0f, 0.2f, 0.5f, 0.985f,1.0f, 0.0f,-1.0f,0.0f,	//D - 21
		-1.0f, 0.0f,-0.5f, 0.75f,0.0f,  0.0f,-1.0f,0.0f,	//G - 22
		-1.0f, 0.0f, 0.5f, 0.985f,0.0f, 0.0f,-1.0f,0.0f,	//H - 23
	};
	Mesh* Casillas2 = new Mesh();
	Casillas2->CreateMesh(Casillas2_vertices, Casillas2_indices, 192, 36);
	meshList.push_back(Casillas2);
}

void Dado_4() {
	unsigned int dado4_indices[] = { 0,1,2, 3,4,5, 6,7,8, 9,10,11 };
	GLfloat dado4_vertices[] = {
		//Cara 1
		 1.00f, 0.00f, 0.58f,	0.00f,0.00f,	0.00f, 1.00f, 0.00f,//0
		-1.00f, 0.00f, 0.58f,	1.00f,0.00f,	0.00f, 1.00f, 0.00f,//1
		 0.00f, 0.00f,-1.15f,	0.50f,0.50f,	0.00f, 1.00f, 0.00f,//2
		//Cara 2
		 1.00f, 0.00f, 0.58f,	1.00f,1.00f,	0.00f,-1.00f,-1.00f,//3
		-1.00f, 0.00f, 0.58f,	1.00f,0.00f,	0.00f,-1.00f,-1.00f,//4
		 0.00f, 1.63f, 0.00f,	0.50f,0.50f,	0.00f,-1.00f,-1.00f,//5
		//Cara 3
		-1.00f, 0.00f, 0.58f,	0.00f,1.00f,	1.00f,-1.00f, 1.00f,//6
		 0.00f, 0.00f,-1.15f,	1.00f,1.00f,	1.00f,-1.00f, 1.00f,//7
		 0.00f, 1.63f, 0.00f,	0.50f,0.50f,	1.00f,-1.00f, 1.00f,//8
		//Cara 4
		 1.00f, 0.00f, 0.58f,	0.00f,1.00f,   -1.00f,-1.00f, 1.00f,//9
		 0.00f, 0.00f,-1.15f,	0.00f,0.00f,   -1.00f,-1.00f, 1.00f,//10
		 0.00f, 1.63f, 0.00f,	0.50f,0.50f,   -1.00f,-1.00f, 1.00f,//11
	};
	Mesh* dado4 = new Mesh();
	dado4->CreateMesh(dado4_vertices, dado4_indices, 96, 12);
	meshList.push_back(dado4);
}

void Dado_8() {
	unsigned int dado8_indices[] = { 0,1,2, 3,4,5, 6,7,8, 9,10,11, 12,13,14, 15,16,17, 18,19,20, 21,22,23 };
	GLfloat dado8_vertices[] = {
		//Cara 1
		 1.00f, 0.00f, 1.00f,	1.00f,0.50f,	0.00f,-1.00f, -1.00f,//0
		-1.00f, 0.00f, 1.00f,	0.00f,0.50f,	0.00f,-1.00f, -1.00f,//1
		 0.00f, 1.51f, 0.00f,	0.50f,0.75f,	0.00f,-1.00f, -1.00f,//2
		//Cara 2
		-1.00f, 0.00f, 1.00f,	0.00f,0.50f,	1.00f,-1.00f, 0.00f,//3
		-1.00f, 0.00f,-1.00f,	0.00f,1.00f,	1.00f,-1.00f, 0.00f,//4
		 0.00f, 1.51f, 0.00f,	0.50f,0.75f,	1.00f,-1.00f, 0.00f,//5
		//Cara 3
		-1.00f, 0.00f,-1.00f,	0.00f,1.00f,	0.00f,-1.00f, 1.00f,//6
		 1.00f, 0.00f,-1.00f,	1.00f,1.00f,	0.00f,-1.00f, 1.00f,//7
		 0.00f, 1.51f, 0.00f,	0.50f,0.75f,	0.00f,-1.00f, 1.00f,//8
		//Cara 4
		 1.00f, 0.00f, 1.00f,	1.00f,0.50f,   -1.00f,-1.00f, 0.00f,//9
		 1.00f, 0.00f,-1.00f,	1.00f,1.00f,   -1.00f,-1.00f, 0.00f,//10
		 0.00f, 1.51f, 0.00f,	0.50f,0.75f,   -1.00f,-1.00f, 0.00f,//11
	    //Cara 5
		 1.00f, 0.00f, 1.00f,	1.00f,0.50f,	0.00f, 1.00f,-1.00f,//12
		-1.00f, 0.00f, 1.00f,	0.00f,0.50f,	0.00f, 1.00f,-1.00f,//13
		 0.00f,-1.51f, 0.00f,	0.50f,0.25f,	0.00f, 1.00f,-1.00f,//14
		//Cara 6
		-1.00f, 0.00f, 1.00f,	0.00f,0.50f,	1.00f, 1.00f, 0.00f,//15
		-1.00f, 0.00f,-1.00f,	0.00f,0.00f,	1.00f, 1.00f, 0.00f,//16
		 0.00f,-1.51f, 0.00f,	0.50f,0.25f,	1.00f, 1.00f, 0.00f,//17
		//Cara 7
		-1.00f, 0.00f,-1.00f,	1.00f,0.00f,	0.00f, 1.00f, 1.00f,//18
		 1.00f, 0.00f,-1.00f,	0.00f,0.00f,	0.00f, 1.00f, 1.00f,//19
		 0.00f,-1.51f, 0.00f,	0.50f,0.25f,	0.00f, 1.00f, 1.00f,//20
		//Cara 8
		 1.00f, 0.00f, 1.00f,	1.00f,0.50f,   -1.00f, 1.00f, 0.00f,//21
		 1.00f, 0.00f,-1.00f,	1.00f,0.00f,   -1.00f, 1.00f, 0.00f,//22
		 0.00f,-1.51f, 0.00f,	0.50f,0.25f,   -1.00f, 1.00f, 0.00f,//23
	};
	Mesh* dado8 = new Mesh();
	dado8->CreateMesh(dado8_vertices, dado8_indices, 192, 24);
	meshList.push_back(dado8);
}

void Centro() {
	unsigned int Centro_indices[] = {
		0,1,2, 0,2,3,	//Up
		4,5,6, 4,6,7,	//Down
		8,9,11, 8,10,11,	//Lateral_01
		12,13,15, 12,14,15,	//Lateral_02
		16,17,18, 17,18,19,	//Lateral_03
		20,21,22, 21,22,23,	//Lateral_04
	};
	GLfloat Centro_vertices[] = {
		//Up
		1.0f, 0.2f, 1.0f, 0.00f, 1.0f, 0.0f,-1.0f,0.0f,	//A - 0
		1.0f, 0.2f,-1.0f, 0.00f, 0.0f, 0.0f,-1.0f,0.0f,	//B - 1
	   -1.0f, 0.2f,-1.0f, 1.00f, 0.0f, 0.0f,-1.0f,0.0f,	//C - 2
	   -1.0f, 0.2f, 1.0f, 1.00f,1.0f,  0.0f,-1.0f,0.0f,	//D - 3

	   //Down
		1.0f, 0.0f, 1.0f, 0.00f,1.0f, 0.0f,0.0f,0.0f,	//E - 4
		1.0f, 0.0f,-1.0f, 0.00f,0.0f, 0.0f,0.0f,0.0f,	//F - 5
	   -1.0f, 0.0f,-1.0f, 1.00f,0.0f, 0.0f,0.0f,0.0f,	//G - 6
	   -1.0f, 0.0f, 1.0f, 1.00f,1.0f, 0.0f,0.0f,0.0f,	//H - 7

	   //Lateral_01
		1.0f, 0.2f, 1.0f, 0.795f,1.0f, 0.0f,0.0f,0.0f,	//A - 8
		1.0f, 0.2f,-1.0f, 0.985f,1.0f, 0.0f,0.0f,0.0f,	//B - 9
		1.0f, 0.0f, 1.0f, 0.795f,0.0f, 0.0f,0.0f,0.0f,	//E - 10
		1.0f, 0.0f,-1.0f, 0.985f,0.0f, 0.0f,0.0f,0.0f,	//F - 11

		//Lateral_02
		 1.0f, 0.2f,-1.0f, 0.795f,1.0f, 0.0f,0.0f,0.0f,	//B - 12
		-1.0f, 0.2f,-1.0f, 0.985f,1.0f, 0.0f,0.0f,0.0f,	//C - 13
		 1.0f, 0.0f,-1.0f, 0.795f,0.0f, 0.0f,0.0f,0.0f,	//F - 14
		-1.0f, 0.0f,-1.0f, 0.985f,0.0f, 0.0f,0.0f,0.0f,	//G - 15

		//Lateral_03
		 1.0f, 0.2f, 1.0f, 0.795f,1.0f, 0.0f,0.0f,0.0f,	//A - 16
		-1.0f, 0.2f, 1.0f, 0.985f,1.0f, 0.0f,0.0f,0.0f,	//D - 17
		 1.0f, 0.0f, 1.0f, 0.795f,0.0f, 0.0f,0.0f,0.0f,	//E - 18
		-1.0f, 0.0f, 1.0f, 0.985f,0.0f, 0.0f,0.0f,0.0f,	//H - 19

		//Lateral_04
		-1.0f, 0.2f,-1.0f, 0.795f,1.0f, 0.0f,0.0f,0.0f,	//C - 20
		-1.0f, 0.2f, 1.0f, 0.985f,1.0f, 0.0f,0.0f,0.0f,	//D - 21
		-1.0f, 0.0f,-1.0f, 0.795f,0.0f, 0.0f,0.0f,0.0f,	//G - 22
		-1.0f, 0.0f, 1.0f, 0.985f,0.0f, 0.0f,0.0f,0.0f,	//H - 23
	};
	Mesh* Centro = new Mesh();
	Centro->CreateMesh(Centro_vertices, Centro_indices, 192, 36);
	meshList.push_back(Centro);
}

int main() {
	mainWindow = Window(1366, 768); // 1280, 1024 or 1024, 768
	mainWindow.Initialise();

	CreateObjects();	Casillas_Esquina();		Casillas_Inter();
	Dado_4();			Dado_8();				Centro();
	CreateShaders();

	camera = Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -60.0f, 0.0f, 0.3f, 0.5f);

	//Texturas para el piso
	pisoTexture = Texture("Textures/piso.tga");					pisoTexture.LoadTextureA();
	pisoTexture2 = Texture("Textures/CentroTableroSolo.tga");	pisoTexture2.LoadTextureA();
	CentroTexture = Texture("Textures/CentroTablero.tga");		CentroTexture.LoadTextureA();

	//Texturas de los Dados
	Dado4_1 = Texture("Textures/Dado4_1.tga");		Dado4_1.LoadTextureA();
	Dado4_2 = Texture("Textures/Dado4_2.tga");		Dado4_2.LoadTextureA();
	Dado8 = Texture("Textures/Dado8.tga");			Dado8.LoadTextureA();

	//Texturas para las esquinas
	
	//DIA
	Casilla1 = Texture("Textures/Casilla_1.tga");		Casilla1.LoadTextureA();
	Csl2 = Texture("Textures/Casilla_2.tga");			Csl2.LoadTextureA();
	Csl3 = Texture("Textures/Casilla_3.tga");			Csl3.LoadTextureA();
	Casilla4 = Texture("Textures/Casilla_4.tga");		Casilla4.LoadTextureA();
	//ILUMINADOS
	Casilla1_D = Texture("Textures/Casilla_1_D.tga");	Casilla1_D.LoadTextureA();
	Csl2_D = Texture("Textures/Casilla_2_D.tga");		Csl2_D.LoadTextureA();
	Csl3_D = Texture("Textures/Casilla_3_D.tga");		Csl3_D.LoadTextureA();
	Casilla4_D = Texture("Textures/Casilla_4_D.tga");	Casilla4_D.LoadTextureA();
	//NOCHE
	Casilla1_N = Texture("Textures/Casilla_1_N.tga");		Casilla1_N.LoadTextureA();
	Csl2_N = Texture("Textures/Casilla_2_N.tga");			Csl2_N.LoadTextureA();
	Csl3_N = Texture("Textures/Casilla_3_N.tga");			Csl3_N.LoadTextureA();
	Casilla4_N = Texture("Textures/Casilla_4_N.tga");		Casilla4_N.LoadTextureA();

	//Texturas para las 40 Casillas
	//DIA
	A1 = Texture("Textures/A1.tga");	A1.LoadTextureA();		A2 = Texture("Textures/A2.tga");	A2.LoadTextureA();
	A3 = Texture("Textures/A3.tga");	A3.LoadTextureA();		A4 = Texture("Textures/A4.tga");	A4.LoadTextureA();
	A5 = Texture("Textures/A5.tga");	A5.LoadTextureA();		A6 = Texture("Textures/A6.tga");	A6.LoadTextureA();
	A7 = Texture("Textures/A7.tga");	A7.LoadTextureA();		A8 = Texture("Textures/A8.tga");	A8.LoadTextureA();
	A9 = Texture("Textures/A9.tga");	A9.LoadTextureA();		B1 = Texture("Textures/B1.tga");	B1.LoadTextureA();
	B2 = Texture("Textures/B2.tga");	B2.LoadTextureA();		B3 = Texture("Textures/B3.tga");	B3.LoadTextureA();
	B4 = Texture("Textures/B4.tga");	B4.LoadTextureA();		B5 = Texture("Textures/B5.tga");	B5.LoadTextureA();
	B6 = Texture("Textures/B6.tga");	B6.LoadTextureA();		B7 = Texture("Textures/B7.tga");	B7.LoadTextureA();
	B8 = Texture("Textures/B8.tga");	B8.LoadTextureA();		B9 = Texture("Textures/B9.tga");	B9.LoadTextureA();
	C1 = Texture("Textures/C1.tga");	C1.LoadTextureA();		C2 = Texture("Textures/C2.tga");	C2.LoadTextureA();
	C3 = Texture("Textures/C3.tga");	C3.LoadTextureA();		C4 = Texture("Textures/C4.tga");	C4.LoadTextureA();
	C5 = Texture("Textures/C5.tga");	C5.LoadTextureA();		C6 = Texture("Textures/C6.tga");	C6.LoadTextureA();
	C7 = Texture("Textures/C7.tga");	C7.LoadTextureA();		C8 = Texture("Textures/C8.tga");	C8.LoadTextureA();
	C9 = Texture("Textures/C9.tga");	C9.LoadTextureA();		D1 = Texture("Textures/D1.tga");	D1.LoadTextureA();
	D2 = Texture("Textures/D2.tga");	D2.LoadTextureA();		D3 = Texture("Textures/D3.tga");	D3.LoadTextureA();
	D4 = Texture("Textures/D4.tga");	D4.LoadTextureA();		D5 = Texture("Textures/D5.tga");	D5.LoadTextureA();
	D6 = Texture("Textures/D6.tga");	D6.LoadTextureA();		D7 = Texture("Textures/D7.tga");	D7.LoadTextureA();
	D8 = Texture("Textures/D8.tga");	D8.LoadTextureA();		D9 = Texture("Textures/D9.tga");	D9.LoadTextureA();

	//ILUMINADOS
	A1_D = Texture("Textures/A1_D.tga");	A1_D.LoadTextureA();		A2_D = Texture("Textures/A2_D.tga");	A2_D.LoadTextureA();
	A3_D = Texture("Textures/A3_D.tga");	A3_D.LoadTextureA();		A4_D = Texture("Textures/A4_D.tga");	A4_D.LoadTextureA();
	A5_D = Texture("Textures/A5_D.tga");	A5_D.LoadTextureA();		A6_D = Texture("Textures/A6_D.tga");	A6_D.LoadTextureA();
	A7_D = Texture("Textures/A7_D.tga");	A7_D.LoadTextureA();		A8_D = Texture("Textures/A8_D.tga");	A8_D.LoadTextureA();
	A9_D = Texture("Textures/A9_D.tga");	A9_D.LoadTextureA();		B1_D = Texture("Textures/B1_D.tga");	B1_D.LoadTextureA();
	B2_D = Texture("Textures/B2_D.tga");	B2_D.LoadTextureA();		B3_D = Texture("Textures/B3_D.tga");	B3_D.LoadTextureA();
	B4_D = Texture("Textures/B4_D.tga");	B4_D.LoadTextureA();		B5_D = Texture("Textures/B5_D.tga");	B5_D.LoadTextureA();
	B6_D = Texture("Textures/B6_D.tga");	B6_D.LoadTextureA();		B7_D = Texture("Textures/B7_D.tga");	B7_D.LoadTextureA();
	B8_D = Texture("Textures/B8_D.tga");	B8_D.LoadTextureA();		B9_D = Texture("Textures/B9_D.tga");	B9_D.LoadTextureA();
	C1_D = Texture("Textures/C1_D.tga");	C1_D.LoadTextureA();		C2_D = Texture("Textures/C2_D.tga");	C2_D.LoadTextureA();
	C3_D = Texture("Textures/C3_D.tga");	C3_D.LoadTextureA();		C4_D = Texture("Textures/C4_D.tga");	C4_D.LoadTextureA();
	C5_D = Texture("Textures/C5_D.tga");	C5_D.LoadTextureA();		C6_D = Texture("Textures/C6_D.tga");	C6_D.LoadTextureA();
	C7_D = Texture("Textures/C7_D.tga");	C7_D.LoadTextureA();		C8_D = Texture("Textures/C8_D.tga");	C8_D.LoadTextureA();
	C9_D = Texture("Textures/C9_D.tga");	C9_D.LoadTextureA();		D1_D = Texture("Textures/D1_D.tga");	D1_D.LoadTextureA();
	D2_D = Texture("Textures/D2_D.tga");	D2_D.LoadTextureA();		D3_D = Texture("Textures/D3_D.tga");	D3_D.LoadTextureA();
	D4_D = Texture("Textures/D4_D.tga");	D4_D.LoadTextureA();		D5_D = Texture("Textures/D5_D.tga");	D5_D.LoadTextureA();
	D6_D = Texture("Textures/D6_D.tga");	D6_D.LoadTextureA();		D7_D = Texture("Textures/D7_D.tga");	D7_D.LoadTextureA();
	D8_D = Texture("Textures/D8_D.tga");	D8_D.LoadTextureA();		D9_D = Texture("Textures/D9_D.tga");	D9_D.LoadTextureA();

	//NOCHE
	A1_N = Texture("Textures/A1_N.tga");	A1_N.LoadTextureA();		A2_N = Texture("Textures/A2_N.tga");	A2_N.LoadTextureA();
	A3_N = Texture("Textures/A3_N.tga");	A3_N.LoadTextureA();		A4_N = Texture("Textures/A4_N.tga");	A4_N.LoadTextureA();
	A5_N = Texture("Textures/A5_N.tga");	A5_N.LoadTextureA();		A6_N = Texture("Textures/A6_N.tga");	A6_N.LoadTextureA();
	A7_N = Texture("Textures/A7_N.tga");	A7_N.LoadTextureA();		A8_N = Texture("Textures/A8_N.tga");	A8_N.LoadTextureA();
	A9_N = Texture("Textures/A9_N.tga");	A9_N.LoadTextureA();		B1_N = Texture("Textures/B1_N.tga");	B1_N.LoadTextureA();
	B2_N = Texture("Textures/B2_N.tga");	B2_N.LoadTextureA();		B3_N = Texture("Textures/B3_N.tga");	B3_N.LoadTextureA();
	B4_N = Texture("Textures/B4_N.tga");	B4_N.LoadTextureA();		B5_N = Texture("Textures/B5_N.tga");	B5_N.LoadTextureA();
	B6_N = Texture("Textures/B6_N.tga");	B6_N.LoadTextureA();		B7_N = Texture("Textures/B7_N.tga");	B7_N.LoadTextureA();
	B8_N = Texture("Textures/B8_N.tga");	B8_N.LoadTextureA();		B9_N = Texture("Textures/B9_N.tga");	B9_N.LoadTextureA();
	C1_N = Texture("Textures/C1_N.tga");	C1_N.LoadTextureA();		C2_N = Texture("Textures/C2_N.tga");	C2_N.LoadTextureA();
	C3_N = Texture("Textures/C3_N.tga");	C3_N.LoadTextureA();		C4_N = Texture("Textures/C4_N.tga");	C4_N.LoadTextureA();
	C5_N = Texture("Textures/C5_N.tga");	C5_N.LoadTextureA();		C6_N = Texture("Textures/C6_N.tga");	C6_N.LoadTextureA();
	C7_N = Texture("Textures/C7_N.tga");	C7_N.LoadTextureA();		C8_N = Texture("Textures/C8_N.tga");	C8_N.LoadTextureA();
	C9_N = Texture("Textures/C9_N.tga");	C9_N.LoadTextureA();		D1_N = Texture("Textures/D1_N.tga");	D1_N.LoadTextureA();
	D2_N = Texture("Textures/D2_N.tga");	D2_N.LoadTextureA();		D3_N = Texture("Textures/D3_N.tga");	D3_N.LoadTextureA();
	D4_N = Texture("Textures/D4_N.tga");	D4_N.LoadTextureA();		D5_N = Texture("Textures/D5_N.tga");	D5_N.LoadTextureA();
	D6_N = Texture("Textures/D6_N.tga");	D6_N.LoadTextureA();		D7_N = Texture("Textures/D7_N.tga");	D7_N.LoadTextureA();
	D8_N = Texture("Textures/D8_N.tga");	D8_N.LoadTextureA();		D9_N = Texture("Textures/D9_N.tga");	D9_N.LoadTextureA();

	//Los 40 Modelos en el Tablero
	Perry = Model();					Perry.LoadModel("Models/Perry.obj");
	Bombon = Model();					Bombon.LoadModel("Models/bombon.obj");
	BaymaxBlanco_M = Model();			BaymaxBlanco_M.LoadModel("Models/BaymaxBlanco/Bigmax_White_OBJ.obj");
	esf = Model();						esf.LoadModel("Models/esfera.obj");

	Gato = Model();						Gato.LoadModel("Models/gato.obj");
	Octi = Model();						Octi.LoadModel("Models/octi.obj");
	Arbol = Model();					Arbol.LoadModel("Models/arbol.obj");
	Burbuja = Model();					Burbuja.LoadModel("Models/burbuja.obj");
	Bellota = Model();					Bellota.LoadModel("Models/bellota.obj");
	Mojo = Model();						Mojo.LoadModel("Models/mojo.obj");
	Peludito = Model();					Peludito.LoadModel("Models/peludito.obj");
	Princesa = Model();					Princesa.LoadModel("Models/princesa.obj");
	Profesor = Model();					Profesor.LoadModel("Models/profesor.obj");
	Sedusa = Model();					Sedusa.LoadModel("Models/sedusa.obj");
	Casa = Model();						Casa.LoadModel("Models/casa.obj");
	Edificio = Model();					Edificio.LoadModel("Models/edificio.obj");
	Alcaldia = Model();					Alcaldia.LoadModel("Models/alcaldia.obj");
	HiroHamada_M = Model();				HiroHamada_M.LoadModel("Models/HiroHamada/hiro.obj");
	Planta1_M = Model();				Planta1_M.LoadModel("Models/Planta1/Phormium_1.obj");
	AutoChico_M = Model();				AutoChico_M.LoadModel("Models/AutoChico/isetta.obj");
	GogoTomago_M = Model();				GogoTomago_M.LoadModel("Models/GogoTomago/gogo.obj");
	Motocicleta_M = Model();			Motocicleta_M.LoadModel("Models/Motocicleta/motocicleta.obj");
	GoldenGate_M = Model();				GoldenGate_M.LoadModel("Models/GoldenGate/golden gate bridge.obj");
	Planta2_M = Model();				Planta2_M.LoadModel("Models/Planta2/hoewa_Forsteriana_1.obj");
	BaymaxSuperArmadura_M = Model();	BaymaxSuperArmadura_M.LoadModel("Models/BaymaxSuperArmadura/baymax_super.obj");
	AutoGrande_M = Model();				AutoGrande_M.LoadModel("Models/AutoGrande/500_fiat_lod_a.obj");
	Fred_M = Model();					Fred_M.LoadModel("Models/Fred/fred.obj");
	Planta3_M = Model();				Planta3_M.LoadModel("Models/Planta3/Planta3.obj");
	CasaHiro_M = Model();				CasaHiro_M.LoadModel("Models/CasaHiro/CasaHiro.obj");
	Megabot_M = Model();				Megabot_M.LoadModel("Models/Megabot/MegaBot.obj");
	Phineas = Model();					Phineas.LoadModel("Models/PHINEAS.obj");
	Ornitocyborg = Model();				Ornitocyborg.LoadModel("Models/OrnitoCyborg.obj");
	Isabella = Model();					Isabella.LoadModel("Models/Isabella.obj");
	PeterPanda = Model();				PeterPanda.LoadModel("Models/PeterPanda.obj");
	Doofenshmirtz = Model();			Doofenshmirtz.LoadModel("Models/Doofenshmirtz.obj");
	TerryTortuga = Model();				TerryTortuga.LoadModel("Models/TerryTortuga.obj");
	Candace = Model();					Candace.LoadModel("Models/Candace.obj");
	Doofenshmirtz2D = Model();			Doofenshmirtz2D.LoadModel("Models/Doofenshmirtz2D.obj");
	Buford = Model();					Buford.LoadModel("Models/Buford.obj");
	PinkyChihuahua = Model();			PinkyChihuahua.LoadModel("Models/PinkyChihuahua.obj");
	Carl = Model();						Carl.LoadModel("Models/Carl.obj");
	Ferb = Model();						Ferb.LoadModel("Models/Ferb.obj");
	Lampara = Model();					Lampara.LoadModel("Models/fobj_lamp_MODFIC.obj");
	Lampara2 = Model();					Lampara2.LoadModel("Models/obj_0401_street_lamp.obj");

	BaymaxBlanco_M = Model();			BaymaxBlanco_M.LoadModel("Models/BaymaxBlanco/CuerpoBaymax.obj");
	BrazoDerechoBaymax = Model();		BrazoDerechoBaymax.LoadModel("Models/BaymaxBlanco/BrazoDerecho.obj");
	ManoBaymax = Model();				ManoBaymax.LoadModel("Models/BaymaxBlanco/ManoBaymax.obj");
	DedoDerechoBaymax = Model();		DedoDerechoBaymax.LoadModel("Models/BaymaxBlanco/DedoDerecho.obj");
	DedoGordoBaymax = Model();			DedoGordoBaymax.LoadModel("Models/BaymaxBlanco/DedoGordo.obj");
	DedoIzquierdoBaymax = Model();		DedoIzquierdoBaymax.LoadModel("Models/BaymaxBlanco/DedoIzquierdo.obj");
	DedoMedioBaymax = Model();			DedoMedioBaymax.LoadModel("Models/BaymaxBlanco/DedoMedio.obj");

	// Edificios Cuidad
	Edificio1 = Model();
	Edificio1.LoadModel("Models/edificio1.obj");
	Edificio2 = Model();
	Edificio2.LoadModel("Models/edificio2.obj");
	Edificio3 = Model();
	Edificio3.LoadModel("Models/edificio3.obj");
	Edificio4 = Model();
	Edificio4.LoadModel("Models/edificio4.obj");
	Edificio5 = Model();
	Edificio5.LoadModel("Models/edificio5.obj");
	Edificio6 = Model();
	Edificio6.LoadModel("Models/edificio6.obj");

	//Phineas and Ferb
	Casa2 = Model();
	Casa2.LoadModel("Models/casa2.obj");
	Doof = Model();
	Doof.LoadModel("Models/doof.obj");
	Edificio7 = Model();
	Edificio7.LoadModel("Models/edificio7.obj");
	Edificio8 = Model();
	Edificio8.LoadModel("Models/edificio8.obj");
	Edificio9 = Model();
	Edificio9.LoadModel("Models/edificio9.obj");
	Edificio10 = Model();
	Edificio10.LoadModel("Models/edificio10.obj");

	//BIG HERO SIX
	Edificio15 = Model();
	Edificio15.LoadModel("Models/edificio15.obj");
	Edificio16 = Model();
	Edificio16.LoadModel("Models/edificio16.obj");
	Edificio17 = Model();
	Edificio17.LoadModel("Models/edificio17.obj");
	Edificio18 = Model();
	Edificio18.LoadModel("Models/edificio18.obj");
	Torre = Model();
	Torre.LoadModel("Models/torre.obj");
	Puente = Model();
	Puente.LoadModel("Models/puente.obj");

	std::vector<std::string> skyboxFaces_DIA;
	std::vector<std::string> skyboxFaces_NOCHE;

	// Texturas de SKYBOX.
	skyboxFaces_DIA.push_back("Textures/Skybox/sp2_rt.tga");
	skyboxFaces_DIA.push_back("Textures/Skybox/sp2_lf.tga");
	skyboxFaces_DIA.push_back("Textures/Skybox/sp2_dn.tga");
	skyboxFaces_DIA.push_back("Textures/Skybox/sp2_up.tga");
	skyboxFaces_DIA.push_back("Textures/Skybox/sp2_bk.tga");
	skyboxFaces_DIA.push_back("Textures/Skybox/sp2_ft.tga");

	skyboxFaces_NOCHE.push_back("Textures/Skybox/sp2_rt_noche.tga");
	skyboxFaces_NOCHE.push_back("Textures/Skybox/sp2_lf_noche.tga");
	skyboxFaces_NOCHE.push_back("Textures/Skybox/sp2_dn_noche.tga");
	skyboxFaces_NOCHE.push_back("Textures/Skybox/sp2_up_noche.tga");
	skyboxFaces_NOCHE.push_back("Textures/Skybox/sp2_bk_noche.tga");
	skyboxFaces_NOCHE.push_back("Textures/Skybox/sp2_ft_noche.tga");

	skyboxDia = Skybox(skyboxFaces_DIA);
	skyboxNoche = Skybox(skyboxFaces_NOCHE);

	Material_brillante = Material(4.0f, 256);
	Material_opaco = Material(0.3f, 4);

	LightDAY = DirectionalLight		(1.0f, 1.0f, 0.9f, 0.4f, 0.6f, 0.0f, -1.0f, 0.0f);
	LightNIGHT = DirectionalLight	(0.8f, 0.8f, 1.0f, 0.1f, 0.2f, 0.0f, -1.0f, 0.0f);

	unsigned int pointLightCount = 0;
	pointLights[0] = PointLight(1.0f, 1.0f, 1.0f, 5.0f, 3.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.2f, 0.1f);
	pointLightCount++;// LUZ ESQUINA 01.

	pointLights[1] = PointLight(1.0f, 1.0f, 1.0f, 3.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.2f, 0.1f);
	pointLightCount++;// LUZ DE SEGUIMIENTO.

	unsigned int spotLightCount = 0;
	
	spotLights[0] = SpotLight(1.0f, 1.0f, 1.0f, 4.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.1f, 0.05f, 45.0f);
	spotLightCount++;// LUZ ESQUINA 02.

	spotLights[1] = SpotLight(1.0f, 1.0f, 1.0f, 4.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.1f, 0.05f, 45.0f);
	spotLightCount++;// LUZ ESQUINA 03.
	
	spotLights[2] = SpotLight(1.0f, 1.0f, 1.0f, 4.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.1f, 0.05f, 45.0f);
	spotLightCount++;// LUZ ESQUINA 04.

	GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0, uniformEyePosition = 0, uniformSpecularIntensity = 0, uniformShininess = 0;
	GLuint uniformColor = 0;
	glm::mat4 projection = glm::perspective(45.0f, (GLfloat)mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 1000.0f);

	// Variables para rotacion de los Dados.
	movDado = 0.0f;		movOffsetDado = 0.8f;
	RotacionX4, RotacionZ4 = 0.0f;	RotacionX8, RotacionZ8 = 0.0f;
	DadoRotando = true;		DadoPiso = false;

	// Variables para movimiento en el Tablero.
	Posicion = 0;
	movX, movZ, giro, avance = 0.0f;
	movOffsetHeli = 0.5f;	V_Rot_Helice = 0.0f;
	UbiCesq1 = 54;	UbiCesq2 = 54;	new_pos = 0;
	Cas1 = true; Cas2 = false; Cas3 = false; Cas4 = false; PuedeSubir = false;

	PerPrincipal1 = true; PerPrincipal2 = false; PerPrincipal3 = false;

	// Variables para la Interacion de los modelos por movimiento.
	ultimaActivacion = 0.0f;	avanza2 = true;
	movYA1 = 0.0f; movYA2 = 0.0f; movYA3 = 0.0f; movYA4 = 0.0f; movYA5 = 0.0f; movYA6 = 0.0f; movYA7 = 0.0f; movYA8 = 0.0f; movYA9 = 0.0f; movYS1 = 0.0f;
	movYB1 = 0.0f; movYB2 = 0.0f; movYB3 = 0.0f; movYB4 = 0.0f; movYB5 = 0.0f; movYB6 = 0.0f; movYB7 = 0.0f; movYB8 = 0.0f; movYB9 = 0.0f; movYS2 = 0.0f;
	movYC1 = 0.0f; movYC2 = 0.0f; movYC3 = 0.0f; movYC4 = 0.0f; movYC5 = 0.0f; movYC6 = 0.0f; movYC7 = 0.0f; movYC8 = 0.0f; movYC9 = 0.0f; movYS3 = 0.0f;
	movYD1 = 0.0f; movYD2 = 0.0f; movYD3 = 0.0f; movYD4 = 0.0f; movYD5 = 0.0f; movYD6 = 0.0f; movYD7 = 0.0f; movYD8 = 0.0f; movYD9 = 0.0f;

	//Iluminacion
	T_Transcurrido = 0.0f;	FASE_01 = true;

	struct Giro4 { float x, z, valor; };
	Giro4 Vista_Caras4[4] = {
		{  60.0f,-125.0f, 1.0f},/*Numero 1*/
		{ 110.0f,   0.0f, 2.0f},/*Numero 2*/
		{ 360.0f, 360.0f, 3.0f},/*Numero 3*/
		{  60.0f, 125.0f, 4.0f},/*Numero 4*/
		
	};

	struct Giro8 { float x, z, valor; };
	Giro8 Vista_Caras8[8] = {
		{ -55.0f,  0.0f, 1.0f},/*Numero 1*/	{   0.0f, 235.0f, 2.0f},/*Numero 2*/
		{ 235.0f,  0.0f, 3.0f},/*Numero 3*/	{   0.0f, -55.0f, 4.0f},/*Numero 4*/
		{   0.0f, 55.0f, 5.0f},/*Numero 5*/	{   0.0f,-235.0f, 6.0f},/*Numero 6*/
		{  55.0f,  0.0f, 7.0f},/*Numero 7*/	{-235.0f,   0.0f, 8.0f},/*Numero 8*/
	};

	struct PCasillas { float mov; char activacion[3]; };
	PCasillas Mov_Casillas[40] = {
		{7.0f, "A1"},/*A1*/ {5.0f, "A2"},/*A2*/ {5.0f, "A3"},/*A3*/ {5.0f, "A4"},/*A4*/ {5.0f, "A5"},/*A5*/
		{5.0f, "A6"},/*A6*/ {5.0f, "A7"},/*A7*/ {5.0f, "A8"},/*A8*/ {5.0f, "A9"},/*A9*/ {7.0f, "S1"},/*S2*/

		{7.0f, "B1"},/*B1*/ {5.0f, "B2"},/*B2*/ {5.0f, "B3"},/*B3*/ {5.0f, "B4"},/*B4*/ {5.0f, "B5"},/*B5*/
		{5.0f, "B6"},/*B6*/ {5.0f, "B7"},/*B7*/ {5.0f, "B8"},/*B8*/ {5.0f, "B9"},/*B9*/ {7.0f, "S2"},/*S3*/

		{7.0f, "C1"},/*C1*/ {5.0f, "C2"},/*C2*/ {5.0f, "C3"},/*C3*/ {5.0f, "C4"},/*C4*/ {5.0f, "C5"},/*C5*/
		{5.0f, "C6"},/*C6*/ {5.0f, "C7"},/*C7*/ {5.0f, "C8"},/*C8*/ {5.0f, "C9"},/*C9*/ {7.0f, "S3"},/*S4*/

		{7.0f, "D1"},/*D1*/ {5.0f, "D2"},/*D2*/ {5.0f, "D3"},/*D3*/ {5.0f, "D4"},/*D4*/ {5.0f, "D5"},/*D5*/
		{5.0f, "D6"},/*D6*/ {5.0f, "D7"},/*D7*/ {5.0f, "D8"},/*D8*/ {5.0f, "D9"},/*D9*/ {7.0f, "S4"}/*S1*/ };

	while (!mainWindow.getShouldClose()) {
		GLfloat now = glfwGetTime();
		deltaTime = now - lastTime;
		deltaTime += (now - lastTime) / limitFPS;
		lastTime = now;

		T_Transcurrido += deltaTime;
		if (T_Transcurrido >= TIEMPO_CAMBIO) { FASE_01 = !FASE_01; T_Transcurrido = 0.0f; }

		float angle = (T_Transcurrido / TIEMPO_CAMBIO) * 3.14159f;

		// Calcular la dirección basada en el ángulo
		float xDir = cos(angle);

		//-- Movimiento para el tiro de los Dados --
		if (mainWindow.gettiro() == true && DadoRotando == true) {
			movDado -= movOffsetDado * deltaTime;

			int sec_D4 = rand() % 4;//Giro para el Dado 4.
			Giro4 rot4 = Vista_Caras4[sec_D4];
			RotacionX4 = rot4.x; RotacionZ4 = rot4.z;
			mainWindow.setUltimoValorDado4(rot4.valor);

			int sec_D8 = rand() % 8;//Giro para el Dado 8.
			Giro8 rot8 = Vista_Caras8[sec_D8];
			RotacionX8 = rot8.x; RotacionZ8 = rot8.z;
			mainWindow.setUltimoValorDado8(rot8.valor);

			if (movDado < -24.0f) {
				DadoRotando = false;
				DadoPiso = true;
				PuedeSubir = false;
				avance = rot4.valor + rot8.valor;
				printf("\n - - - - - - - - - \n Los valores de los dados en el ultimo tiro fueron : \n");
				printf("Valor del Dado4: %.0f\n", rot4.valor);
				printf("Valor del Dado8: %.0f\n", rot8.valor);
				printf("Numero de Casillas a mover: %.0f\n", avance);

				do {
					if (Posicion == 40) { Posicion = 0; }
					PCasillas movcasilla = Mov_Casillas[Posicion];
					new_pos += movcasilla.mov;
					strcpy_s(casilla_Activacion, sizeof(casilla_Activacion), movcasilla.activacion);  // Versión segura  // Usar strcpy para copiar el string
					Posicion++; avance--;
					printf("Sumando, valor nuevo = %f\nEstamos en el arreglo = %d, de valor = %f\n", new_pos, Posicion, movcasilla.mov);
					printf("Nombre de la casilla: %s\n", casilla_Activacion);
				} while (avance != 0);
				printf("\n PROCEDEMOS CON EL MOVIMIENTO \n");
				Continuar = true;
			}
		}

		if (mainWindow.getreinicio() == true && DadoPiso == true) { movDado = 0.0f; DadoRotando = true;  DadoPiso = false; }

		if (Continuar = true) {
			if (Cas1 == true) {
				if (movZ >= new_pos) {PuedeSubir = true; }
				if (movZ < new_pos) {
					movZ += movOffsetHeli * deltaTime;
					if (movZ > 54) {
						Cas1 = false; Cas2 = true;
						new_pos = new_pos - 54;
						PuedeSubir = true;
						giro -= 90.0f;
						printf("\n C1Valor new_pos: %f\n", new_pos);
					}
				}
			}
			else if (Cas2 == true) {
				if (movX <= (-new_pos)) { PuedeSubir = true; }
				if (movX > (-new_pos)) {
					movX -= movOffsetHeli * deltaTime;
					if (movX < -54) {
						Cas2 = false; Cas3 = true;
						new_pos = new_pos - 54;
						PuedeSubir = true;
						giro -= 90.0f;
						printf("\n C2Valor new_pos: %f\n", new_pos);
					}
				}
			}
			else if (Cas3 == true) {
				if (movZ <= (-new_pos + UbiCesq1)) { PuedeSubir = true; }
				if (movZ > (-new_pos + UbiCesq1)) {
					movZ -= movOffsetHeli * deltaTime;
					if (movZ < 1) {
						Cas3 = false; Cas4 = true;
						new_pos = new_pos - 54;
						PuedeSubir = true;
						giro -= 90.0f;
						printf("\n C3Valor new_pos: %f\n", new_pos);
					}
				}
				else if (movZ == (-new_pos + UbiCesq1)) { UbiCesq1 = movZ; }
			}
			else if (Cas4 == true) {
				if (movX >= (new_pos - UbiCesq2)) { PuedeSubir = true; }
				if (movX < (new_pos - UbiCesq2)) {
					movX += movOffsetHeli * deltaTime;
					if (movX > -1) {
						Cas4 = false; Cas1 = true; Cas2 = false; Cas3 = false;
						new_pos = new_pos - 54;
						PuedeSubir = true;
						giro -= 90.0f;
						printf("\n C4Valor new_pos: %f\n", new_pos);
						if(PerPrincipal1 == true){ PerPrincipal1 = false; PerPrincipal2 = true; PerPrincipal3 = false; }
						else if (PerPrincipal2 == true) { PerPrincipal1 = false; PerPrincipal2 = false; PerPrincipal3 = true; }
						else if (PerPrincipal3 == true) { PerPrincipal1 = true; PerPrincipal2 = false; PerPrincipal3 = false; }
					}
				}
				else if (movX == (new_pos - UbiCesq2)) { UbiCesq2 = movX; }
			}
		}

		//Animacion BAYMAX "SALUDO"
		if (mueveBrazo) {
			if (giroBrazo < 85 or giroBrazo > 90) {
				giroBrazo += giroBrazoOffset * deltaTime;
			}
			else { mueveBrazo = !mueveBrazo; mueveMano = true; }
			if (giroBrazo > 180) { giroBrazo = 0.0; giraDedos = 0.0; giraMano = 0.0; }
		}
		else {
			if (mueveMano) {
				if (giraMano < 90) { giraMano += giraManoOffset * deltaTime; }
				else {
					giroBrazo = 91; mueveMano = -!mueveMano;
					giraDedos += 0.5f * deltaTime; mueveBrazo = true;
				}
			}
		}

		// --- Casillas de la CHICAS SUPERPODEROSAS ---

		//GATO
		if (strcmp(casilla_Activacion, "A1") == 0) {
			strcpy_s(ultimaCasillaGato, sizeof(ultimaCasillaGato), "A1");
			if (PuedeSubir == true && avanzaGato) {// Subiendo
				if (movYA1 < 6.25f) {movYA1 += 0.3 * movOffsetHeli * deltaTime; rotA1 += 17.0 * deltaTime;}
				else {avanzaGato = false;ultimaActivacionGato = now;}}
			else if (!avanzaGato && (now - ultimaActivacionGato) >= 3.0f) {// Espera de 3 segundos
				if (movYA1 > 0.0f) {movYA1 -= 0.3 * movOffsetHeli * deltaTime; rotA1 -= 17.0 * deltaTime;}}
		}
		else if (strcmp(ultimaCasillaGato, "A1") == 0) {// Tirada de dados antes de los 3 segundos
			if (movYA1 > 0.0f) { movYA1 -= 0.3 * movOffsetHeli * deltaTime; rotA1 -= 17.0 * deltaTime;}
			else {strcpy_s(ultimaCasillaGato, sizeof(ultimaCasillaGato), ""); avanzaGato = true;}
		}

		//OCTI
		if (strcmp(casilla_Activacion, "A2") == 0) {
			strcpy_s(ultimaCasillaOcti, sizeof(ultimaCasillaOcti), "A2");
			if (PuedeSubir == true && avanzaOcti) {
				if (movYA2 < 6.25f) { movYA2 += 0.3 * movOffsetHeli * deltaTime; rotA2 += 17.0 * deltaTime;}
				else {avanzaOcti = false; ultimaActivacionOcti = now;}}
			else if (!avanzaOcti && (now - ultimaActivacionOcti) >= 3.0f) {// Espera de 3 segundos
				if (movYA2 > 0.0f) { movYA2 -= 0.3 * movOffsetHeli * deltaTime; rotA2 -= 17.0 * deltaTime;}}
		}
		else if (strcmp(ultimaCasillaOcti, "A2") == 0) {
			if (movYA2 > 0.0f) { movYA2 -= 0.3 * movOffsetHeli * deltaTime; rotA2 -= 17.0 * deltaTime;}
			else {strcpy_s(ultimaCasillaOcti, sizeof(ultimaCasillaOcti), ""); avanzaOcti = true;}
		}

		//ARBOL 
		if (strcmp(casilla_Activacion, "A3") == 0) {
			strcpy_s(ultimaCasillaArbol, sizeof(ultimaCasillaArbol), "A3");
			if (PuedeSubir == true && avanzaArbol) {
				if (movYA3 < 6.25f) { movYA3 += 0.3 * movOffsetHeli * deltaTime; rotA3 += 17.0 * deltaTime; }
				else {avanzaArbol = false; ultimaActivacionArbol = now;}}
			else if (!avanzaArbol && (now - ultimaActivacionArbol) >= 3.0f) {// Espera de 3 segundos
				if (movYA3 > 0.0f) { movYA3 -= 0.3 * movOffsetHeli * deltaTime; rotA3 -= 17.0 * deltaTime; }}
		}
		else if (strcmp(ultimaCasillaArbol, "A3") == 0) {
			if (movYA3 > 0.0f) {movYA3 -= 0.3 * movOffsetHeli * deltaTime; rotA3 -= 17.0 * deltaTime;}
			else {strcpy_s(ultimaCasillaArbol, sizeof(ultimaCasillaArbol), "");avanzaArbol = true;}
		}

		//BURBUJA 
		if (strcmp(casilla_Activacion, "A4") == 0) {
			strcpy_s(ultimaCasillaBurbuja, sizeof(ultimaCasillaBurbuja), "A4");
			if (PuedeSubir == true && avanzaBurbuja) {
				if (movYA4 < 6.25f) {movYA4 += 0.3 * movOffsetHeli * deltaTime; rotA4 += 17.0 * deltaTime;}
				else {avanzaBurbuja = false; ultimaActivacionBurbuja = now;}}
			else if (!avanzaBurbuja && (now - ultimaActivacionBurbuja) >= 3.0f) {// Espera de 3 segundos
				if (movYA4 > 0.0f) { movYA4 -= 0.3 * movOffsetHeli * deltaTime; rotA4 -= 17.0 * deltaTime; }}
		}
		else if (strcmp(ultimaCasillaBurbuja, "A4") == 0) {
			if (movYA4 > 0.0f) {movYA4 -= 0.3 * movOffsetHeli * deltaTime; rotA4 -= 17.0 * deltaTime;}
			else {strcpy_s(ultimaCasillaBurbuja, sizeof(ultimaCasillaBurbuja), ""); avanzaBurbuja = true;}
		}

		//BELLOTA 
		if (strcmp(casilla_Activacion, "A5") == 0) {
			strcpy_s(ultimaCasillaBellota, sizeof(ultimaCasillaBellota), "A5");
			if (PuedeSubir == true && avanzaBellota) {
				if (movYA5 < 6.25f) {movYA5 += 0.3 * movOffsetHeli * deltaTime; rotA5 += 17.0 * deltaTime;}
				else {avanzaBellota = false; ultimaActivacionBellota = now;}}
			else if (!avanzaBellota && (now - ultimaActivacionBellota) >= 3.0f) {// Espera de 3 segundos
				if (movYA5 > 0.0f) { movYA5 -= 0.3 * movOffsetHeli * deltaTime; rotA5 -= 17.0 * deltaTime; }}
		}
		else if (strcmp(ultimaCasillaBellota, "A5") == 0) {
			if (movYA5 > 0.0f) {movYA5 -= 0.3 * movOffsetHeli * deltaTime; rotA5 -= 17.0 * deltaTime;}
			else {strcpy_s(ultimaCasillaBellota, sizeof(ultimaCasillaBellota), "");avanzaBellota = true;}
		}

		//MOJO JOJO 
		if (strcmp(casilla_Activacion, "A6") == 0) {
			strcpy_s(ultimaCasillaMojoJojo, sizeof(ultimaCasillaMojoJojo), "A6");
			if (PuedeSubir == true && avanzaMojoJojo) {
				if (movYA6 < 6.25f) { movYA6 += 0.3 * movOffsetHeli * deltaTime; rotA6 += 17.0 * deltaTime; }
				else { avanzaMojoJojo = false; ultimaActivacionMojoJojo = now; }}
			else if (!avanzaMojoJojo && (now - ultimaActivacionMojoJojo) >= 3.0f) {// Espera de 3 segundos
				if (movYA6 > 0.0f) { movYA6 -= 0.3 * movOffsetHeli * deltaTime; rotA6 -= 17.0 * deltaTime; }}
		}
		else if (strcmp(ultimaCasillaMojoJojo, "A6") == 0) {
			if (movYA6 > 0.0f) { movYA6 -= 0.3 * movOffsetHeli * deltaTime; rotA6 -= 17.0 * deltaTime; }
			else { strcpy_s(ultimaCasillaMojoJojo, sizeof(ultimaCasillaMojoJojo), ""); avanzaMojoJojo = true; }
		}

		//PELUDITO 
		if (strcmp(casilla_Activacion, "A7") == 0) {
			strcpy_s(ultimaCasillaPeludito, sizeof(ultimaCasillaPeludito), "A7");
			if (PuedeSubir == true && avanzaPeludito) {
				if (movYA7 < 6.25f) {movYA7 += 0.3 * movOffsetHeli * deltaTime; rotA7 += 17.0 * deltaTime;}
				else {avanzaPeludito = false; ultimaActivacionPeludito = now;}}
			else if (!avanzaPeludito && (now - ultimaActivacionPeludito) >= 3.0f) {// Espera de 3 segundos
				if (movYA7 > 0.0f) { movYA7 -= 0.3 * movOffsetHeli * deltaTime; rotA7 -= 17.0 * deltaTime;}}
		}
		else if (strcmp(ultimaCasillaPeludito, "A7") == 0) {
			if (movYA7 > 0.0f) {movYA7 -= 0.3 * movOffsetHeli * deltaTime; rotA7 -= 17.0 * deltaTime;}
			else {strcpy_s(ultimaCasillaPeludito, sizeof(ultimaCasillaPeludito), ""); avanzaPeludito = true;}
		}

		//PRINCESA 
		if (strcmp(casilla_Activacion, "A8") == 0) {
			strcpy_s(ultimaCasillaPrincesa, sizeof(ultimaCasillaPrincesa), "A8");
			if (PuedeSubir == true && avanzaPrincesa) {
				if (movYA8 < 6.25f) {movYA8 += 0.3 * movOffsetHeli * deltaTime; rotA8 += 17.0 * deltaTime;}
				else {avanzaPrincesa = false; ultimaActivacionPrincesa = now;}}
			else if (!avanzaPrincesa && (now - ultimaActivacionPrincesa) >= 3.0f) {// Espera de 3 segundos
				if (movYA8 > 0.0f) { movYA8 -= 0.3 * movOffsetHeli * deltaTime; rotA8 -= 17.0 * deltaTime;}}
		}
		else if (strcmp(ultimaCasillaPrincesa, "A8") == 0) {
			if (movYA8 > 0.0f) {movYA8 -= 0.3 * movOffsetHeli * deltaTime; rotA8 -= 17.0 * deltaTime;}
			else {strcpy_s(ultimaCasillaPrincesa, sizeof(ultimaCasillaPrincesa), "");avanzaPrincesa = true;}
		}

		//UTONIUM 
		if (strcmp(casilla_Activacion, "A9") == 0) {
			strcpy_s(ultimaCasillaProfesor, sizeof(ultimaCasillaProfesor), "A9");
			if (PuedeSubir == true && avanzaProfesor) {
				if (movYA9 < 6.25f) {movYA9 += 0.3 * movOffsetHeli * deltaTime; rotA9 += 17.0 * deltaTime;}
				else {avanzaProfesor = false; ultimaActivacionProfesor = now;}}
			else if (!avanzaProfesor && (now - ultimaActivacionProfesor) >= 3.0f) {// Espera de 3 segundos
				if (movYA9 > 0.0f) { movYA9 -= 0.3 * movOffsetHeli * deltaTime; rotA9 -= 17.0 * deltaTime; }
			}
		}
		else if (strcmp(ultimaCasillaProfesor, "A9") == 0) {
			if (movYA9 > 0.0f) {movYA9 -= 0.3 * movOffsetHeli * deltaTime; rotA9 -= 17.0 * deltaTime;}
			else {strcpy_s(ultimaCasillaProfesor, sizeof(ultimaCasillaProfesor), "");avanzaProfesor = true;}
		}

		//SEDUSA 
		if (strcmp(casilla_Activacion, "S1") == 0) {
			strcpy_s(ultimaCasillaSedusa, sizeof(ultimaCasillaSedusa), "S1");
			if (PuedeSubir == true && avanzaSedusa) {
				if (movYS1 < 7.25f) {movYS1 += 0.3 * movOffsetHeli * deltaTime; rotS1 += 15.0 * deltaTime;}
				else {avanzaSedusa = false; ultimaActivacionSedusa = now;}}
			else if (!avanzaSedusa && (now - ultimaActivacionSedusa) >= 3.0f) {// Espera de 3 segundos
				if (movYS1 > 0.0f) { movYS1 -= 0.3 * movOffsetHeli * deltaTime; rotS1 -= 15.0 * deltaTime; }
			}
		}
		else if (strcmp(ultimaCasillaSedusa, "S1") == 0) {
			if (movYS1 > 0.0f) {movYS1 -= 0.3 * movOffsetHeli * deltaTime; rotS1 -= 15.0 * deltaTime;}
			else {strcpy_s(ultimaCasillaSedusa, sizeof(ultimaCasillaSedusa), ""); avanzaSedusa = true;}
		}

		//CASA_CSP 
		if (strcmp(casilla_Activacion, "B1") == 0) {
			strcpy_s(ultimaCasillaCasaCSP, sizeof(ultimaCasillaCasaCSP), "B1");
			if (PuedeSubir == true && avanzaCasaCSP) {
				if (movYB1 < 6.25f) { movYB1 += 0.3 * movOffsetHeli * deltaTime; rotB1 += 17.2 * deltaTime; }
				else { avanzaCasaCSP = false; ultimaActivacionCasaCSP = now; }
			}
			else if (!avanzaCasaCSP && (now - ultimaActivacionCasaCSP) >= 3.0f) {// Espera de 3 segundos
				if (movYB1 > 0.0f) { movYB1 -= 0.3 * movOffsetHeli * deltaTime; rotB1 -= 17.2 * deltaTime; }
			}
		}
		else if (strcmp(ultimaCasillaCasaCSP, "B1") == 0) {
			if (movYB1 > 0.0f) {movYB1 -= 0.3 * movOffsetHeli * deltaTime; rotB1 -= 17.2 * deltaTime;}
			else {strcpy_s(ultimaCasillaCasaCSP, sizeof(ultimaCasillaCasaCSP), "");avanzaCasaCSP = true;}
		}

		//EdificioCSP 
		if (strcmp(casilla_Activacion, "B2") == 0) {
			strcpy_s(ultimaCasillaEdificioCSP, sizeof(ultimaCasillaEdificioCSP), "B2");
			if (PuedeSubir == true && avanzaEdificioCSP) {
				if (movYB2 < 16.75f) {movYB2 += 0.3 * movOffsetHeli * deltaTime; rotB2 += 6.4 * deltaTime;}
				else {avanzaEdificioCSP = false; ultimaActivacionEdificioCSP = now;}}
			else if (!avanzaEdificioCSP && (now - ultimaActivacionEdificioCSP) >= 3.0f) {// Espera de 3 segundos
				if (movYB2 > 0.0f) { movYB2 -= 0.3 * movOffsetHeli * deltaTime; rotB2 -= 6.4 * deltaTime; }}
		}
		else if (strcmp(ultimaCasillaEdificioCSP, "B2") == 0) {
			if (movYB2 > 0.0f) {movYB2 -= 0.3 * movOffsetHeli * deltaTime;  rotB2 -= 6.4 * deltaTime;}
			else {strcpy_s(ultimaCasillaEdificioCSP, sizeof(ultimaCasillaEdificioCSP), "");avanzaEdificioCSP = true;}
		}

		//ALCALDIA_CSP 
		if (strcmp(casilla_Activacion, "B3") == 0) {
			strcpy_s(ultimaCasillaAlcaldia, sizeof(ultimaCasillaAlcaldia), "B3");
			if (PuedeSubir == true && avanzaAlcaldia) {
				if (movYB3 < 6.25f) { movYB3 += 0.3 * movOffsetHeli * deltaTime; rotB3 += 17.2 * deltaTime; }
				else { avanzaAlcaldia = false; ultimaActivacionAlcaldia = now;}}
			else if (!avanzaAlcaldia && (now - ultimaActivacionAlcaldia) >= 3.0f) {// Espera de 3 segundos
				if (movYB3 > 0.0f) { movYB3 -= 0.3 * movOffsetHeli * deltaTime; rotB3 -= 17.2 * deltaTime; }}
		}
		else if (strcmp(ultimaCasillaAlcaldia, "B3") == 0) {
			if (movYB3 > 0.0f) {movYB3 -= 0.3 * movOffsetHeli * deltaTime; rotB3 -= 17.0 * deltaTime;}
			else {strcpy_s(ultimaCasillaAlcaldia, sizeof(ultimaCasillaAlcaldia), "");avanzaAlcaldia = true; }
		}

		// --- Casillas de BIG HERO 6 ---
		
		//Hiro Hamada
		if (strcmp(casilla_Activacion, "B4") == 0) {
			strcpy_s(ultimaCasillaHiroHamada_M, sizeof(ultimaCasillaHiroHamada_M), "B4");
			if (PuedeSubir == true && avanzaHiroHamada_M) {
				if (movYB4 < 12.25f) { movYB4 += 0.3 *  movOffsetHeli * deltaTime; rotB4 += 13.2 * deltaTime;}
				else {avanzaHiroHamada_M = false; ultimaActivacionHiroHamada_M = now;}}
			else if (!avanzaHiroHamada_M && (now - ultimaActivacionHiroHamada_M) >= 3.0f) {// Espera de 3 segundos
				if (movYB4 > 0.0f) { movYB4 -= 0.3 * movOffsetHeli * deltaTime; rotB4 -= 13.2 * deltaTime; }}
		}
		else if (strcmp(ultimaCasillaHiroHamada_M, "B4") == 0) {
			if (movYB4 > 0.0f) { movYB4 -= 0.3 * movOffsetHeli * deltaTime; rotB4 -= 13.2 * deltaTime;}
			else {strcpy_s(ultimaCasillaHiroHamada_M, sizeof(ultimaCasillaHiroHamada_M), "");avanzaHiroHamada_M = true;}
		}

		//Planta 01
		if (strcmp(casilla_Activacion, "B5") == 0) {
			strcpy_s(ultimaCasillaPlanta1_M, sizeof(ultimaCasillaPlanta1_M), "B5");
			if (PuedeSubir == true && avanzaPlanta1_M) {
				if (movYB5 < 12.25f) { movYB5 += 0.3 * movOffsetHeli * deltaTime; rotB5 += 13.2 * deltaTime;}
				else {avanzaPlanta1_M = false; ultimaActivacionPlanta1_M = now;}}
			else if (!avanzaPlanta1_M && (now - ultimaActivacionPlanta1_M) >= 3.0f) {// Espera de 3 segundos
				if (movYB5 > 0.0f) { movYB5 -= 0.3 * movOffsetHeli * deltaTime; rotB5 -= 13.2 * deltaTime; }}
		}
		else if (strcmp(ultimaCasillaPlanta1_M, "B5") == 0) {
			if (movYB5 > 0.0f) { movYB5 -= 0.3 * movOffsetHeli * deltaTime; rotB5 -= 13.2 * deltaTime;}
			else {strcpy_s(ultimaCasillaPlanta1_M, sizeof(ultimaCasillaPlanta1_M), "");avanzaPlanta1_M = true;}
		}

		//Auto Chico
		if (strcmp(casilla_Activacion, "B6") == 0) {
			strcpy_s(ultimaCasillaAutoChico_M, sizeof(ultimaCasillaAutoChico_M), "B6");
			if (PuedeSubir == true && avanzaAutoChico_M) {
				if (movYB6 < 12.25f) { movYB6 += 0.3 * movOffsetHeli * deltaTime; rotB6 += 13.2 * deltaTime;}
				else {avanzaAutoChico_M = false; ultimaActivacionAutoChico_M = now;}}
			else if (!avanzaAutoChico_M && (now - ultimaActivacionAutoChico_M) >= 3.0f) {// Espera de 3 segundos
				if (movYB6 > 0.0f) { movYB6 -= 0.3 * movOffsetHeli * deltaTime; rotB6 -= 13.2 * deltaTime; }}
		}
		else if (strcmp(ultimaCasillaAutoChico_M, "B6") == 0) {
			if (movYB6 > 0.0f) { movYB6 -= 0.3 * movOffsetHeli * deltaTime; rotB6 -= 13.2 * deltaTime;}
			else {strcpy_s(ultimaCasillaAutoChico_M, sizeof(ultimaCasillaAutoChico_M), "");avanzaAutoChico_M = true;}
		}

		//Gogo Tomago
		if (strcmp(casilla_Activacion, "B7") == 0) {
			strcpy_s(ultimaCasillaGogoTomago_M, sizeof(ultimaCasillaGogoTomago_M), "B7");
			if (PuedeSubir == true && avanzaGogoTomago_M) {
				if (movYB7 < 12.25f) { movYB7 += 0.3 * movOffsetHeli * deltaTime; rotB7 += 13.2 * deltaTime;}
				else {avanzaGogoTomago_M = false; ultimaActivacionGogoTomago_M = now;}}
			else if (!avanzaGogoTomago_M && (now - ultimaActivacionGogoTomago_M) >= 3.0f) {// Espera de 3 segundos
				if (movYB7 > 0.0f) { movYB7 -= 0.3 * movOffsetHeli * deltaTime; rotB7 -= 13.2 * deltaTime;}}
		}
		else if (strcmp(ultimaCasillaGogoTomago_M, "B7") == 0) {
			if (movYB7 > 0.0f) { movYB7 -= 0.3 * movOffsetHeli * deltaTime; rotB7 -= 13.2 * deltaTime;}
			else {strcpy_s(ultimaCasillaGogoTomago_M, sizeof(ultimaCasillaGogoTomago_M), "");avanzaGogoTomago_M = true;}
		}

		//Motocicleta
		if (strcmp(casilla_Activacion, "B8") == 0) {
			strcpy_s(ultimaCasillaMotocicleta_M, sizeof(ultimaCasillaMotocicleta_M), "B8");
			if (PuedeSubir == true && avanzaMotocicleta_M) {
				if (movYB8 < 12.25f) { movYB8 += 0.3 * movOffsetHeli * deltaTime; rotB8 += 13.2 * deltaTime;}
				else {avanzaMotocicleta_M = false; ultimaActivacionMotocicleta_M = now;}}
			else if (!avanzaMotocicleta_M && (now - ultimaActivacionMotocicleta_M) >= 3.0f) {// Espera de 3 segundos
				if (movYB8 > 0.0f) { movYB8 -= 0.3 * movOffsetHeli * deltaTime; rotB8 -= 13.2 * deltaTime; }}
		}
		else if (strcmp(ultimaCasillaMotocicleta_M, "B8") == 0) {
			if (movYB8 > 0.0f) { movYB8 -= 0.3 * movOffsetHeli * deltaTime; rotB8 -= 13.2 * deltaTime;}
			else {strcpy_s(ultimaCasillaMotocicleta_M, sizeof(ultimaCasillaMotocicleta_M), "");avanzaMotocicleta_M = true; }
		}

		//GoldenGate
		if (strcmp(casilla_Activacion, "B9") == 0) {
			strcpy_s(ultimaCasillaGoldenGate_M, sizeof(ultimaCasillaGoldenGate_M), "B9");
			if (PuedeSubir == true && avanzaGoldenGate_M) {
				if (movYB9 < 12.25f) { movYB9 += 0.3 * movOffsetHeli * deltaTime; rotB9 += 13.2 * deltaTime;}
				else {avanzaGoldenGate_M = false; ultimaActivacionGoldenGate_M = now;}}
			else if (!avanzaGoldenGate_M && (now - ultimaActivacionGoldenGate_M) >= 3.0f) {// Espera de 3 segundos
				if (movYB9 > 0.0f) { movYB9 -= 0.3 * movOffsetHeli * deltaTime; rotB9 -= 13.2 * deltaTime; }}
		}
		else if (strcmp(ultimaCasillaGoldenGate_M, "B9") == 0) {
			if (movYB9 > 0.0f) { movYB9 -= 0.3 * movOffsetHeli * deltaTime; rotB9 -= 13.2 * deltaTime;}
			else {strcpy_s(ultimaCasillaGoldenGate_M, sizeof(ultimaCasillaGoldenGate_M), "");avanzaGoldenGate_M = true; }
		}

		//Planta 2
		if (strcmp(casilla_Activacion, "S2") == 0) {
			strcpy_s(ultimaCasillaPlanta2_M, sizeof(ultimaCasillaPlanta2_M), "S2");
			if (PuedeSubir == true && avanzaPlanta2_M) {
				if (movYS2 < 12.25f) { movYS2 += 0.3 * movOffsetHeli * deltaTime; rotS2 += 13.2 * deltaTime;}
				else {avanzaPlanta2_M = false; ultimaActivacionPlanta2_M = now;}}
			else if (!avanzaPlanta2_M && (now - ultimaActivacionPlanta2_M) >= 3.0f) {// Espera de 3 segundos
				if (movYS2 > 0.0f) { movYS2 -= 0.3 * movOffsetHeli * deltaTime; rotS2 -= 13.2 * deltaTime; }
			}
		}
		else if (strcmp(ultimaCasillaPlanta2_M, "S2") == 0) {
			if (movYS2 > 0.0f) { movYS2 -= 0.3 * movOffsetHeli * deltaTime; rotS2 -= 13.2 * deltaTime;}
			else {strcpy_s(ultimaCasillaPlanta2_M, sizeof(ultimaCasillaPlanta2_M), ""); avanzaPlanta2_M = true;}
		}

		//Baymax Super Armadura
		if (strcmp(casilla_Activacion, "C1") == 0) {
			strcpy_s(ultimaCasillaBaymaxSuperArmadura_M, sizeof(ultimaCasillaBaymaxSuperArmadura_M), "C1");
			if (PuedeSubir == true && avanzaBaymaxSuperArmadura_M) {
				if (movYC1 < 16.75f) { movYC1 += 0.3 * movOffsetHeli * deltaTime; rotC1 += 6.4 * deltaTime;}
				else {avanzaBaymaxSuperArmadura_M = false; ultimaActivacionBaymaxSuperArmadura_M = now;}}
			else if (!avanzaBaymaxSuperArmadura_M && (now - ultimaActivacionBaymaxSuperArmadura_M) >= 3.0f) {// Espera de 3 segundos
				if (movYC1 > 0.0f) { movYC1 -= 0.3 * movOffsetHeli * deltaTime; rotC1 -= 6.4 * deltaTime; }
			}
		}
		else if (strcmp(ultimaCasillaBaymaxSuperArmadura_M, "C1") == 0) {
			if (movYC1 > 0.0f) { movYC1 -= 0.3 * movOffsetHeli * deltaTime; rotC1 -= 11.9 * deltaTime;}
			else {strcpy_s(ultimaCasillaBaymaxSuperArmadura_M, sizeof(ultimaCasillaBaymaxSuperArmadura_M), "");avanzaBaymaxSuperArmadura_M = true;}
		}

		//Auto Grande
		if (strcmp(casilla_Activacion, "C2") == 0) {
			strcpy_s(ultimaCasillaAutoGrande_M, sizeof(ultimaCasillaAutoGrande_M), "C2");
			if (PuedeSubir == true && avanzaAutoGrande_M) {
				if (movYC2 < 12.25f) { movYC2 += 0.3 *movOffsetHeli * deltaTime; rotC2 += 13.2 * deltaTime;}
				else {avanzaAutoGrande_M = false; ultimaActivacionAutoGrande_M = now;}}
			else if (!avanzaAutoGrande_M && (now - ultimaActivacionAutoGrande_M) >= 3.0f) {// Espera de 3 segundos
				if (movYC2 > 0.0f) { movYC2 -= 0.3 * movOffsetHeli * deltaTime; rotC2 -= 13.2 * deltaTime; }}
		}
		else if (strcmp(ultimaCasillaAutoGrande_M, "C2") == 0) {
			if (movYC2 > 0.0f) { movYC2 -= 0.3 * movOffsetHeli * deltaTime; rotC2 -= 13.2 * deltaTime;}
			else {strcpy_s(ultimaCasillaAutoGrande_M, sizeof(ultimaCasillaAutoGrande_M), ""); avanzaAutoGrande_M = true;}
		}

		//Fred
		if (strcmp(casilla_Activacion, "C3") == 0) {
			strcpy_s(ultimaCasillaFred_M, sizeof(ultimaCasillaFred_M), "C3");
			if (PuedeSubir == true && avanzaFred_M) {
				if (movYC3 < 12.25f) { movYC3 += 0.3 * movOffsetHeli * deltaTime; rotC3 += 13.2 * deltaTime;}
				else {avanzaFred_M = false; ultimaActivacionFred_M = now;}}
			else if (!avanzaFred_M && (now - ultimaActivacionFred_M) >= 3.0f) {// Espera de 3 segundos
				if (movYC3 > 0.0f) { movYC3 -= 0.3 * movOffsetHeli * deltaTime; rotC3 -= 13.2 * deltaTime; }
			}
		}
		else if (strcmp(ultimaCasillaFred_M, "C3") == 0) {
			if (movYC3 > 0.0f) { movYC3 -= 0.3 * movOffsetHeli * deltaTime; rotC3-= 13.2 * deltaTime;}
			else {strcpy_s(ultimaCasillaFred_M, sizeof(ultimaCasillaFred_M), ""); avanzaFred_M = true;}
		}

		//Planta 3
		if (strcmp(casilla_Activacion, "C4") == 0) {
			strcpy_s(ultimaCasillaPlanta3_M, sizeof(ultimaCasillaPlanta3_M), "C4");
			if (PuedeSubir == true && avanzaPlanta3_M) {
				if (movYC4 < 12.25f) { movYC4 += 0.3 * movOffsetHeli * deltaTime; rotC4 += 13.2 * deltaTime; }
				else { avanzaPlanta3_M = false; ultimaActivacionPlanta3_M = now; }
			}
			else if (!avanzaPlanta3_M && (now - ultimaActivacionPlanta3_M) >= 3.0f) {// Espera de 3 segundos
				if (movYC4 > 0.0f) { movYC4 -= 0.3 * movOffsetHeli * deltaTime; rotC4 -= 13.2 * deltaTime; }
			}
		}
		else if (strcmp(ultimaCasillaPlanta3_M, "C4") == 0) {
			if (movYC4 > 0.0f) { movYC4 -= 0.3 * movOffsetHeli * deltaTime; rotC4 -= 13.2 * deltaTime;}
			else {strcpy_s(ultimaCasillaPlanta3_M, sizeof(ultimaCasillaPlanta3_M), ""); avanzaPlanta3_M = true;}
		}

		//Casa Hiro
		if (strcmp(casilla_Activacion, "C5") == 0) {
			strcpy_s(ultimaCasillaCasaHiro_M, sizeof(ultimaCasillaCasaHiro_M), "C5");
			if (PuedeSubir == true && avanzaCasaHiro_M) {
				if (movYC5 < 12.25f) { movYC5 += 0.3 * movOffsetHeli * deltaTime; rotC5 += 13.2 * deltaTime; }
				else { avanzaCasaHiro_M = false; ultimaActivacionCasaHiro_M = now; }
			}
			else if (!avanzaCasaHiro_M && (now - ultimaActivacionCasaHiro_M) >= 3.0f) {// Espera de 3 segundos
				if (movYC5 > 0.0f) { movYC5 -= 0.3 * movOffsetHeli * deltaTime; rotC5 -= 13.2 * deltaTime; }
			}
		}
		else if (strcmp(ultimaCasillaCasaHiro_M, "C5") == 0) {
			if (movYC5 > 0.0f) { movYC5 -= 0.3 * movOffsetHeli * deltaTime; rotC5 -= 13.2 * deltaTime;}
			else {strcpy_s(ultimaCasillaCasaHiro_M, sizeof(ultimaCasillaCasaHiro_M), ""); avanzaCasaHiro_M = true;}
		}

		//Mega bot
		if (strcmp(casilla_Activacion, "C6") == 0) {
			strcpy_s(ultimaCasillaMegabot_M, sizeof(ultimaCasillaMegabot_M), "C6");
			if (PuedeSubir == true && avanzaMegabot_M) {
				if (movYC6 < 12.25f) { movYC6 += 0.3 * movOffsetHeli * deltaTime; rotC6 += 13.2 * deltaTime; }
				else { avanzaMegabot_M = false; ultimaActivacionMegabot_M = now; }
			}
			else if (!avanzaMegabot_M && (now - ultimaActivacionMegabot_M) >= 3.0f) {// Espera de 3 segundos
				if (movYC6 > 0.0f) { movYC6 -= 0.3 * movOffsetHeli * deltaTime; rotC6 -= 13.2 * deltaTime; }
			}
		}
		else if (strcmp(ultimaCasillaMegabot_M, "C6") == 0) {
			if (movYC6 > 0.0f) { movYC6 -= 0.3 * movOffsetHeli * deltaTime; rotC6 -= 13.2 * deltaTime;}
			else {strcpy_s(ultimaCasillaMegabot_M, sizeof(ultimaCasillaMegabot_M), "");avanzaMegabot_M = true;}
		}

		// --- Casillas de PHINEAS Y FERB ---
		
		//PHINEAS
		if (strcmp(casilla_Activacion, "C7") == 0) {
			strcpy_s(ultimaCasillaPhineas, sizeof(ultimaCasillaPhineas), "C7");
			if (PuedeSubir == true && avanzaPhineas) {
				if (movYC7 < 6.55f) { movYC7 += 0.3 * movOffsetHeli * deltaTime; rotC7 += 16.6 * deltaTime;}
				else {avanzaPhineas = false; ultimaActivacionPhineas = now;}}
			else if (!avanzaPhineas && (now - ultimaActivacionPhineas) >= 3.0f) {// Espera de 3 segundos
				if (movYC7 > 0.0f) { movYC7 -= 0.3 * movOffsetHeli * deltaTime; rotC7 -= 16.6 * deltaTime; }
			}
		}
		else if (strcmp(ultimaCasillaPhineas, "C7") == 0) {
			if (movYC7 > 0.0f) { movYC7 -= 0.3 * movOffsetHeli * deltaTime; rotC7 -= 16.6 * deltaTime;}
			else {strcpy_s(ultimaCasillaPhineas, sizeof(ultimaCasillaPhineas), "");avanzaPhineas = true;}
		}

		//ORNITOCYBORG
		if (strcmp(casilla_Activacion, "C8") == 0) {
			strcpy_s(ultimaCasillaOrnitocyborg, sizeof(ultimaCasillaOrnitocyborg), "C8");
			if (PuedeSubir == true && avanzaOrnitocyborg) {
				if (movYC8 < 6.55f) { movYC8 += 0.3 * movOffsetHeli * deltaTime; rotC8 += 16.6 * deltaTime; }
				else { avanzaOrnitocyborg = false; ultimaActivacionOrnitocyborg = now; }
			}
			else if (!avanzaOrnitocyborg && (now - ultimaActivacionOrnitocyborg) >= 3.0f) {// Espera de 3 segundos
				if (movYC8 > 0.0f) { movYC8 -= 0.3 * movOffsetHeli * deltaTime; rotC8 -= 16.6 * deltaTime; }
			}
		}
		else if (strcmp(ultimaCasillaOrnitocyborg, "C8") == 0) {
			if (movYC8 > 0.0f) { movYC8 -= 0.3 * movOffsetHeli * deltaTime; rotC8 -= 16.6 * deltaTime;}
			else {strcpy_s(ultimaCasillaOrnitocyborg, sizeof(ultimaCasillaOrnitocyborg), ""); avanzaOrnitocyborg = true;}
		}

		//ISABELLA
		if (strcmp(casilla_Activacion, "C9") == 0) {
			strcpy_s(ultimaCasillaIsabella, sizeof(ultimaCasillaIsabella), "C9");
			if (PuedeSubir == true && avanzaIsabella) {
				if (movYC9 < 6.35f) { movYC9 += 0.3 * movOffsetHeli * deltaTime; rotC9 += 16.6 * deltaTime;}
				else {avanzaIsabella = false; ultimaActivacionIsabella = now;}}
			else if (!avanzaIsabella && (now - ultimaActivacionIsabella) >= 3.0f) {// Espera de 3 segundos
				if (movYC9 > 0.0f) { movYC9 -= 0.3 * movOffsetHeli * deltaTime; rotC9 -= 16.6 * deltaTime; }
			}
		}
		else if (strcmp(ultimaCasillaIsabella, "C9") == 0) {
			if (movYC9 > 0.0f) { movYC9 -= 0.3 * movOffsetHeli * deltaTime; rotC9 -= 16.6 * deltaTime;}
			else {strcpy_s(ultimaCasillaIsabella, sizeof(ultimaCasillaIsabella), "");avanzaIsabella = true;}
		}

		//Edificio Doofenshmirtz
		if (strcmp(casilla_Activacion, "S3") == 0) {
			strcpy_s(ultimaCasillaEDoofenshmirtz, sizeof(ultimaCasillaEDoofenshmirtz), "S3");
			if (PuedeSubir == true && avanzaEDoofenshmirtz) {
				if (movYS3 < 16.75f) { movYS3 += 0.3 * movOffsetHeli * deltaTime; rotS3 += 6.4 * deltaTime; }
				else { avanzaEDoofenshmirtz = false; ultimaActivacionEDoofenshmirtz = now; }
			}
			else if (!avanzaEDoofenshmirtz && (now - ultimaActivacionEDoofenshmirtz) >= 3.0f) {// Espera de 3 segundos
				if (movYS3 > 0.0f) { movYS3 -= 0.3 * movOffsetHeli * deltaTime; rotS3 -= 13.2 * deltaTime; }
			}
		}
		else if (strcmp(ultimaCasillaEDoofenshmirtz, "S3") == 0) {
			if (movYS3 > 0.0f) { movYS3 -= 0.3 * movOffsetHeli * deltaTime; rotS3 -= 13.2 * deltaTime; }
			else { strcpy_s(ultimaCasillaEDoofenshmirtz, sizeof(ultimaCasillaEDoofenshmirtz), ""); avanzaEDoofenshmirtz = true; }
		}

		//Peter el Panda
		if (strcmp(casilla_Activacion, "D1") == 0) {
			strcpy_s(ultimaCasillaPeterPanda, sizeof(ultimaCasillaPeterPanda), "D1");
			if (PuedeSubir == true && avanzaPeterPanda) {
				if (movYD1 < 6.35f) { movYD1 += 0.3 * movOffsetHeli * deltaTime; rotD1 += 16.6 * deltaTime; }
				else { avanzaPeterPanda = false; ultimaActivacionPeterPanda = now; }
			}
			else if (!avanzaPeterPanda && (now - ultimaActivacionPeterPanda) >= 3.0f) {// Espera de 3 segundos
				if (movYD1 > 0.0f) { movYD1 -= 0.3 * movOffsetHeli * deltaTime; rotD1 -= 16.6 * deltaTime; }
			}
		}
		else if (strcmp(ultimaCasillaPeterPanda, "D1") == 0) {
			if (movYD1 > 0.0f) { movYD1 -= 0.3 * movOffsetHeli * deltaTime; rotD1 -= 16.6 * deltaTime; }
			else { strcpy_s(ultimaCasillaPeterPanda, sizeof(ultimaCasillaPeterPanda), ""); avanzaPeterPanda = true; }
		}

		// Doofenshmirtz
		if (strcmp(casilla_Activacion, "D2") == 0) {
			strcpy_s(ultimaCasillaDoofenshmirtz, sizeof(ultimaCasillaDoofenshmirtz), "D2");
			if (PuedeSubir == true && avanzaDoofenshmirtz) {
				if (movYD2 < 12.25f) { movYD2 += 0.3 * movOffsetHeli * deltaTime; rotD2 += 13.2 * deltaTime; }
				else { avanzaDoofenshmirtz = false; ultimaActivacionDoofenshmirtz = now; }
			}
			else if (!avanzaDoofenshmirtz && (now - ultimaActivacionDoofenshmirtz) >= 3.0f) {// Espera de 3 segundos
				if (movYD2 > 0.0f) { movYD2 -= 0.3 * movOffsetHeli * deltaTime; rotD2 -= 13.2 * deltaTime; }
			}
		}
		else if (strcmp(ultimaCasillaDoofenshmirtz, "D2") == 0) {
			if (movYD2 > 0.0f) { movYD2 -= 0.3 * movOffsetHeli * deltaTime; rotD2 -= 13.2 * deltaTime; }
			else { strcpy_s(ultimaCasillaDoofenshmirtz, sizeof(ultimaCasillaDoofenshmirtz), ""); avanzaDoofenshmirtz = true; }
		}

		//Terry la tortuga
		if (strcmp(casilla_Activacion, "D3") == 0) {
			strcpy_s(ultimaCasillaTerryTortuga, sizeof(ultimaCasillaTerryTortuga), "D3");
			if (PuedeSubir == true && avanzaTerryTortuga) {
				if (movYD3 < 6.35f) { movYD3 += 0.3 * movOffsetHeli * deltaTime; rotD3 += 16.6 * deltaTime; }
				else { avanzaTerryTortuga = false; ultimaActivacionTerryTortuga = now; }
			}
			else if (!avanzaTerryTortuga && (now - ultimaActivacionTerryTortuga) >= 3.0f) {// Espera de 3 segundos
				if (movYD3 > 0.0f) { movYD3 -= 0.3 * movOffsetHeli * deltaTime; rotD3 -= 16.6 * deltaTime; }
			}
		}
		else if (strcmp(ultimaCasillaTerryTortuga, "D3") == 0) {
			if (movYD3 > 0.0f) { movYD3 -= 0.3 * movOffsetHeli * deltaTime; rotD3 -= 16.6 * deltaTime; }
			else { strcpy_s(ultimaCasillaTerryTortuga, sizeof(ultimaCasillaTerryTortuga), ""); avanzaTerryTortuga = true; }
		}

		//Candace
		if (strcmp(casilla_Activacion, "D4") == 0) {
			strcpy_s(ultimaCasillaCandace, sizeof(ultimaCasillaCandace), "D4");
			if (PuedeSubir == true && avanzaCandace) {
				if (movYD4 < 12.25f) { movYD4 += 0.3 * movOffsetHeli * deltaTime; rotD4 += 13.2 * deltaTime; }
				else { avanzaCandace = false; ultimaActivacionCandace = now; }
			}
			else if (!avanzaCandace && (now - ultimaActivacionCandace) >= 3.0f) {// Espera de 3 segundos
				if (movYD4 > 0.0f) { movYD4 -= 0.3 * movOffsetHeli * deltaTime; rotD4 -= 13.2 * deltaTime; }
			}
		}
		else if (strcmp(ultimaCasillaCandace, "D4") == 0) {
			if (movYD4 > 0.0f) { movYD4 -= 0.3 * movOffsetHeli * deltaTime; rotD4 -= 13.2 * deltaTime; }
			else { strcpy_s(ultimaCasillaCandace, sizeof(ultimaCasillaCandace), ""); avanzaCandace = true; }
		}

		//Doofenshmirtz 2D
		if (strcmp(casilla_Activacion, "D5") == 0) {
			strcpy_s(ultimaCasillaDoofenshmirtz2D, sizeof(ultimaCasillaDoofenshmirtz2D), "D5");
			if (PuedeSubir == true && avanzaDoofenshmirtz2D) {
				if (movYD5 < 12.25f) { movYD5 += 0.3 * movOffsetHeli * deltaTime; rotD5 += 13.2 * deltaTime; }
				else { avanzaDoofenshmirtz2D = false; ultimaActivacionDoofenshmirtz2D = now; }
			}
			else if (!avanzaDoofenshmirtz2D && (now - ultimaActivacionDoofenshmirtz2D) >= 3.0f) {// Espera de 3 segundos
				if (movYD5 > 0.0f) { movYD5 -= 0.3 * movOffsetHeli * deltaTime; rotD5 -= 13.2 * deltaTime; }
			}
		}
		else if (strcmp(ultimaCasillaDoofenshmirtz2D, "D5") == 0) {
			if (movYD5 > 0.0f) { movYD5 -= 0.3 * movOffsetHeli * deltaTime; rotD5 -= 13.2 * deltaTime; }
			else { strcpy_s(ultimaCasillaDoofenshmirtz2D, sizeof(ultimaCasillaDoofenshmirtz2D), ""); avanzaDoofenshmirtz2D = true; }
		}

		// Buford
		if (strcmp(casilla_Activacion, "D6") == 0) {
			strcpy_s(ultimaCasillaBuford, sizeof(ultimaCasillaBuford), "D6");
			if (PuedeSubir == true && avanzaBuford) {
				if (movYD6 < 6.35f) { movYD6 += 0.3 * movOffsetHeli * deltaTime; rotD6 += 16.6 * deltaTime; }
				else { avanzaBuford = false; ultimaActivacionBuford = now; }
			}
			else if (!avanzaBuford && (now - ultimaActivacionBuford) >= 3.0f) {// Espera de 3 segundos
				if (movYD6 > 0.0f) { movYD6 -= 0.3 * movOffsetHeli * deltaTime; rotD6 -= 16.6 * deltaTime; }
			}
		}
		else if (strcmp(ultimaCasillaBuford, "D6") == 0) {
			if (movYD6 > 0.0f) { movYD6 -= 0.3 * movOffsetHeli * deltaTime; rotD6 -= 16.6 * deltaTime; }
			else { strcpy_s(ultimaCasillaBuford, sizeof(ultimaCasillaBuford), ""); avanzaBuford = true; }
		}
		
		// Pinky el Chihuahua
		if (strcmp(casilla_Activacion, "D7") == 0) {
			strcpy_s(ultimaCasillaPinkyChihuahua, sizeof(ultimaCasillaPinkyChihuahua), "D7");
			if (PuedeSubir == true && avanzaPinkyChihuahua) {
				if (movYD7 < 6.35f) { movYD7 += 0.3 * movOffsetHeli * deltaTime; rotD7 += 16.6 * deltaTime; }
				else { avanzaPinkyChihuahua = false; ultimaActivacionPinkyChihuahua = now; }
			}
			else if (!avanzaPinkyChihuahua && (now - ultimaActivacionPinkyChihuahua) >= 3.0f) {// Espera de 3 segundos
				if (movYD7 > 0.0f) { movYD7 -= 0.3 * movOffsetHeli * deltaTime; rotD7 -= 16.6 * deltaTime; }
			}
		}
		else if (strcmp(ultimaCasillaPinkyChihuahua, "D7") == 0) {
			if (movYD7 > 0.0f) { movYD7 -= 0.3 * movOffsetHeli * deltaTime; rotD7 -= 16.6 * deltaTime; }
			else { strcpy_s(ultimaCasillaPinkyChihuahua, sizeof(ultimaCasillaPinkyChihuahua), ""); avanzaPinkyChihuahua = true; }
		}
		
		// Carl
		if (strcmp(casilla_Activacion, "D8") == 0) {
			strcpy_s(ultimaCasillaCarl, sizeof(ultimaCasillaCarl), "D8");
			if (PuedeSubir == true && avanzaCarl) {
				if (movYD8 < 12.25f) { movYD8 += 0.3 * movOffsetHeli * deltaTime; rotD8 += 13.2 * deltaTime; }
				else { avanzaCarl = false; ultimaActivacionCarl = now; }
			}
			else if (!avanzaCarl && (now - ultimaActivacionCarl) >= 3.0f) {// Espera de 3 segundos
				if (movYD8 > 0.0f) { movYD8 -= 0.3 * movOffsetHeli * deltaTime; rotD8 -= 13.2 * deltaTime; }
			}
		}
		else if (strcmp(ultimaCasillaCarl, "D8") == 0) {
			if (movYD8 > 0.0f) { movYD8 -= 0.3 * movOffsetHeli * deltaTime; rotD8 -= 13.2 * deltaTime; }
			else { strcpy_s(ultimaCasillaCarl, sizeof(ultimaCasillaCarl), ""); avanzaCarl = true; }
		}

		// Ferb
		if (strcmp(casilla_Activacion, "D9") == 0) {
			strcpy_s(ultimaCasillaFerb, sizeof(ultimaCasillaFerb), "D9");
			if (PuedeSubir == true && avanzaFerb) {
				if (movYD9 < 12.25f) { movYD9 += 0.3 * movOffsetHeli * deltaTime; rotD9 += 13.2 * deltaTime; }
				else { avanzaFerb = false; ultimaActivacionFerb = now; }
			}
			else if (!avanzaFerb && (now - ultimaActivacionFerb) >= 3.0f) {// Espera de 3 segundos
				if (movYD9 > 0.0f) { movYD9 -= 0.3 * movOffsetHeli * deltaTime; rotD9 -= 13.2 * deltaTime; }
			}
		}
		else if (strcmp(ultimaCasillaFerb, "D9") == 0) {
			if (movYD9 > 0.0f) { movYD9 -= 0.3 * movOffsetHeli * deltaTime; rotD9 -= 13.2 * deltaTime; }
			else { strcpy_s(ultimaCasillaFerb, sizeof(ultimaCasillaFerb), ""); avanzaFerb = true; }
		}

		

		glfwPollEvents();
		camera.keyControl(mainWindow.getsKeys(), deltaTime);
		camera.mouseControl(mainWindow.getXChange(), mainWindow.getYChange());

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		if (FASE_01) {
			LightDAY.SetDirection(xDir, -0.25f, 0.0f/*zDir*/);
			shaderList[0].SetDirectionalLight(&LightDAY);
			skyboxDia.DrawSkybox(camera.calculateViewMatrix(), projection);
		}
		else {
			LightNIGHT.SetDirection(xDir, -0.25f, 0.0f/*zDir*/);
			shaderList[0].SetDirectionalLight(&LightNIGHT);
			skyboxNoche.DrawSkybox(camera.calculateViewMatrix(), projection);
		}

		shaderList[0].UseShader();
		uniformModel = shaderList[0].GetModelLocation();
		uniformProjection = shaderList[0].GetProjectionLocation();
		uniformView = shaderList[0].GetViewLocation();
		uniformEyePosition = shaderList[0].GetEyePositionLocation();
		uniformColor = shaderList[0].getColorLocation();
		uniformSpecularIntensity = shaderList[0].GetSpecularIntensityLocation();
		uniformShininess = shaderList[0].GetShininessLocation();

		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
		glUniform3f(uniformEyePosition, camera.getCameraPosition().x, camera.getCameraPosition().y, camera.getCameraPosition().z);

		glm::vec3 lowerLight = camera.getCameraPosition();
		lowerLight.y -= 0.3f;

		shaderList[0].SetSpotLights(spotLights, spotLightCount);

		if (FASE_01) { shaderList[0].SetDirectionalLight(&LightDAY); }
		else { shaderList[0].SetDirectionalLight(&LightNIGHT); }

		unsigned int activeLightCount = 0;
		PointLight activeLights[2];

		glm::mat4 model(1.0);
		glm::mat4 modelaux(1.0);
		glm::mat4 modelaux2(1.0);
		glm::mat4 modelLamp1(1.0);
		glm::mat4 modelLamp2(1.0);
		glm::mat4 modelLamp3(1.0);
		glm::mat4 modelLamp4(1.0);
		glm::mat4 modelauxBaymax(1.0);
		glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(30.0f, 1.0f, 30.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		pisoTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[2]->RenderMesh();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-32.0f, movDado + 25.0f, 27.0f));
		model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
		if (mainWindow.gettiro() == true) {
			model = glm::rotate(model, glm::radians(RotacionZ8), glm::vec3(0.0f, 0.0f, 1.0f));
			model = glm::rotate(model, glm::radians(RotacionX8), glm::vec3(1.0f, 0.0f, 0.0f));
		}
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Dado8.UseTexture(); meshList[7]->RenderMesh();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-22.0f, movDado + 24.6f, 27.0f));
		model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
		if (mainWindow.gettiro() == true) {
			model = glm::rotate(model, glm::radians(RotacionZ4), glm::vec3(0.0f, 0.0f, 1.0f));
			model = glm::rotate(model, glm::radians(RotacionX4), glm::vec3(1.0f, 0.0f, 0.0f));
		}
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Dado4_2.UseTexture(); meshList[6]->RenderMesh();

		
		// --- Tablero ---
		
		//Start - Esquina 1
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -1.0f, 0.0f));
		modelLamp1 = model; modelLamp2 = model; modelLamp3 = model; modelLamp4 = model;
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		if (strcmp(casilla_Activacion, "S4") == 0 && PuedeSubir) { Casilla1_D.UseTexture(); }
		else if(FASE_01) { Casilla1.UseTexture(); }
		else if(!FASE_01) { Casilla1_N.UseTexture(); }
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[4]->RenderMesh();

		//A1
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 1.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		if (strcmp(casilla_Activacion, "A1") == 0 && PuedeSubir) {A1_D.UseTexture();}
		else if (FASE_01) { A1.UseTexture(); }
		else if (!FASE_01) { A1_N.UseTexture(); }
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[5]->RenderMesh();

		//A2
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		if (strcmp(casilla_Activacion, "A2") == 0 && PuedeSubir) { A2_D.UseTexture(); }
		else if (FASE_01) { A2.UseTexture(); }
		else if (!FASE_01) { A2_N.UseTexture(); }
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[5]->RenderMesh();

		//A3
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		if (strcmp(casilla_Activacion, "A3") == 0 && PuedeSubir) { A3_D.UseTexture(); }
		else if (FASE_01) { A3.UseTexture(); }
		else if (!FASE_01) { A3_N.UseTexture(); }
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[5]->RenderMesh();

		//A4
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		if (strcmp(casilla_Activacion, "A4") == 0 && PuedeSubir) { A4_D.UseTexture(); }
		else if (FASE_01) { A4.UseTexture(); }
		else if (!FASE_01) { A4_N.UseTexture(); }
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[5]->RenderMesh();

		//A5
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		if (strcmp(casilla_Activacion, "A5") == 0 && PuedeSubir) { A5_D.UseTexture(); }
		else if (FASE_01) { A5.UseTexture(); }
		else if (!FASE_01) { A5_N.UseTexture(); }
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[5]->RenderMesh();

		//A6
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		if (strcmp(casilla_Activacion, "A6") == 0 && PuedeSubir) { A6_D.UseTexture(); }
		else if (FASE_01) { A6.UseTexture(); }
		else if (!FASE_01) { A6_N.UseTexture(); }
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[5]->RenderMesh();

		//A7
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		if (strcmp(casilla_Activacion, "A7") == 0 && PuedeSubir) { A7_D.UseTexture(); }
		else if (FASE_01) { A7.UseTexture(); }
		else if (!FASE_01) { A7_N.UseTexture(); }
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[5]->RenderMesh();

		//A8
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		if (strcmp(casilla_Activacion, "A8") == 0 && PuedeSubir) { A8_D.UseTexture(); }
		else if (FASE_01) { A8.UseTexture(); }
		else if (!FASE_01) { A8_N.UseTexture(); }
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[5]->RenderMesh();

		//A9
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		if (strcmp(casilla_Activacion, "A9") == 0 && PuedeSubir) { A9_D.UseTexture(); }
		else if (FASE_01) { A9.UseTexture(); }
		else if (!FASE_01) { A9_N.UseTexture(); }
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[5]->RenderMesh();

		//Esquina 2
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 1.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		if (strcmp(casilla_Activacion, "S1") == 0 && PuedeSubir) { Csl2_D.UseTexture(); }
		else if (FASE_01) { Csl2.UseTexture(); }
		else if (!FASE_01) { Csl2_N.UseTexture(); }
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[4]->RenderMesh();

		//B1
		model = glm::translate(model, glm::vec3(-1.5f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		if (strcmp(casilla_Activacion, "B1") == 0 && PuedeSubir) { B1_D.UseTexture(); }
		else if (FASE_01) { B1.UseTexture(); }
		else if (!FASE_01) { B1_N.UseTexture(); }
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[5]->RenderMesh();

		//B2
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		if (strcmp(casilla_Activacion, "B2") == 0 && PuedeSubir) { B2_D.UseTexture(); }
		else if (FASE_01) { B2.UseTexture(); }
		else if (!FASE_01) { B2_N.UseTexture(); }
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[5]->RenderMesh();

		//B3
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		if (strcmp(casilla_Activacion, "B3") == 0 && PuedeSubir) { B3_D.UseTexture(); }
		else if (FASE_01) { B3.UseTexture(); }
		else if (!FASE_01) { B3_N.UseTexture(); }
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[5]->RenderMesh();

		//B4
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		if (strcmp(casilla_Activacion, "B4") == 0 && PuedeSubir) { B4_D.UseTexture(); }
		else if (FASE_01) { B4.UseTexture(); }
		else if (!FASE_01) { B4_N.UseTexture(); }
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[5]->RenderMesh();

		//B5
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		if (strcmp(casilla_Activacion, "B5") == 0 && PuedeSubir) { B5_D.UseTexture(); }
		else if (FASE_01) { B5.UseTexture(); }
		else if (!FASE_01) { B5_N.UseTexture(); }
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[5]->RenderMesh();

		//B6
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		if (strcmp(casilla_Activacion, "B6") == 0 && PuedeSubir) { B6_D.UseTexture(); }
		else if (FASE_01) { B6.UseTexture(); }
		else if (!FASE_01) { B6_N.UseTexture(); }
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[5]->RenderMesh();

		//B7
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		if (strcmp(casilla_Activacion, "B7") == 0 && PuedeSubir) { B7_D.UseTexture(); }
		else if (FASE_01) { B7.UseTexture(); }
		else if (!FASE_01) { B7_N.UseTexture(); }
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[5]->RenderMesh();

		//B8
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		if (strcmp(casilla_Activacion, "B8") == 0 && PuedeSubir) { B8_D.UseTexture(); }
		else if (FASE_01) { B8.UseTexture(); }
		else if (!FASE_01) { B8_N.UseTexture(); }
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[5]->RenderMesh();

		//B9
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		if (strcmp(casilla_Activacion, "B9") == 0 && PuedeSubir) { B9_D.UseTexture(); }
		else if (FASE_01) { B9.UseTexture(); }
		else if (!FASE_01) { B9_N.UseTexture(); }
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[5]->RenderMesh();

		//Esquina 3
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -1.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		if (strcmp(casilla_Activacion, "S2") == 0 && PuedeSubir) { Csl3_D.UseTexture(); }
		else if (FASE_01) { Csl3.UseTexture(); }
		else if (!FASE_01) { Csl3_N.UseTexture(); }
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[4]->RenderMesh();

		//C1
		model = glm::translate(model, glm::vec3(1.5f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		if (strcmp(casilla_Activacion, "C1") == 0 && PuedeSubir) { C1_D.UseTexture(); }
		else if (FASE_01) { C1.UseTexture(); }
		else if (!FASE_01) { C1_N.UseTexture(); }
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[5]->RenderMesh();

		//C2
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		if (strcmp(casilla_Activacion, "C2") == 0 && PuedeSubir) { C2_D.UseTexture(); }
		else if (FASE_01) { C2.UseTexture(); }
		else if (!FASE_01) { C2_N.UseTexture(); }
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[5]->RenderMesh();

		//C3
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		if (strcmp(casilla_Activacion, "C3") == 0 && PuedeSubir) { C3_D.UseTexture(); }
		else if (FASE_01) { C3.UseTexture(); }
		else if (!FASE_01) { C3_N.UseTexture(); }
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[5]->RenderMesh();

		//C4
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		if (strcmp(casilla_Activacion, "C4") == 0 && PuedeSubir) { C4_D.UseTexture(); }
		else if (FASE_01) { C4.UseTexture(); }
		else if (!FASE_01) { C4_N.UseTexture(); }
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[5]->RenderMesh();

		//C5
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		if (strcmp(casilla_Activacion, "C5") == 0 && PuedeSubir) { C5_D.UseTexture(); }
		else if (FASE_01) { C5.UseTexture(); }
		else if (!FASE_01) { C5_N.UseTexture(); }
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[5]->RenderMesh();

		//C6
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		if (strcmp(casilla_Activacion, "C6") == 0 && PuedeSubir) { C6_D.UseTexture(); }
		else if (FASE_01) { C6.UseTexture(); }
		else if (!FASE_01) { C6_N.UseTexture(); }
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[5]->RenderMesh();

		//C7
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		if (strcmp(casilla_Activacion, "C7") == 0 && PuedeSubir) { C7_D.UseTexture(); }
		else if (FASE_01) { C7.UseTexture(); }
		else if (!FASE_01) { C7_N.UseTexture(); }
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[5]->RenderMesh();

		//C8
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		if (strcmp(casilla_Activacion, "C8") == 0 && PuedeSubir) { C8_D.UseTexture(); }
		else if (FASE_01) { C8.UseTexture(); }
		else if (!FASE_01) { C8_N.UseTexture(); }
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[5]->RenderMesh();

		//C9
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		if (strcmp(casilla_Activacion, "C9") == 0 && PuedeSubir) { C9_D.UseTexture(); }
		else if (FASE_01) { C9.UseTexture(); }
		else if (!FASE_01) { C9_N.UseTexture(); }
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[5]->RenderMesh();

		//Esquina 4
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 1.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		if (strcmp(casilla_Activacion, "S3") == 0 && PuedeSubir) { Casilla4_D.UseTexture(); }
		else if (FASE_01) { Casilla4.UseTexture(); }
		else if (!FASE_01) { Casilla4_N.UseTexture(); }
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[4]->RenderMesh();

		//D1
		model = glm::translate(model, glm::vec3(-1.5f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		if (strcmp(casilla_Activacion, "D1") == 0 && PuedeSubir) { D1_D.UseTexture(); }
		else if (FASE_01) { D1.UseTexture(); }
		else if (!FASE_01) { D1_N.UseTexture(); }
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[5]->RenderMesh();

		//D2
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		if (strcmp(casilla_Activacion, "D2") == 0 && PuedeSubir) { D2_D.UseTexture(); }
		else if (FASE_01) { D2.UseTexture(); }
		else if (!FASE_01) { D2_N.UseTexture(); }
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[5]->RenderMesh();

		//D3
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		if (strcmp(casilla_Activacion, "D3") == 0 && PuedeSubir) { D3_D.UseTexture(); }
		else if (FASE_01) { D3.UseTexture(); }
		else if (!FASE_01) { D3_N.UseTexture(); }
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[5]->RenderMesh();

		//D4
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		if (strcmp(casilla_Activacion, "D4") == 0 && PuedeSubir) { D4_D.UseTexture(); }
		else if (FASE_01) { D4.UseTexture(); }
		else if (!FASE_01) { D4_N.UseTexture(); }
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[5]->RenderMesh();

		//D5
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		if (strcmp(casilla_Activacion, "D5") == 0 && PuedeSubir) { D5_D.UseTexture(); }
		else if (FASE_01) { D5.UseTexture(); }
		else if (!FASE_01) { D5_N.UseTexture(); }
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[5]->RenderMesh();

		//D6
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		if (strcmp(casilla_Activacion, "D6") == 0 && PuedeSubir) { D6_D.UseTexture(); }
		else if (FASE_01) { D6.UseTexture(); }
		else if (!FASE_01) { D6_N.UseTexture(); }
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[5]->RenderMesh();

		//D7
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		if (strcmp(casilla_Activacion, "D7") == 0 && PuedeSubir) { D7_D.UseTexture(); }
		else if (FASE_01) { D7.UseTexture(); }
		else if (!FASE_01) { D7_N.UseTexture(); }
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[5]->RenderMesh();

		//D8
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		if (strcmp(casilla_Activacion, "D8") == 0 && PuedeSubir) { D8_D.UseTexture(); }
		else if (FASE_01) { D8.UseTexture(); }
		else if (!FASE_01) { D8_N.UseTexture(); }
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[5]->RenderMesh();

		//D9
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		if (strcmp(casilla_Activacion, "D9") == 0 && PuedeSubir) { D9_D.UseTexture(); }
		else if (FASE_01) { D9.UseTexture(); }
		else if (!FASE_01) { D9_N.UseTexture(); }
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[5]->RenderMesh();

		//Centro
		model = glm::translate(model, glm::vec3(-5.5f, 0.0f, -4.0f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(4.5f, 0.25f, 4.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		CentroTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[8]->RenderMesh();

		// --- MODELOS PRINCIPALES ---

		model = glm::mat4(1.0f);// Personaje Principal en el tablero
		model = glm::translate(model, glm::vec3(movX, 0.0f, movZ));
		model = glm::rotate(model, glm::radians(giro), glm::vec3(0.0f, 1.0f, 0.0f));
		if (PerPrincipal1 == true) { 
			model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
			modelaux2 = model;
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model)); 
			Perry.RenderModel(); }
		else if (PerPrincipal2 == true) { 
			model = glm::scale(model, glm::vec3(0.6f, 0.6f, 0.6f));
			modelaux2 = model;
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model)); 
			Bombon.RenderModel(); }
		else if (PerPrincipal3 == true) { 
			model = glm::mat4(1.0); // Baymax Blanco Con Jerarquía
			model = glm::translate(model, glm::vec3(movX, 0.0f, movZ));
			model = glm::rotate(model, glm::radians(giro), glm::vec3(0.0f, 1.0f, 0.0f));
			model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
			modelaux2 = model;
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			BaymaxBlanco_M.RenderModel();

			model = modelaux2;
			model = glm::translate(model, glm::vec3(-12.0f, 60.0f, 0.0f));
			modelaux2 = model;
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			BrazoDerechoBaymax.RenderModel();

			model = modelaux2;
			model = glm::translate(model, glm::vec3(-13.0f, -30.0f, 0.0f));
			modelaux2 = model;
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			ManoBaymax.RenderModel();

			model = modelaux2;
			model = glm::translate(model, glm::vec3(-5.0f, -5.0f, 0.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			DedoMedioBaymax.RenderModel();

			model = modelaux2;
			model = glm::translate(model, glm::vec3(-5.0f, -4.0f, 2.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			DedoIzquierdoBaymax.RenderModel();

			model = modelaux2;
			model = glm::translate(model, glm::vec3(-5.0f, -4.0f, -2.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			DedoDerechoBaymax.RenderModel();

			model = modelaux2;
			model = glm::translate(model, glm::vec3(2.0f, -4.0f, 2.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			DedoGordoBaymax.RenderModel();
		}

		if (!FASE_01) {
			model = modelaux2;//Luz de seguimiento
			if (PerPrincipal3 == true) {
				model = glm::translate(model, glm::vec3(-20.0f, 70.0f, -20.0f));
				model = glm::rotate(model, glm::radians(giro), glm::vec3(0.0f, 1.0f, 0.0f));
				model = glm::scale(model, glm::vec3(0.8f, 0.8f, 0.8f));}
			else {
				model = glm::translate(model, glm::vec3(-4.0f, 11.0f, -4.0f));
				model = glm::rotate(model, glm::radians(giro), glm::vec3(0.0f, 1.0f, 0.0f));
				model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));}
			modelaux2 = model;
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			esf.RenderModel();
			glm::vec3 lghtPrinc = glm::vec3(modelaux2[3]);
			pointLights[1].SetPosition(lghtPrinc.x, lghtPrinc.y, lghtPrinc.z);
			activeLights[activeLightCount++] = pointLights[1];
		}

		model = modelaux;// Personaje Secundario1 afuera del tablero
		model = glm::translate(model, glm::vec3(8.0f, -0.8f, 0.0f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));

		if (PerPrincipal1 == true) {
			model = glm::scale(model, glm::vec3(0.6f, 0.6f, 0.6f));
			modelaux2 = model;
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			Bombon.RenderModel();
		}
		else if (PerPrincipal2 == true) {
			/*model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
			modelaux2 = model;
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			BaymaxBlanco_M.RenderModel();*/

			model = glm::mat4(1.0);// Baymax Animado
			model = glm::translate(model, glm::vec3(8.0f, -0.8f, 0.0f));
			model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
			model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
			modelauxBaymax = model;
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			BaymaxBlanco_M.RenderModel();

			model = modelauxBaymax;
			model = glm::translate(model, glm::vec3(-12.0f, 60.0f, 0.0f));
			model = glm::rotate(model, giroBrazo * toRadians, glm::vec3(-1.0f, 0.0f, 0.0f));
			modelauxBaymax = model;
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			BrazoDerechoBaymax.RenderModel();

			model = modelauxBaymax;
			model = glm::translate(model, glm::vec3(-13.0f, -30.0f, 0.0f));
			model = glm::rotate(model, giraMano * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
			modelauxBaymax = model;
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			ManoBaymax.RenderModel();

			model = modelauxBaymax;
			model = glm::translate(model, glm::vec3(-5.0f, -4.0f, 0.0f));
			model = glm::rotate(model, sin(giraDedos) * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			DedoMedioBaymax.RenderModel();

			model = modelauxBaymax;
			model = glm::translate(model, glm::vec3(-5.0f, -4.0f, 2.0f));
			model = glm::rotate(model, sin(giraDedos) * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			DedoIzquierdoBaymax.RenderModel();

			model = modelauxBaymax;
			model = glm::translate(model, glm::vec3(-5.0f, -4.0f, -2.0f));
			model = glm::rotate(model, sin(giraDedos) * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			DedoDerechoBaymax.RenderModel();

			model = modelauxBaymax;
			model = glm::translate(model, glm::vec3(2.0f, -4.0f, 2.0f));
			model = glm::rotate(model, sin(giraDedos) * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			DedoGordoBaymax.RenderModel();
		}
		else if (PerPrincipal3 == true) {
			model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
			modelaux2 = model;
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			Perry.RenderModel();
		}

		model = glm::mat4(1.0);// Personaje Secundario2 afuera del tablero
		model = glm::translate(model, glm::vec3(0.0f, -0.8f, -8.0f));
		if (PerPrincipal1 == true) {
			model = glm::mat4(1.0);// Baymax Animado
			model = glm::translate(model, glm::vec3(0.0f, -0.8f, -8.0f));
			model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
			modelauxBaymax = model;
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			BaymaxBlanco_M.RenderModel();

			model = modelauxBaymax;
			model = glm::translate(model, glm::vec3(-12.0f, 60.0f, 0.0f));
			model = glm::rotate(model, giroBrazo * toRadians, glm::vec3(-1.0f, 0.0f, 0.0f));
			modelauxBaymax = model;
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			BrazoDerechoBaymax.RenderModel();

			model = modelauxBaymax;
			model = glm::translate(model, glm::vec3(-13.0f, -30.0f, 0.0f));
			model = glm::rotate(model, giraMano * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
			modelauxBaymax = model;
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			ManoBaymax.RenderModel();

			model = modelauxBaymax;
			model = glm::translate(model, glm::vec3(-5.0f, -4.0f, 0.0f));
			model = glm::rotate(model, sin(giraDedos) * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			DedoMedioBaymax.RenderModel();

			model = modelauxBaymax;
			model = glm::translate(model, glm::vec3(-5.0f, -4.0f, 2.0f));
			model = glm::rotate(model, sin(giraDedos) * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			DedoIzquierdoBaymax.RenderModel();

			model = modelauxBaymax;
			model = glm::translate(model, glm::vec3(-5.0f, -4.0f, -2.0f));
			model = glm::rotate(model, sin(giraDedos) * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			DedoDerechoBaymax.RenderModel();

			model = modelauxBaymax;
			model = glm::translate(model, glm::vec3(2.0f, -4.0f, 2.0f));
			model = glm::rotate(model, sin(giraDedos) * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			DedoGordoBaymax.RenderModel();
		}
		else if (PerPrincipal2 == true) {
			model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
			modelaux2 = model;
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			Perry.RenderModel();
		}
		else if (PerPrincipal3 == true) {
			model = glm::scale(model, glm::vec3(0.6f, 0.6f, 0.6f));
			modelaux2 = model;
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			Bombon.RenderModel();
		}

		//Lampara 01
		model = modelLamp1;
		model = glm::translate(model, glm::vec3(8.0f, 0.2f, -8.0f));
		model = glm::scale(model, glm::vec3(0.15f, 0.15f, 0.15f));
		modelLamp1 = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Lampara.RenderModel();
		glm::vec3 lamparaPos1 = glm::vec3(modelLamp1[3]);
		pointLights[0].SetPosition(lamparaPos1.x, lamparaPos1.y + 8.2f, lamparaPos1.z);
		if (!FASE_01) { activeLights[activeLightCount++] = pointLights[0]; }

		//Lampara 02
		model = modelLamp2;
		model = glm::translate(model, glm::vec3(6.0f, 0.2f, 62.0f));
		model = glm::rotate(model, -135 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.25f, 0.25f, 0.25f));
		modelLamp2 = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Lampara2.RenderModel();
		glm::vec3 lamparaPos2 = glm::vec3(modelLamp2[3]);
		glm::vec3 lightPos = glm::vec3(lamparaPos2.x - 3.2f, lamparaPos2.y + 11.6f, lamparaPos2.z - 3.2f);
		if (!FASE_01) { spotLights[0].SetFlash(lightPos, glm::vec3(0.0f, -1.0f, 0.0f)); }	// Noche - Luz encendida
		else { spotLights[0].SetFlash(lightPos, glm::vec3(0.0f)); }						// Día - Luz apagada

		//Lampara 03
		model = modelLamp3;
		model = glm::translate(model, glm::vec3(-62.0f, 0.2f, 62.0f));
		model = glm::rotate(model, -225 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.25f, 0.25f, 0.25f));
		modelLamp3 = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Lampara2.RenderModel();
		glm::vec3 lamparaPos3 = glm::vec3(modelLamp3[3]);
		glm::vec3 lightPos2 = glm::vec3(lamparaPos3.x + 3.2f, lamparaPos3.y + 11.6f, lamparaPos3.z - 3.2f);
		if (!FASE_01) { spotLights[1].SetFlash(lightPos2, glm::vec3(0.0f, -1.0f, 0.0f)); }	// Noche - Luz encendida
		else { spotLights[1].SetFlash(lightPos2, glm::vec3(0.0f)); }						// Día - Luz apagada

		//Lampara 04
		model = modelLamp4;
		model = glm::translate(model, glm::vec3(-62.0f, 0.2f, -6.0f));
		model = glm::rotate(model, 45 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.25f, 0.25f, 0.25f));
		modelLamp4 = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Lampara2.RenderModel();
		glm::vec3 lamparaPos4 = glm::vec3(modelLamp4[3]);
		glm::vec3 lightPos3 = glm::vec3(lamparaPos4.x + 3.2f, lamparaPos4.y + 11.6f, lamparaPos4.z + 3.2f);
		if (!FASE_01) { spotLights[2].SetFlash(lightPos3, glm::vec3(0.0f, -1.0f, 0.0f)); }	// Noche - Luz encendida
		else { spotLights[2].SetFlash(lightPos3, glm::vec3(0.0f)); }						// Día - Luz apagada

		shaderList[0].SetPointLights(activeLights, activeLightCount);

		// ---  MODELOS CHICAS SUPER PODEROSAS  ---
		
		model = modelaux;// Gato
		model = glm::translate(model, glm::vec3(8.0f, movYA1 -7.0f, 7.0f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, rotA1 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Gato.RenderModel();

		model = modelaux;// Octi
		model = glm::translate(model, glm::vec3(8.0f, movYA2 - 7.0f, 12.5f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, rotA2 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Octi.RenderModel();

		model = modelaux;// Arbol
		model = glm::translate(model, glm::vec3(8.0f, movYA3 - 7.5f, 17.5f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, rotA3 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.35f, 0.35f, 0.35f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Arbol.RenderModel();

		model = modelaux;// Burbuja
		model = glm::translate(model, glm::vec3(8.0f, movYA4 - 7.0f, 22.5f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, rotA4 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Burbuja.RenderModel();

		model = modelaux;// Bellota
		model = glm::translate(model, glm::vec3(8.0f, movYA5 - 7.0f, 27.5f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, rotA5 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Bellota.RenderModel();

		model = modelaux;// Mojo Jojo
		model = glm::translate(model, glm::vec3(8.0f, movYA6 - 7.0f, 32.5f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, rotA6 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.6f, 0.6f, 0.6f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Mojo.RenderModel();

		model = modelaux;// Peludito
		model = glm::translate(model, glm::vec3(8.0f, movYA7 - 7.0f, 37.5f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, rotA7 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Peludito.RenderModel();

		model = modelaux;// Princesa 
		model = glm::translate(model, glm::vec3(8.0f, movYA8 - 7.0f, 42.5f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, rotA8 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Princesa.RenderModel();

		model = modelaux;// Profesor
		model = glm::translate(model, glm::vec3(8.0f, movYA9 - 7.0f, 47.5f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, rotA9 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Profesor.RenderModel();

		model = modelaux;// Sedusa
		model = glm::translate(model, glm::vec3(8.0f, movYS1 - 8.0f, 52.5f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, rotS1 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Sedusa.RenderModel();

		model = modelaux;// Casa
		model = glm::translate(model, glm::vec3(-7.5f, movYB1 - 7.0f, 65.0f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, rotB1 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Casa.RenderModel();

		model = modelaux;// Edificio
		model = glm::translate(model, glm::vec3(-12.8f, movYB2 - 17.5f, 65.0f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, rotB2 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.33f, 0.33f, 0.33f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Edificio.RenderModel();

		model = modelaux;// Alcaldia
		model = glm::translate(model, glm::vec3(-18.0f, movYB3 - 7.0f, 65.0f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, rotB3 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Alcaldia.RenderModel();

		//Edificio1
		model = modelaux;
		model = glm::translate(model, glm::vec3(92.0f, -0.8f, 30.0f));
		//model = glm::translate(model, glm::vec3(42.0f, -0.8f, -20.0f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Edificio1.RenderModel();

		//Edificio2
		model = modelaux;
		model = glm::translate(model, glm::vec3(85.0f, -0.8f, -20.0f));
		//model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Edificio2.RenderModel();

		//Alcaldia
		model = modelaux;
		model = glm::translate(model, glm::vec3(52.0f, -0.8f, 30.0f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Alcaldia.RenderModel();

		//Edificio3
		model = modelaux;
		model = glm::translate(model, glm::vec3(42.0f, -0.8f, -20.0f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.7f, 0.7f, 0.7f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Edificio3.RenderModel();

		//Edificio4
		model = modelaux;
		model = glm::translate(model, glm::vec3(82.0f, -0.8f, 85.0f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Edificio4.RenderModel();

		//Edificio5
		model = modelaux;
		model = glm::translate(model, glm::vec3(40.0f, -0.8f, 85.0f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Edificio5.RenderModel();

		//Edificio6
		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f, -0.8f, 85.0f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Edificio6.RenderModel();


		// --- MODELOS BIG HERO 6 ---
		
		model = glm::mat4(1.0);// Hiro Hamada
		model = glm::translate(model, glm::vec3(-23.0f, movYB4 - 13.2f, 65.0f));
		model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, rotB4 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		HiroHamada_M.RenderModel();
		
		model = glm::mat4(1.0);// Planta1
		model = glm::translate(model, glm::vec3(-28.0f, movYB5 - 13.2f, 65.0f));
		model = glm::scale(model, glm::vec3(0.6f, 0.6f, 0.6f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, rotB5 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Planta1_M.RenderModel();
		
		model = glm::mat4(1.0);// Auto Chico
		model = glm::translate(model, glm::vec3(-33.0f, movYB6 - 9.8f, 68.0f));
		model = glm::scale(model, glm::vec3(3.5f, 3.5f, 3.5f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, rotB6 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		AutoChico_M.RenderModel();
		
		model = glm::mat4(1.0);// Gogo Tomago
		model = glm::translate(model, glm::vec3(-38.0f, movYB7 - 13.0f, 65.0f));
		model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, rotB7 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		GogoTomago_M.RenderModel();
		
		model = glm::mat4(1.0);// Motocicleta
		model = glm::translate(model, glm::vec3(-43.0f, movYB8 - 13.3f, 68.0f));
		model = glm::scale(model, glm::vec3(5.3f, 5.3f, 5.3f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, rotB8 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Motocicleta_M.RenderModel();
		
		model = glm::mat4(1.0);// GoldenGate
		model = glm::translate(model, glm::vec3(-48.0f, movYB9 - 10.2f, 65.0f));
		model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, rotB9 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		GoldenGate_M.RenderModel();

		model = glm::mat4(1.0); // Planta2
		model = glm::translate(model, glm::vec3(-53.0f, movYS2 - 13.2f, 65.0f));
		model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.05f));
		model = glm::rotate(model, rotS2 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Planta2_M.RenderModel();

		model = glm::mat4(1.0);// Baymax Super Armadura
		model = glm::translate(model, glm::vec3(-65.0f, movYC1 - 17.5f, 47.5f));
		model = glm::scale(model, glm::vec3(1.4f, 1.4f, 1.4f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, rotC1 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		BaymaxSuperArmadura_M.RenderModel();

		model = glm::mat4(1.0);// Auto Grande		
		model = glm::translate(model, glm::vec3(-67.0f, movYC2 - 13.2f, 42.5f));
		model = glm::scale(model, glm::vec3(3.5f, 3.5f, 3.5f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, rotC2 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		AutoGrande_M.RenderModel();

		model = glm::mat4(1.0);// Fred	
		model = glm::translate(model, glm::vec3(-65.0f, movYC3 - 13.2f, 37.5f));
		model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, rotC3 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Fred_M.RenderModel();

		model = glm::mat4(1.0);// Planta3
		model = glm::translate(model, glm::vec3(-65.0f, movYC4 - 13.0f, 32.5f));
		model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, rotC4 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Planta3_M.RenderModel();

		model = glm::mat4(1.0);// Casa Hiro
		model = glm::translate(model, glm::vec3(-69.0f, movYC5 - 13.0f, 27.5f));
		model = glm::scale(model, glm::vec3(0.8f, 0.8f, 0.8f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, rotC5 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		CasaHiro_M.RenderModel();

		model = glm::mat4(1.0);//Mega Bot
		model = glm::translate(model, glm::vec3(-65.0f, movYC6 - 13.0f, 22.5f));
		model = glm::scale(model, glm::vec3(5.5f, 5.5f, 5.5f));
		model = glm::rotate(model, 270 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, rotC6 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Megabot_M.RenderModel();

		// ---  BIG HERO SIX ------

		//Edificio15
		model = modelaux;
		model = glm::translate(model, glm::vec3(-35.0f, -0.8f, 80.0f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.8f, 0.8f, 0.8f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Edificio15.RenderModel();

		//dificio16
		model = modelaux;
		model = glm::translate(model, glm::vec3(-57.0f, -0.8f, 80.0f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Edificio16.RenderModel();

		//Torre
		model = modelaux;
		model = glm::translate(model, glm::vec3(-87.0f, -0.8f, 30.0f));
		//model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.7f, 0.7f, 0.7f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Torre.RenderModel();


		//Edificio18
		model = modelaux;
		model = glm::translate(model, glm::vec3(-87.0f, -0.8f, 55.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Edificio18.RenderModel();

		//Puente
		model = modelaux;
		model = glm::translate(model, glm::vec3(-100.0f, -0.8f, 60.0f));
		//model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.8f, 0.8f, 0.8f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Puente.RenderModel();

		//Edificio17
		model = modelaux;
		model = glm::translate(model, glm::vec3(-80.0f, -0.8f, 80.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Edificio17.RenderModel();

		// ---  MODELOS PHINEAS Y FERB  ------

		model = modelaux;// Phineas
		model = glm::translate(model, glm::vec3(-65.0f, movYC7 - 7.5f, 17.5f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, rotC7 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.25f, 0.25f, 0.25f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Phineas.RenderModel();

		model = modelaux;// Ornitocyborg
		model = glm::translate(model, glm::vec3(-65.0f, movYC8 - 7.5f, 12.5f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, rotC8 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.125f, 0.125f, 0.125f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Ornitocyborg.RenderModel();
		
		model = modelaux;// Isabella
		model = glm::translate(model, glm::vec3(-65.0f, movYC9 - 7.5f, 7.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, rotC9 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(9.0f, 9.0f, 9.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Isabella.RenderModel();

		model = modelaux;// Edificio Doofenshmirtz
		model = glm::translate(model, glm::vec3(-65.0f, movYS3 - 17.5f, 2.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, rotS3 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.24f, 0.24f, 0.24f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Doof.RenderModel();

		model = modelaux;// Peter el Panda
		model = glm::translate(model, glm::vec3(-47.5f, movYD1 - 7.0f, -9.5f));
		model = glm::rotate(model, rotD1 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.65f, 0.65f, 0.65f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		PeterPanda.RenderModel();

		model = modelaux;// Doofenshmirtz
		model = glm::translate(model, glm::vec3(-42.5f, movYD2 - 13.0f, -9.5f));
		model = glm::rotate(model, rotD2 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.25f, 0.25f, 0.25f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Doofenshmirtz.RenderModel();
		
		model = modelaux;// Terry la tortuga
		model = glm::translate(model, glm::vec3(-37.5f, movYD3 - 7.0f, -9.5f));
		model = glm::rotate(model, rotD3 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.65f, 0.65f, 0.65f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		TerryTortuga.RenderModel();

		model = modelaux;// Candace
		model = glm::translate(model, glm::vec3(-32.5f, movYD4 - 13.0f, -9.5f));
		model = glm::rotate(model, rotD4 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.25f, 0.25f, 0.25f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Candace.RenderModel();

		model = modelaux;// Doofenshmirtz 2D
		model = glm::translate(model, glm::vec3(-27.5f, movYD5 - 13.0f, -9.5f));
		model = glm::rotate(model, rotD5 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(8.0f, 8.0f, 8.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Doofenshmirtz2D.RenderModel();

		model = modelaux;// Buford
		model = glm::translate(model, glm::vec3(-22.5f, movYD6 - 7.5f, -9.5f));
		model = glm::rotate(model, rotD6 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(7.5f, 7.5f, 7.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Buford.RenderModel();

		model = modelaux;// Pinky el Chihuahua
		model = glm::translate(model, glm::vec3(-17.5f, movYD7 - 7.5f, -9.5f));
		model = glm::rotate(model, rotD7 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		PinkyChihuahua.RenderModel();

		model = modelaux;// Carl
		model = glm::translate(model, glm::vec3(-12.5f, movYD8 - 13.0f, -9.5f));
		model = glm::rotate(model, rotD8 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(2.25f, 2.25f, 2.25f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Carl.RenderModel();

		model = modelaux;// Ferb
		model = glm::translate(model, glm::vec3(-7.5f, movYD9 - 13.0f, -9.5f));
		model = glm::rotate(model, rotD9 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.25f, 0.25f, 0.25f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Ferb.RenderModel();

		//PHINEAS Y FERB
		//Casa
		model = modelaux;
		model = glm::translate(model, glm::vec3(-23.0f, -0.8f, -45.0f));
		model = glm::scale(model, glm::vec3(0.7f, 0.7f, 0.7f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Casa2.RenderModel();

		//Doof casa
		model = modelaux;
		model = glm::translate(model, glm::vec3(-90.0f, -0.8f, -60.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		//model = glm::scale(model, glm::vec3(0.7f, 0.7f, 0.7f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Doof.RenderModel();

		//Edificio7
		model = modelaux;
		model = glm::translate(model, glm::vec3(-85.0f, -0.8f, 5.0f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Edificio7.RenderModel();

		//Edificio8
		model = modelaux;
		model = glm::translate(model, glm::vec3(-87.0f, -0.8f, -25.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.6f, 0.6f, 0.6f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Edificio8.RenderModel();

		//Edificio9
		model = modelaux;
		model = glm::translate(model, glm::vec3(-58.0f, -0.8f, -25.0f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.6f, 0.6f, 0.6f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Edificio9.RenderModel();

		//Edificio10
		model = modelaux;
		model = glm::translate(model, glm::vec3(-65.0f, -0.8f, -60.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.8f, 0.8f, 0.8f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Edificio10.RenderModel();

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glDisable(GL_BLEND);
		glUseProgram(0);
		mainWindow.swapBuffers();
	}
	return 0;
}