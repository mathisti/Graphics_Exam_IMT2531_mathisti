#pragma once

#include "shader.hpp"
#include "mesh.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"
#include "assimp/Importer.hpp"


#include <vector>
#include <iostream>

#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"

// TODO: RIP APART!!! (modularity.)


// Defines several possible options for model movement. Used as abstraction to stay away from window-system specific input methods
enum Model_Movement {
	throttle,
	throttleLEFT,
	throttleRIGHT,
	throttleUPWARD,
	throttleDOWNWARD
};



class Model
{
public:
	/*  Model atributes */
	float moveSpeed;
	glm::vec3 model_Front;
	glm::vec3 model_Up;
	glm::vec3 model_Right;
	glm::vec3 WorldUp;
	
	/* Euler Angles */
	float modelYaw;
	float modelPitch;

	/*  Functions   */
	Model();
	Model(char *path, glm::vec3);
	void Draw(Shader shader);
	glm::mat4 getTransform();
	void translate(glm::vec3 offset);
	void rotate(float degrees, glm::vec3 rotation);
	void scale(glm::vec3 scale);
	void scale(float scale);
	glm::vec3 getPos();
	void setPos(glm::vec3);
	void Model::ProcessKeyboard(Model_Movement direction, float deltaTime);
	void Model::updateModelVectors();
	
private:
	std::vector<Texture> textures_loaded;

	/*  Model Data  */
	glm::vec3 pos;
	glm::mat4 transform;
	std::vector<Mesh> meshes;
	std::string directory;
	/*  Functions   */
	void loadModel(std::string path);
	void processNode(aiNode *node, const aiScene *scene);
	Mesh processMesh(aiMesh *mesh, const aiScene *scene);
	std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type,
		std::string typeName);
};