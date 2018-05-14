#pragma once
#include "model.hpp"

class planeModel : public Model {
public:

	float moveSpeed;
	glm::vec3 model_Front;

	planeModel();
	planeModel(char *path);

	void update(Model_Movement direction, float deltaTime);
	void setNewPosition();
	void resetToOriginalPosition();
	glm::vec3 currentPosition();
	void updatePlaneVectors();
	void setRandomPos();
	void resetPos();



	/* Euler Angles */
	float modelYaw;
	float modelPitch;

private:
	glm::vec3 velocity;
	glm::vec3 pos;
	glm::vec3 Right;

	float Yaw;
	float Pitch;

	float acceleration;
	float rotationSpeed;
	float maxSpeed;
	float minSpeed;
};