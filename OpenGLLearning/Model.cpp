//#include "Model.h"
//
//Model::Model(char * path)
//{
//	loadModel(path);
//}
//
//void Model::draw(Shader shader)
//{
//	for (unsigned int i = 0; i < meshes.size(); i++)
//		meshes[i].draw(shader);
//}
//
//void Model::loadModel(string path)
//{
//	Assimp::Importer importer;
//	const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
//
//	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
//	{
//		cout << "ERROR::ASSIMP::" << importer.GetErrorString() << endl;
//		return;
//	}
//	directory = path.substr(0, path.find_last_of('/'));
//
//	processNode(scene->mRootNode, scene);
//}
//
//void Model::processNode(aiNode * node, const aiScene * scene)
//{
//}
//
//Mesh Model::processMesh(aiMesh * mesh, const aiScene * scene)
//{
//	return Mesh();
//}
//
//vector<Texture> Model::loadMaterialTextures(aiMaterial * mat, aiTextureType type, string typeName)
//{
//	return vector<Texture>();
//}
