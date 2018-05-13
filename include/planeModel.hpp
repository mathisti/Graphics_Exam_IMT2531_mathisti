#pragma once
#include "model.hpp"

class planeModel : public Model {
public:
	planeModel();
	planeModel(char *path);

	void update(Model_Movement direction, float deltaTime);
	void setNewPosition();
	void resetToOriginalPosition();
	glm::vec3 currentPosition();
private:
	glm::vec3 velocity;
	glm::vec3 pos;

	glm::vec3 Front;
	glm::vec3 Right;

	float Yaw;
	float Pitch;

	float currentSpeed;
	float acceleration;
	float rotationSpeed;
	float maxSpeed;
	float minSpeed;
};