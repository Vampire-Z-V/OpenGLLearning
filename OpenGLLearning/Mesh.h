#ifndef MESH_H
#define MESH_H

#include <glad\glad.h>
#include <assimp\Importer.hpp>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

#include <string>
#include <vector>
#include <sstream>
using namespace std;

#include "shader.h"

struct Vertex
{
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
	glm::vec3 Tangent;
	glm::vec3 Bitangent;
};

struct Texture
{
	unsigned int id;
	string type;
	aiString path;
};

class Mesh
{
public:
	Mesh(vector <Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures);
	~Mesh();

	void draw(Shader shader);

private:
	void setupMesh();
	vector<Vertex> vertices;
	vector<unsigned int>indices;
	vector<Texture> textures;

	unsigned int VAO, VBO, EBO;
	
};

#endif // !MESH_H


