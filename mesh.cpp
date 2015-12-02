#include "mesh.h"
#include <map>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <stdlib.h>

#include <glm/gtc/type_ptr.hpp>

Mesh::Mesh(ModelAsset model)
{
	m_instanceCount = 0;
	m_primitiveType = model.primitiveType;
    m_numIndices = model.indices.size();

    glGenVertexArrays(1, &m_vertexArrayObject);
	glBindVertexArray(m_vertexArrayObject);

	glGenBuffers(NUM_BUFFERS, m_vertexArrayBuffers);
	
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[POSITION_VB]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(model.positions[0]) * model.positions.size(), &model.positions[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[COLOR_VB]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(model.colors[0]) * model.colors.size(), &model.colors[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glVertexAttribDivisor(0, 1);

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[TEXCOORD_VB]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(model.texCoords[0]) * model.texCoords.size(), &model.texCoords[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[NORMAL_VB]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(model.normals[0]) * model.normals.size(), &model.normals[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, 0);	

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vertexArrayBuffers[INDEX_VB]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(model.indices[0]) * model.indices.size(), &model.indices[0], GL_STATIC_DRAW);

	glBindVertexArray(0);
}

void Mesh::addInstance(glm::mat4 model) {
	m_instanceCount++;
	m_modelMatrices.push_back(model);		
}

Mesh::~Mesh()
{
	glDeleteBuffers(NUM_BUFFERS, m_vertexArrayBuffers);
	glDeleteVertexArrays(1, &m_vertexArrayObject);
}

void printMat4(std::string str, glm::mat4 mat) {
	printf("%s\n", str.c_str());
	const float *pSource = (const float*)glm::value_ptr(mat);
	for (int i = 0; i < 16; ++i) {
		if (i % 4 == 0) printf("\n");
	    printf("%f ", pSource[i]);
	}
}

void Mesh::draw()
{
	glBindBuffer(GL_ARRAY_BUFFER, m_modelMatrixBuffer);
	for (int i = 0; i < 4; i++)
	{
		glVertexAttribPointer(4 + i, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void *)(sizeof(glm::vec4) * i));
		glEnableVertexAttribArray(4 + i);
		glVertexAttribDivisor(4 + i, 1);
	}
	glBufferData(GL_ARRAY_BUFFER, m_modelMatrices.size(), m_modelMatrices.data(), GL_STATIC_DRAW);

	if (m_instanceCount) {
		glBindVertexArray(m_vertexArrayObject);
		glDrawElementsInstanced(m_primitiveType, m_numIndices, GL_UNSIGNED_INT, 0, m_instanceCount);
		glBindVertexArray(0);
	}
}


