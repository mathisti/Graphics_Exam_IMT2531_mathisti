#include "planeModel.hpp"

planeModel::planeModel() {
	velocity = glm::vec3(-5.0f, 0.0f, 0.0f);
	rotationSpeed = 30.0f;
	acceleration = 2.0f;
	maxSpeed = 300.0f;
	minSpeed = 0.5f;
	currentSpeed = 0.5f;
}

planeModel::planeModel(char *path) {
	velocity = glm::vec3(-5.0f, 0.0f, 0.0f);
	rotationSpeed = 30.0f;
	acceleration = 2.0f;
	maxSpeed = 300.0f;
	minSpeed = 0.55f;
	currentSpeed = 0.5f;

	loadModel(path);
}

void planeModel::update(Model_Movement direction, float deltaTime) {

	if (direction == throttleDOWNWARD) {
		rotate(rotationSpeed * deltaTime, glm::vec3(0.0f, 0.0f, 1.0f));
	}
	if (direction == throttleUPWARD) {
		rotate(-rotationSpeed * deltaTime, glm::vec3(0.0f, 0.0f, 1.0f));
	}
	if (direction == throttleLEFT) {
		rotate(rotationSpeed * deltaTime, glm::vec3(1.0f, 0.0f, 0.0f));
	}
	if (direction == throttleRIGHT) {
		rotate(-rotationSpeed * deltaTime, glm::vec3(1.0f, 0.0f, 0.0f));
	}

	translate(glm::vec3(-currentSpeed * deltaTime, 0.0f, 0.0f));
}

glm::vec3 planeModel::currentPosition() {
	glm::vec3 returnPosition;
	glm::decompose(transform, glm::vec3(), glm::quat(), returnPosition, glm::vec3(), glm::vec4());
	pos = returnPosition;
	return returnPosition;
}
