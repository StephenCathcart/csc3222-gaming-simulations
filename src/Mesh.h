#ifndef MESH_H
#define MESH_H

#include <GL\glew.h>
#include "glm\glm.hpp"
#include "Vec3.h"
#include <fstream>
#include <string>
#include <assimp\Importer.hpp>
#include <assimp\scene.h>
#include <assimp\postprocess.h> 

using std::string;

enum MeshBuffer {
	VERTEX_BUFFER , COLOUR_BUFFER , TEXTURE_BUFFER , NORMAL_BUFFER , INDEX_BUFFER, MAX_BUFFER
};

class Mesh {
public:
	Mesh(void);
	virtual ~Mesh(void);

	virtual void draw();

	static Mesh* importModel(const string &filename);

	void setTexture(GLuint tex) { texture = tex;}
	GLuint getTexture() { return texture; }

	void generateNormals();

	void drawBoundingBox(Mesh* mesh, glm::mat4 modelMat);
	void calculateSize(Mesh* mesh);

	const string getMeshName() { return m_filename; }
	float getXSize() { return m_xSize; }
	float getYSize() { return m_ySize; }
	float getZSize() { return m_zSize; }
	float getRadius() { return m_xSize / 2; }
	glm::vec3 getV0() { return vertices[0]; }
	glm::vec3 getPlaneNormal() {
		glm::vec3 &a = vertices[0];
		glm::vec3 &b = vertices[1];
		glm::vec3 &c = vertices[2];

		glm::vec3 normal = glm::cross(b-a,c-a);
		glm::vec3 n = glm::normalize(normal);

		return n;
	}

protected:
	//Buffers all VBO data into graphics memory. Required before drawing!
	void bufferData();
	
	GLuint arrayObject;
	GLuint bufferObject[MAX_BUFFER];
	GLuint numVertices;
	GLuint texture;
	GLuint type;

	glm::vec3* normals;
	
	//Pointer to vertex position attribute data (badly named...?)
	glm::vec3*		vertices;
	//Pointer to vertex colour attribute data
	glm::vec4*		colours;
	//Pointer to vertex texture coordinate attribute data
	glm::vec2*		textureCoords;

	//Optional, but using indices is more efficient
	GLuint numIndices;
	unsigned int* indices;

	// Collitsion variables
	float m_xSize;
	float m_ySize;
	float m_zSize;

	string m_filename;
};

#endif

