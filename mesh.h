#ifndef MESH_INCLUDED_H
#define MESH_INCLUDED_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <string>
#include <vector>
#include "transform.h"

struct ModelAsset
{
    GLenum primitiveType;

    std::vector<glm::vec3> positions; 
    std::vector<glm::vec3> colors;
    std::vector<glm::vec2> texCoords;
    std::vector<glm::vec3> normals;

    std::vector<unsigned int> indices;

    void addVertex(const glm::vec3& position, const glm::vec3& color, const glm::vec2& texCoord, const glm::vec3& normal) {
        positions.push_back(position);
        colors.push_back(color);
        texCoords.push_back(texCoord);
        normals.push_back(normal);
    }

    void addVertex(const glm::vec3& position) {
        positions.push_back(position);
        colors.push_back(glm::vec3(0.0, 0.0, 0.0));
        texCoords.push_back(glm::vec2(0.0, 0.0));
        normals.push_back(glm::vec3(0.0, 0.0, 0.0));
    }

    void addIndex(unsigned int index) {
        indices.push_back(index);
    }

    void addIndices(std::vector<unsigned int> other) {
        indices.insert(indices.end(), other.begin(), other.end());
    }
};

struct ModelInstance
{
    ModelAsset model;
    Transform transform;

    void setColor(glm::vec3 color) {
        for (auto & it : model.colors) {
            it = color;
        }
    }
};

enum MeshBufferPositions
{
	POSITION_VB,
	COLOR_VB,
	TEXCOORD_VB,
	NORMAL_VB,
	INDEX_VB
};

class Mesh
{
	public:
	    Mesh();
	    Mesh(ModelAsset model);

		~Mesh();

		void draw();

	private:

		static const unsigned int NUM_BUFFERS = 5;
        GLenum m_primitiveType;
		GLuint m_vertexArrayObject;
		GLuint m_vertexArrayBuffers[NUM_BUFFERS];
		unsigned int m_numIndices;
};

#endif
