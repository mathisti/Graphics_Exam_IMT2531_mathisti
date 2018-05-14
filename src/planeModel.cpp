#include "planeModel.hpp"

planeModel::planeModel() {
	velocity = glm::vec3(-5.0f, 0.0f, 0.0f);
	rotationSpeed = 30.0f;
	acceleration = 1.0f;
	maxSpeed = 300.0f;
	minSpeed = 0.5f;
	moveSpeed = 0.5f;
}

planeModel::planeModel(char *path) {
	velocity = glm::vec3(-5.0f, 0.0f, 0.0f);
	rotationSpeed = 30.0f;
	acceleration = 2.0f;
	maxSpeed = 300.0f;
	minSpeed = 0.55f;
	moveSpeed = 0.5f;
	model_Front = glm::vec3(-1.0f, 0.0f, 0.0f);


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

	translate(glm::vec3(moveSpeed * deltaTime, 0.0f, 0.0f));
}

glm::vec3 planeModel::currentPosition() {
	glm::vec3 returnPosition;
	glm::decompose(transform, glm::vec3(), glm::quat(), returnPosition, glm::vec3(), glm::vec4());
	pos = returnPosition;
	return returnPosition;
}

void planeModel::updatePlaneVectors()
{
	// Calculate the new Front vector
	glm::vec3 front;
	front.x = cos(glm::radians(modelYaw)) * cos(glm::radians(modelPitch));
	front.y = sin(glm::radians(modelPitch));
	front.z = sin(glm::radians(modelYaw)) * cos(glm::radians(modelPitch));
	model_Front = glm::normalize(front);
	// Also re-calculate the Right and Up vector
	model_Right = glm::normalize(glm::cross(model_Front, WorldUp));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
	model_Up = glm::normalize(glm::cross(model_Right, model_Front));
}

void planeModel::setRandomPos() {
	glm::vec3 newPos = glm::vec3(40.0f, 25.0f, -33.0f);
	translate(newPos);
	pos = newPos;

}

void planeModel::resetPos() {
	glm::vec3 newPos = glm::vec3(-(spawn + pos));
	translate(newPos);
	pos = newPos;
}