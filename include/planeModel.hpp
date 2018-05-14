#pragma once
#include "model.hpp"


// Defines several possible options for plane movement. Used as abstraction to stay away from window-system specific input methods
enum Model_Movement {
	throttleLEFT,
	throttleRIGHT,
	throttleUPWARD,
	throttleDOWNWARD
};


class planeModel : public Model {
public:

	float moveSpeed;
	glm::vec3 model_Front;
	glm::vec3 model_Up;
	glm::vec3 model_Right;
	glm::vec3 WorldUp;
	glm::vec3 spawn;

	planeModel();
	planeModel(char *path);

	void update(Model_Movement direction, float deltaTime);
	glm::vec3 currentPosition();
	void updatePlaneVectors();
	void setRandomPos();
	void resetPos(glm::vec3);



	/* Euler Angles */
	float modelYaw;
	float modelPitch;

private:
	glm::vec3 velocity;
	glm::vec3 pos;

	float Yaw;
	float Pitch;

	float acceleration;
	float rotationSpeed;
	float maxSpeed;
	float minSpeed;
};