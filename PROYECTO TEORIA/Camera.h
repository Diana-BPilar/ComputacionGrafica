#pragma once

#include <glew.h>

#include <glm.hpp>
#include <gtc\matrix_transform.hpp>

#include <glfw3.h>

class Camera
{
public:
	Camera();
	Camera(glm::vec3 startPosition, glm::vec3 startUp, GLfloat startYaw, GLfloat startPitch, GLfloat startMoveSpeed, GLfloat startTurnSpeed);

	void keyControl(bool* keys, GLfloat deltaTime);
	void mouseControl(GLfloat xChange, GLfloat yChange);

	void updateThirdPerson(const glm::vec3& characterPosition, float characterRotation);
	void updateAerialView(bool* keys, GLfloat deltaTime);
    
    // Métodos para cambiar entre modos de cámara
    void toggleAerialView();
    bool isInAerialView() { return isAerialView; }

	glm::vec3 getCameraPosition();
	glm::vec3 getCameraDirection();
	glm::mat4 calculateViewMatrix();

	~Camera();

private:
	glm::vec3 position;
	glm::vec3 front;
	glm::vec3 up;
	glm::vec3 right;
	glm::vec3 worldUp;

	GLfloat yaw;
	GLfloat pitch;

	GLfloat moveSpeed;
	GLfloat turnSpeed;

	// Variables para cámara en tercera persona
	glm::vec3 targetPosition;
	float cameraDistance;
	float cameraHeight;

	// Variables para cámara aérea
	bool isAerialView;
	float aerialHeight;
	float aerialMoveSpeed;

	void update();
};

