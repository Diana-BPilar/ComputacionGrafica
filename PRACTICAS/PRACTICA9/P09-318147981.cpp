/*
Semestre 2024-1
Animación:
Sesión 1:
Simple o básica:Por banderas y condicionales (más de 1 transforomación geométrica se ve modificada
Sesión 2
Compleja: Por medio de funciones y algoritmos.
Adicional.- ,Textura Animada
*/
//para cargar imagen
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
//para probar el importer
//#include<assimp/Importer.hpp>

#include "Window.h"
#include "Mesh.h"
#include "Shader_light.h"
#include "Camera.h"
#include "Texture.h"
#include "Sphere.h"
#include"Model.h"
#include "Skybox.h"

//para iluminación
#include "CommonValues.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "Material.h"

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <chrono>
#include <thread>


const float toRadians = 3.14159265f / 180.0f;

//variables para animación
float movCoche;
float movCoche2;
float movDado;
float movDado2;
float movLetrero;
float movOffsetD;
float movOffsetV;
float rotllanta;
float rotLetrero;
float rotDadox;
float rotDadoy;
int tiradaDado;
float rotllantaOffset;
bool avanza;
bool regresa;
bool caer;


Window mainWindow;
std::vector<Mesh*> meshList;
std::vector<Shader> shaderList;

Camera camera;

Texture brickTexture;
Texture dirtTexture;
Texture plainTexture;
Texture pisoTexture;
Texture AgaveTexture;
Texture Blanco;
Texture Casilla1;
Texture Casilla2;
Texture Casilla3;
Texture dadodiez1Texture;
Texture dadodiez2Texture;

Model Kitt_M;
Model Llanta_M;
Model Blackhawk_M;
Model Arco;
Model Letrero;
Model Casa;
Model Vehiculo;
Model Helice1;
Model Helice2;


Skybox skybox;

//materiales
Material Material_brillante;
Material Material_opaco;


//Sphere cabeza = Sphere(0.5, 20, 20);
GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;
static double limitFPS = 1.0 / 60.0;

// luz direccional
DirectionalLight mainLight;
//para declarar varias luces de tipo pointlight
PointLight pointLights[MAX_POINT_LIGHTS];
SpotLight spotLights[MAX_SPOT_LIGHTS];

// Vertex Shader
static const char* vShader = "shaders/shader_light.vert";

// Fragment Shader
static const char* fShader = "shaders/shader_light.frag";


//función de calculo de normales por promedio de vértices 
void calcAverageNormals(unsigned int* indices, unsigned int indiceCount, GLfloat* vertices, unsigned int verticeCount,
	unsigned int vLength, unsigned int normalOffset)
{
	for (size_t i = 0; i < indiceCount; i += 3)
	{
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

	for (size_t i = 0; i < verticeCount / vLength; i++)
	{
		unsigned int nOffset = i * vLength + normalOffset;
		glm::vec3 vec(vertices[nOffset], vertices[nOffset + 1], vertices[nOffset + 2]);
		vec = glm::normalize(vec);
		vertices[nOffset] = vec.x; vertices[nOffset + 1] = vec.y; vertices[nOffset + 2] = vec.z;
	}
}


void CreateObjects()
{
	unsigned int indices[] = {
		0, 3, 1,
		1, 3, 2,
		2, 3, 0,
		0, 1, 2
	};

	GLfloat vertices[] = {
		//	x      y      z			u	  v			nx	  ny    nz
			-1.0f, -1.0f, -0.6f,	0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
			0.0f, -1.0f, 1.0f,		0.5f, 0.0f,		0.0f, 0.0f, 0.0f,
			1.0f, -1.0f, -0.6f,		1.0f, 0.0f,		0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f,		0.5f, 1.0f,		0.0f, 0.0f, 0.0f
	};

	unsigned int floorIndices[] = {
		0, 2, 1,
		1, 2, 3
	};

	GLfloat floorVertices[] = {
		-10.0f, 0.0f, -10.0f,	0.0f, 0.0f,		0.0f, -1.0f, 0.0f,
		10.0f, 0.0f, -10.0f,	10.0f, 0.0f,	0.0f, -1.0f, 0.0f,
		-10.0f, 0.0f, 10.0f,	0.0f, 10.0f,	0.0f, -1.0f, 0.0f,
		10.0f, 0.0f, 10.0f,		10.0f, 10.0f,	0.0f, -1.0f, 0.0f
	};

	unsigned int vegetacionIndices[] = {
	   0, 1, 2,
	   0, 2, 3,
	   4,5,6,
	   4,6,7
	};

	GLfloat vegetacionVertices[] = {
		-0.5f, -0.5f, 0.0f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.5f, -0.5f, 0.0f,		1.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.5f, 0.5f, 0.0f,		1.0f, 1.0f,		0.0f, 0.0f, 0.0f,
		-0.5f, 0.5f, 0.0f,		0.0f, 1.0f,		0.0f, 0.0f, 0.0f,

		0.0f, -0.5f, -0.5f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.0f, -0.5f, 0.5f,		1.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.0f, 0.5f, 0.5f,		1.0f, 1.0f,		0.0f, 0.0f, 0.0f,
		0.0f, 0.5f, -0.5f,		0.0f, 1.0f,		0.0f, 0.0f, 0.0f,


	};
	
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

	calcAverageNormals(vegetacionIndices, 12, vegetacionVertices, 64, 8, 5);

}

void Casillas() {
	unsigned int Casillas1_indices[] = {
		0,1,2, 0,2,3,
		4,5,6, 4,6,7,

		0,1,5, 0,4,5,
		1,2,6, 1,5,6,
		0,3,4, 3,4,7,
		2,3,6, 3,6,7,
	};
	GLfloat Casillas1_vertices[] = {
		1.0f, 0.2f, 1.0f, 1.0f,0.0f, 0.0f,0.0f,0.0f,//A - 0
		1.0f, 0.2f,-1.0f, 1.0f,1.0f, 0.0f,0.0f,0.0f,//B - 1
	   -1.0f, 0.2f,-1.0f, 0.0f,1.0f, 0.0f,0.0f,0.0f,//C - 2
	   -1.0f, 0.2f, 1.0f, 0.0f,0.0f, 0.0f,0.0f,0.0f,//D - 3

		1.0f, 0.0f, 1.0f, 1.0f,0.0f, 0.0f,0.0f,0.0f,//E - 4
		1.0f, 0.0f,-1.0f, 1.0f,1.0f, 0.0f,0.0f,0.0f,//F - 5
	   -1.0f, 0.0f,-1.0f, 0.0f,1.0f, 0.0f,0.0f,0.0f,//G - 6
	   -1.0f, 0.0f, 1.0f, 0.0f,0.0f, 0.0f,0.0f,0.0f,//H - 7

	};
	Mesh* Casillas1 = new Mesh();
	Casillas1->CreateMesh(Casillas1_vertices, Casillas1_indices, 64, 36);
	meshList.push_back(Casillas1);

	unsigned int Casillas2_indices[] = {
		0,1,2, 0,2,3,
		4,5,6, 4,6,7,

		0,1,5, 0,4,5,
		1,2,6, 1,5,6,
		0,3,4, 3,4,7,
		2,3,6, 3,6,7,
	};
	GLfloat Casillas2_vertices[] = {
		1.0f, 0.2f, 0.5f, 1.0f,1.0f, 0.0f,0.0f,0.0f,//A - 0
		1.0f, 0.2f,-0.5f, 1.0f,0.0f, 0.0f,0.0f,0.0f,//B - 1
	   -1.0f, 0.2f,-0.5f, 0.0f,0.0f, 0.0f,0.0f,0.0f,//C - 2
	   -1.0f, 0.2f, 0.5f, 0.0f,1.0f, 0.0f,0.0f,0.0f,//D - 3

		1.0f, 0.0f, 0.5f, 1.0f,1.0f, 0.0f,0.0f,0.0f,//E - 4
		1.0f, 0.0f,-0.5f, 1.0f,0.0f, 0.0f,0.0f,0.0f,//F - 5
	   -1.0f, 0.0f,-0.5f, 0.0f,0.0f, 0.0f,0.0f,0.0f,//G - 6
	   -1.0f, 0.0f, 0.5f, 0.0f,1.0f, 0.0f,0.0f,0.0f,//H - 7
	};
	Mesh* Casillas2 = new Mesh();
	Casillas2->CreateMesh(Casillas2_vertices, Casillas2_indices, 144, 90);
	meshList.push_back(Casillas2);
}

void CrearPiramidePentagonal()
{

	unsigned int piramidepentagonal_indices[] = {
		// Caras triangulares que conectan la punta con cada lado del pentágono
		0, 1, 2,  // Cara 1
		3, 4, 5,  // Cara 2
		6, 7, 8,  // Cara 3
		9, 10, 11, // Cara 4
		12, 13, 14, // Cara 5

		// Base pentagonal (hacemos 3 triángulos para formar la base)
		0, 1, 4,  // Primer triángulo
		4, 7, 10,  // Segundo triángulo
		10, 13, 0   // Tercer triángulo
	};



	GLfloat piramidepentagonal_vertices[] = {
		//X     Y      Z            S    T            NX     NY     NZ
		0.5f, -0.5f,  0.0f,	      0.29f, 0.57f,	   0.0,  0.0f,   -1.0f,  // Vértice 0  //0
		0.15f, -0.5f,  0.47f,     0.04f, 0.57f,    0.0f,  0.0f,   -1.0f,  // Vértice 1  //1
		0.0f,  0.5f,  0.0f,       0.17f, 0.98f,    0.0f,  0.0f,   -1.0f,   // Vértice 5 (punta de la pirámide) //2

		0.15f, -0.5f,  0.47f,     0.63f, 0.57f,    -1.0f, 0.0f, 0.0f,  // Vértice 1  //3
	   -0.4f, -0.5f,  0.29f,      0.37f, 0.57f,    -1.0f, 0.0f, 0.0f,  // Vértice 2  //4
		0.0f,  0.5f,  0.0f,       0.5f, 0.98f,     -1.0f, 0.0f, 0.0f,   // Vértice 5 (punta de la pirámide) //5

	   -0.4f, -0.5f,  0.29f,      0.95f, 0.57f,    0.0f,  0.0f,  1.0f,  // Vértice 2  //6
	   -0.4f, -0.5f, -0.29f,      0.72f, 0.57f,    0.0f,  0.0f,  1.0f,  // Vértice 3   //7
	   0.0f,  0.5f,  0.0f,        0.83f, 0.98f,    0.0f,  0.0f,  1.0f,   // Vértice 5 (punta de la pirámide) //8

	   -0.4f, -0.5f, -0.29f,      0.29f, 0.07f,     1.0f,  0.0f,  0.0f,  // Vértice 3   //9
		0.15f, -0.5f, -0.47f,     0.05f, 0.07f,     1.0f,  0.0f,  0.0f,  // Vértice 4   //10
		0.0f,  0.5f,  0.0f,       0.165f, 0.43f,    1.0f,  0.0f,  0.0f,   // Vértice 5 (punta de la pirámide) //11

		0.15f, -0.5f, -0.47f,     0.62f, 0.07f,     0.0f,   1.0f,   0.0f,  // Vértice 4   //12
		0.5f, -0.5f,  0.0f,	      0.38f, 0.07f,	    0.0f,   1.0f,   0.0f,  // Vértice 0  //13
		0.0f,  0.5f,  0.0f,       0.5f, 0.43f,      0.0f,   1.0f,   0.0f   // Vértice 5 (punta de la pirámide) //14
	};

	Mesh* piramide = new Mesh();
	piramide->CreateMesh(piramidepentagonal_vertices, piramidepentagonal_indices, 120, 24);
	meshList.push_back(piramide);
}

void CreateShaders()
{
	Shader *shader1 = new Shader();
	shader1->CreateFromFiles(vShader, fShader);
	shaderList.push_back(*shader1);
}



int main()
{

	srand(time(0));

	mainWindow = Window(1366, 768); // 1280, 1024 or 1024, 768
	mainWindow.Initialise();

	CreateObjects();
	Casillas();
	CrearPiramidePentagonal();
	CreateShaders();

	camera = Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -60.0f, 0.0f, 0.3f, 0.5f);

	brickTexture = Texture("Textures/brick.png");
	brickTexture.LoadTextureA();
	dirtTexture = Texture("Textures/dirt.png");
	dirtTexture.LoadTextureA();
	plainTexture = Texture("Textures/plain.png");
	plainTexture.LoadTextureA();
	pisoTexture = Texture("Textures/pisoT.tga");
	pisoTexture.LoadTextureA();
	AgaveTexture = Texture("Textures/Agave.tga");
	AgaveTexture.LoadTextureA();

	Casilla1 = Texture("Textures/Casilla1.tga");
	Casilla1.LoadTextureA();
	Casilla2 = Texture("Textures/Casilla2.tga");
	Casilla2.LoadTextureA();
	Casilla3 = Texture("Textures/Casilla3.tga");
	Casilla3.LoadTextureA();

	dadodiez1Texture = Texture("Textures/dadodiez_1.tga");
	dadodiez1Texture.LoadTextureA();
	dadodiez2Texture = Texture("Textures/dadodiez_2.tga");
	dadodiez2Texture.LoadTextureA();


	Kitt_M = Model();
	Kitt_M.LoadModel("Models/kitt_optimizado.obj");
	Llanta_M = Model();
	Llanta_M.LoadModel("Models/llanta_optimizada.obj");
	Blackhawk_M = Model();
	Blackhawk_M.LoadModel("Models/uh60.obj");
	Arco = Model();
	Arco.LoadModel("Models/arco.obj");
	Letrero = Model();
	Letrero.LoadModel("Models/letrero.obj");
	Casa = Model();
	Casa.LoadModel("Models/casa.obj");
	Vehiculo = Model();
	Vehiculo.LoadModel("Models/vehiculo.obj");
	Helice1 = Model();
	Helice1.LoadModel("Models/helice1.obj");
	Helice2 = Model();
	Helice2.LoadModel("Models/helice2.obj");
	

	std::vector<std::string> skyboxFaces;
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_rt.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_lf.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_dn.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_up.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_bk.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_ft.tga");

	skybox = Skybox(skyboxFaces);

	Material_brillante = Material(4.0f, 256);
	Material_opaco = Material(0.3f, 4);


	//luz direccional, sólo 1 y siempre debe de existir
	mainLight = DirectionalLight(1.0f, 1.0f, 1.0f,
		0.3f, 0.3f,
		0.0f, 0.0f, -1.0f);
	//contador de luces puntuales
	unsigned int pointLightCount = 0;
	//Declaración de primer luz puntual
	pointLights[0] = PointLight(1.0f, 0.0f, 0.0f,
		0.0f, 1.0f,
		-6.0f, 1.5f, 1.5f,
		0.3f, 0.2f, 0.1f);
	pointLightCount++;

	unsigned int spotLightCount = 0;
	//linterna
	spotLights[0] = SpotLight(1.0f, 1.0f, 1.0f,
		0.0f, 2.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, -1.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		5.0f);
	spotLightCount++;

	//luz fija
	spotLights[1] = SpotLight(0.0f, 1.0f, 0.0f,
		1.0f, 2.0f,
		5.0f, 10.0f, 0.0f,
		0.0f, -5.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		15.0f);
	spotLightCount++;
	
	//se crean mas luces puntuales y spotlight 

	GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0, uniformEyePosition = 0,
		uniformSpecularIntensity = 0, uniformShininess = 0;
	GLuint uniformColor = 0;
	glm::mat4 projection = glm::perspective(45.0f, (GLfloat)mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 1000.0f);
	movCoche = 0.0f;
	movCoche2 = -55.0f;
	movDado = 6.5f;
	//movDado2 = -2.0f;
	movLetrero = 3.0f;
	movOffsetD = 0.02f;
	movOffsetV = 0.5f;
	rotllanta = 0.0f;
	rotLetrero = 0.0f;
	rotDadox = 0.0f;
	rotDadoy = 0.0f;
	rotllantaOffset = 0.6f;
	tiradaDado = rand() % 10 + 1;
	avanza = true;
	regresa = true;
	caer = true;
	int iter = 0;
	////Loop mientras no se cierra la ventana
	while (!mainWindow.getShouldClose())
	{
		GLfloat now = glfwGetTime(); //Tiempo actual o tiempo de inicio
		deltaTime = now - lastTime; //Tiempo que transcurre
		deltaTime += (now - lastTime) / limitFPS;
		lastTime = now;




		//Tirada del Dado
		if (mainWindow.getpres() == true) {
			if (caer) {

				if (movDado <= 6.5 && movDado > 1.3f) {
					movDado -= movOffsetD * deltaTime;
				}
				else {
					switch (tiradaDado) {
					case 1:
						if (rotDadox < 70.0f) {
							rotDadox += rotllantaOffset * deltaTime;
						}
						if (movDado < 1.3f && movDado>0.4) {
							movDado -= movOffsetD * deltaTime;
						}
						else {
							if (rotDadoy > -20.0f) {
								rotDadoy -= rotllantaOffset * deltaTime;
							}
						}

						break;
					case 2:

						if (rotDadox > -120.0f) {
							rotDadox -= rotllantaOffset * deltaTime;
						}
						if (movDado < 1.3f && movDado>-0.1) {
							//printf("movDado%f \n ", movDado);
							movDado -= movOffsetD * deltaTime;
						}
						else {
							if (rotDadoy < 90.0f) {
								rotDadoy += rotllantaOffset * deltaTime;
							}
						}

						break;
					case 3:
						if (rotDadox < 70.0f) {
							rotDadox += rotllantaOffset * deltaTime;
						}
						if (movDado < 1.3f && movDado>0.4) {
							movDado -= movOffsetD * deltaTime;
						}
						else {
							if (rotDadoy > -90.0f) {
								rotDadoy -= rotllantaOffset * deltaTime;
							}
						}
						break;

					case 4:

						if (rotDadox > -120.0f) {
							rotDadox -= rotllantaOffset * deltaTime;
						}
						if (movDado < 1.3f && movDado>-0.1) {
							//printf("movDado%f \n ", movDado);
							movDado -= movOffsetD * deltaTime;
						}
						else {
							if (rotDadoy > -120.0f) {
								rotDadoy -= rotllantaOffset * deltaTime;
							}
						}

						break;
					case 5:

						if (rotDadox < 70.0f) {
							rotDadox += rotllantaOffset * deltaTime;
						}
						if (movDado < 1.3f && movDado>0.4) {
							movDado -= movOffsetD * deltaTime;
						}
						else {
							if (rotDadoy < 125.0f) {
								rotDadoy += rotllantaOffset * deltaTime;
							}
						}
						break;

					case 6:

						if (rotDadox > -120.0f) {
							rotDadox -= rotllantaOffset * deltaTime;
						}
						if (movDado < 1.3f && movDado>-0.1) {
							//printf("movDado%f \n ", movDado);
							movDado -= movOffsetD * deltaTime;
						}
						else {
							if (rotDadoy < 165.0f) {
								rotDadoy += rotllantaOffset * deltaTime;
							}
						}
						break;

					case 7:

						if (rotDadox < 70.0f) {
							rotDadox += rotllantaOffset * deltaTime;
						}
						if (movDado < 1.3f && movDado>0.4) {
							movDado -= movOffsetD * deltaTime;
						}
						else {
							if (rotDadoy < 55.0f) {
								rotDadoy += rotllantaOffset * deltaTime;
							}
						}

						break;

					case 8:

						if (rotDadox > -120.0f) {
							rotDadox -= rotllantaOffset * deltaTime;
						}
						if (movDado < 1.3f && movDado>-0.1) {
							//printf("movDado%f \n ", movDado);
							movDado -= movOffsetD * deltaTime;
						}
						else {
							if (rotDadoy < 17.0f) {
								rotDadoy += rotllantaOffset * deltaTime;
							}
						}

						break;

					case 9:
						if (rotDadox < 70.0f) {
							rotDadox += rotllantaOffset * deltaTime;
						}
						if (movDado < 1.3f && movDado>0.4) {
							movDado -= movOffsetD * deltaTime;
						}
						else {
							if (rotDadoy > -160.0f) {
								rotDadoy -= rotllantaOffset * deltaTime;
							}
						}

						break;

					case 10:
						if (rotDadox > -120.0f) {
							rotDadox -= rotllantaOffset * deltaTime;
						}
						if (movDado < 1.3f && movDado>-0.1) {
							//printf("movDado%f \n ", movDado);
							movDado -= movOffsetD * deltaTime;
						}
						else {
							if (rotDadoy > -50.0f) {
								rotDadoy -= rotllantaOffset * deltaTime;
							}
						}
						break;

					default:

						break;
					}
				}
			}
		}
		

		//Movimiento del vehiculo
		
		if (avanza) {
			
			if (movCoche >= 0.0f && movCoche <56.8f) {
				
				movCoche += movOffsetV * deltaTime;
				
			}
			else {
				if (rotLetrero < 90.0f || rotLetrero==0.0f) {
					rotLetrero += rotllantaOffset * deltaTime;
				}
				else {
					if (movCoche >= 56.8f) {
						
						if (movCoche2>=-55.0f && movCoche2<29.0f) {
							movCoche2 += movOffsetV * deltaTime;
						}
						else {
							if (rotLetrero < 180.0f) {
								rotLetrero += rotllantaOffset * deltaTime;
							}
							else {
								avanza = !avanza;
								//printf("avanza %s \n ", avanza);
								//movCoche -= movOffset * deltaTime;
							}
						}

					}
				}
			}
		}
		else {
			
			if (regresa) {
				if (movCoche > -30.0f && movCoche < 57.0f) {
					//printf("movCoche%f \n ", movCoche);
					movCoche -= movOffsetV * deltaTime;
				}
				else {
					if (rotLetrero < 270.0f) {
						rotLetrero += rotllantaOffset * deltaTime;
					}
					else {

						if (movCoche > -31.0f) {

							if (movCoche2 < 29.2f && movCoche2 > -54.0f) {
								movCoche2 -= movOffsetV * deltaTime;
							}
							else {
								if (rotLetrero < 360.0f) {
									rotLetrero += rotllantaOffset * deltaTime;
								}
								else {
									regresa = !regresa;
								}
							}
						}
					}
				}
			}
			else {
				if (movCoche > -31.0f && movCoche < 0.0f) {
					movCoche += movOffsetV * deltaTime;
				}
				else {
					avanza = !avanza;
					regresa = true;
					rotLetrero = 0;
				}
			}
		}

		rotllanta += rotllantaOffset * deltaTime;

		/*
		if (avanza)
		{
			
			if (movLetrero > 0.1f) {
				//printf("movLetrero%f \n ", movLetrero);
				if (movLetrero>2.9f && movLetrero<3.1f) {
					if (rotLetrero < 360.0f) {
						rotLetrero += rotllantaOffset * deltaTime;
					}
					else {
						movLetrero -= movOffset * deltaTime;
						
					}
				}
				else {
					movLetrero -= movOffset * deltaTime;
					rotLetrero = 0.0f;
				}
				
			}
			else {
				avanza = !avanza;
			}
			
		}else {
			if (movLetrero <= 3.0f) {
				
				if (movLetrero > 0.09f && movLetrero < 0.12f) {
					//printf("movLetrero%f \n ", movLetrero);
					if (rotLetrero < 360.0f) {
						rotLetrero += rotllantaOffset * deltaTime;
					}
					else {
						movLetrero += movOffset * deltaTime;

					}
				}
				else {
					movLetrero += movOffset * deltaTime;
					rotLetrero = 0.0f;
				}
			}
			else {
				avanza = !avanza;
			}
		}
		*/

		//Recibir eventos del usuario
		glfwPollEvents();
		camera.keyControl(mainWindow.getsKeys(), deltaTime);
		camera.mouseControl(mainWindow.getXChange(), mainWindow.getYChange());

		// Clear the window
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		skybox.DrawSkybox(camera.calculateViewMatrix(), projection);
		shaderList[0].UseShader();
		uniformModel = shaderList[0].GetModelLocation();
		uniformProjection = shaderList[0].GetProjectionLocation();
		uniformView = shaderList[0].GetViewLocation();
		uniformEyePosition = shaderList[0].GetEyePositionLocation();
		uniformColor = shaderList[0].getColorLocation();
		
		//información en el shader de intensidad especular y brillo
		uniformSpecularIntensity = shaderList[0].GetSpecularIntensityLocation();
		uniformShininess = shaderList[0].GetShininessLocation();

		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
		glUniform3f(uniformEyePosition, camera.getCameraPosition().x, camera.getCameraPosition().y, camera.getCameraPosition().z);

		// luz ligada a la cámara de tipo flash
		//sirve para que en tiempo de ejecución (dentro del while) se cambien propiedades de la luz
			glm::vec3 lowerLight = camera.getCameraPosition();
		lowerLight.y -= 0.3f;
		spotLights[0].SetFlash(lowerLight, camera.getCameraDirection());

		//información al shader de fuentes de iluminación
		shaderList[0].SetDirectionalLight(&mainLight);
		shaderList[0].SetPointLights(pointLights, pointLightCount);
		shaderList[0].SetSpotLights(spotLights, spotLightCount);



		glm::mat4 model(1.0);
		glm::mat4 modelaux(1.0);
		glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(30.0f, 1.0f, 30.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));

		pisoTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);

		meshList[2]->RenderMesh();

		//TABLERO
		//-Casilla de inicio
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Casilla1.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[4]->RenderMesh();

		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 1.5f));
		//model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Casilla2.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[5]->RenderMesh();

		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 1.0f));
		//model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Casilla2.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[5]->RenderMesh();

		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 1.0f));
		//model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Casilla2.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[5]->RenderMesh();

		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 1.0f));
		//model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Casilla2.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[5]->RenderMesh();

		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 1.0f));
		//model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Casilla2.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[5]->RenderMesh();

		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 1.0f));
		//model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Casilla2.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[5]->RenderMesh();

		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 1.0f));
		//model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Casilla2.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[5]->RenderMesh();

		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 1.0f));
		//model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Casilla2.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[5]->RenderMesh();

		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 1.0f));
		//model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Casilla2.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[5]->RenderMesh();

		//-Esquina
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 1.5f));
		//model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Casilla3.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[4]->RenderMesh();

		//-------

		model = glm::translate(model, glm::vec3(-1.5f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		//model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Casilla2.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[5]->RenderMesh();

		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -1.0f));
		//model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Casilla2.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[5]->RenderMesh();

		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -1.0f));
		//model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Casilla2.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[5]->RenderMesh();

		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -1.0f));
		//model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Casilla2.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[5]->RenderMesh();

		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -1.0f));
		//model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Casilla2.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[5]->RenderMesh();

		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -1.0f));
		//model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Casilla2.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[5]->RenderMesh();

		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -1.0f));
		//model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Casilla2.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[5]->RenderMesh();

		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -1.0f));
		//model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Casilla2.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[5]->RenderMesh();

		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -1.0f));
		//model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Casilla2.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[5]->RenderMesh();

		//-Esquina
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -1.5f));
		//model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Casilla3.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[4]->RenderMesh();

		//-------

		model = glm::translate(model, glm::vec3(1.5f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		//model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Casilla2.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[5]->RenderMesh();

		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 1.0f));
		//model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Casilla2.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[5]->RenderMesh();

		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 1.0f));
		//model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Casilla2.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[5]->RenderMesh();

		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 1.0f));
		//model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Casilla2.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[5]->RenderMesh();

		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 1.0f));
		//model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Casilla2.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[5]->RenderMesh();

		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 1.0f));
		//model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Casilla2.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[5]->RenderMesh();

		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 1.0f));
		//model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Casilla2.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[5]->RenderMesh();

		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 1.0f));
		//model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Casilla2.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[5]->RenderMesh();

		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 1.0f));
		//model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Casilla2.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[5]->RenderMesh();

		//-Esquina
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 1.5f));
		//model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Casilla3.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[4]->RenderMesh();

		//-------

		model = glm::translate(model, glm::vec3(-1.5f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		//model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Casilla2.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[5]->RenderMesh();

		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 1.0f));
		//model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Casilla2.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[5]->RenderMesh();

		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 1.0f));
		//model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Casilla2.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[5]->RenderMesh();

		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 1.0f));
		//model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Casilla2.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[5]->RenderMesh();

		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 1.0f));
		//model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Casilla2.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[5]->RenderMesh();

		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 1.0f));
		//model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Casilla2.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[5]->RenderMesh();

		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 1.0f));
		//model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Casilla2.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[5]->RenderMesh();

		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 1.0f));
		//model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Casilla2.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[5]->RenderMesh();

		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));
		model = glm::translate(model, glm::vec3(-1.5f, -0.34f, 0.0f));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Casilla2.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[5]->RenderMesh();

		
		//Arco
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -0.2f, 0.0f));
		modelaux = model;
		model = glm::scale(model, glm::vec3(0.6f, 0.6f, 0.6f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Arco.RenderModel();

		//Letrero
		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f, movLetrero, 0.3f));
		//model = glm::translate(model, glm::vec3(0.0f, 0.1f, 0.3f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, rotLetrero * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(0.6f, 0.6f, 0.6f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Letrero.RenderModel();

		//Dado de Opengl
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-20.5f, movDado, 0.0f));
		model = glm::scale(model, glm::vec3(2.0f, 1.2f, 2.0f));
		model = glm::rotate(model, rotDadox * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, rotDadoy * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		dadodiez1Texture.UseTexture();
		meshList[6]->RenderMesh();

		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f, -1.0f, 0.0f));
		//model = glm::scale(model, glm::vec3(5.5f, 5.2f, 5.5f));
		model = glm::rotate(model, -180 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::rotate(model, -105 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		dadodiez2Texture.UseTexture();
		meshList[6]->RenderMesh();

		//Casa
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-45.0f, -1.2f, 0.0f));
		modelaux = model;
		model = glm::scale(model, glm::vec3(0.6f, 0.6f, 0.6f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Casa.RenderModel();

		//Vehiculo
		model = glm::mat4(1.0);
		//model = glm::translate(model, glm::vec3(-55.0f, 5.0f, movCoche));
		model = glm::translate(model, glm::vec3(movCoche2, 5.0f, movCoche));
		//modelaux = model;
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));
		model = glm::rotate(model, rotLetrero * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Vehiculo.RenderModel();

		//Helice 1
		model = modelaux;
		model = glm::translate(model, glm::vec3(7.8f, 2.0f, 0.0f));
		//model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, rotllanta * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		//model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Helice1.RenderModel();

		//Helice 2
		model = modelaux;
		model = glm::translate(model, glm::vec3(-7.8f, 2.0f, 0.0f));
		//model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, rotllanta * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		//model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Helice2.RenderModel();

		/*
		//Instancia del coche 
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(movCoche, 0.5f, -3.0f));
		modelaux = model;
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Kitt_M.RenderModel();

		//Llanta delantera izquierda
		model = modelaux;
		model = glm::translate(model, glm::vec3(7.0f, -0.5f, 8.0f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, rotllanta * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));
		color = glm::vec3(0.5f, 0.5f, 0.5f);//llanta con color gris
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Llanta_M.RenderModel();

		//Llanta trasera izquierda
		model = modelaux;
		model = glm::translate(model, glm::vec3(15.5f, -0.5f, 8.0f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, rotllanta * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Llanta_M.RenderModel();

		//Llanta delantera derecha
		model = modelaux;
		model = glm::translate(model, glm::vec3(7.0f, -0.5f, 1.5f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, -rotllanta * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Llanta_M.RenderModel();

		//Llanta trasera derecha
		model = modelaux;
		model = glm::translate(model, glm::vec3(15.5f, -0.5f, 1.5f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, -rotllanta * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Llanta_M.RenderModel();
	

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 5.0f, 6.0));
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Blackhawk_M.RenderModel();

		//Agave ¿qué sucede si lo renderizan antes del coche y el helicóptero?
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 1.0f, -4.0f));
		model = glm::scale(model, glm::vec3(4.0f, 4.0f, 4.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		
		//blending: transparencia o traslucidez
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		AgaveTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[3]->RenderMesh();
		glDisable(GL_BLEND);
		*/
		glUseProgram(0);

		mainWindow.swapBuffers();
	}

	return 0;
}
