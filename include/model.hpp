#pragma once
#define GLM_ENABLE_EXPERIMENTAL


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
#include "gtx/matrix_decompose.hpp"


class Model
{
public:
	/*  Model atributes */
	glm::mat4 transform;
	

	/*  Functions   */
	Model();
	Model(char *path);
	void Draw(Shader shader);
	glm::mat4 getTransform();
	void translate(glm::vec3 offset);
	void rotate(float degrees, glm::vec3 rotation);
	void scale(glm::vec3 scale);
	void scale(float scale);
	void loadModel(std::string path);
	
	
private:
	std::vector<Texture> textures_loaded;

	/*  Model Data  */
	std::vector<Mesh> meshes;
	std::string directory;

	/*  Functions   */
	void processNode(aiNode *node, const aiScene *scene);
	Mesh processMesh(aiMesh *mesh, const aiScene *scene);
	std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type,
		std::string typeName);
};