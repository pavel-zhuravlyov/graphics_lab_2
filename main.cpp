#include <iostream>
#include <cmath>
#include <SDL2/SDL.h>
#include <glm/gtc/type_ptr.hpp>

#include "display.h"
#include "shader.h"
#include "mesh.h"
#include "texture.h"
#include "transform.h"
#include "camera.h"

#define DISPLAY_WIDTH 1280
#define DISPLAY_HEIGHT 720

Mesh createAxis();
Mesh createWireOoctahedron();
Mesh createSolidOoctahedron();

Mesh createFloorMesh();
Mesh createWallsMesh();

// void draw() {
// // 	std::vector<Mesh> meshes;

// 	Mesh axis = createAxis();
// 	axis.transform()

// 	Mesh octahedron = createSolidOoctahedron();
// }

// void printMat4(std::string str, glm::mat4 mat) {
// 	printf("%s\n", str.c_str());
// 	const float *pSource = (const float*)glm::value_ptr(mat);
// 	for (int i = 0; i < 16; ++i) {
// 		if (i % 4 == 0) printf("\n");
// 		printf("%f ", pSource[i]);
// 	}
// }

int main(int argc, char const *argv[])
{
	Display display(DISPLAY_WIDTH, DISPLAY_HEIGHT, "Labs");
	ShaderProgram shaderProgram("./resourses/shaders/newShader");
	Texture bricks("./resourses/textures/bricks0.jpg");
	Texture white("./resourses/textures/white.jpg");
	Transform transform;


	glm::vec3 forward = glm::vec3(0.0f, 0.0f, -1.0f);
	Camera camera(  glm::vec3(1.0f, 1.0f, 1.0f), 				// position
					forward, 									// forward
					glm::vec3(0.0f, 1.0f, 0.0f), 				// up
				 	70.0f, 										// fovy
				 	(float)DISPLAY_WIDTH/(float)DISPLAY_HEIGHT, // aspect
				 	0.1f, 										// zNear
				 	100.0f);									// zFar

	Mesh axis = createAxis();
	// Mesh wireOctahedron = createWireOoctahedron();
	// Mesh solidOctahedron = createSolidOoctahedron();

	// Mesh floorMesh = createFloorMesh();
	// Mesh wallsMesh = createWallsMesh();

	// meshTransform.setPos(glm::vec3(0.0, 0.0, 0.0));
	// meshTransform.setScale(glm::vec3(10.0, 10.0, 10.0));
	// axis.addInstance(meshTransform.getModel());

	// meshTransform.setPos(glm::vec3(1.0, 0.5, 1.0));
	// meshTransform.setScale(glm::vec3(1.0, 1.0, 1.0));
	// wireOctahedron.addInstance(meshTransform.getModel());

	// meshTransform.setPos(glm::vec3(5.0, 2.0, 5.0));
	// solidOctahedron.addInstance(meshTransform.getModel());


	glm::vec3 ambient =  glm::vec3(1.0, 1.0, 1.0);
	glm::vec3 lightDirection = glm::vec3(-1.0, -1.0, -1.0);
	glm::vec3 halfVector = glm::normalize(lightDirection + forward);
	float shininess = 1.0;
	float strength = 1.0;
	
	SDL_SetRelativeMouseMode(SDL_TRUE);
	SDL_Event event;
	bool isRunning = true;
	float scale = 1.0f;

	while(isRunning)
	{
		display.clear(0.0f, 0.0f, 0.0f, 1.0f);

		while(SDL_PollEvent(&event))
		{
			switch( event.type ){
				case SDL_QUIT:
					isRunning = false;
					break;

				case SDL_KEYDOWN:
					if (event.key.keysym.sym == SDLK_w) {
						camera.moveForward(0.1f);
					} else if (event.key.keysym.sym == SDLK_s) {
						camera.moveForward(-0.1f);
					} else if (event.key.keysym.sym == SDLK_a) {
						camera.moveRight(-0.1f);
					} else if (event.key.keysym.sym == SDLK_d) {
						camera.moveRight(0.1f);
					} 
					break;

				case SDL_MOUSEWHEEL: 
					if (event.wheel.y > 0) {  
						scale += 0.01f;
					} else if (event.wheel.y < 0) {
						scale -= 0.01f;
					}
					break;

	            case SDL_MOUSEMOTION:
	            	if (event.motion.xrel > 0) {
	            		camera.yaw(-0.5f);
	            	} else if (event.motion.xrel < 0) {
	            		camera.yaw(0.5f);
	            	} 
	         		if (event.motion.yrel > 0) {
	            		camera.pitch(-0.5f);
	            	} else if (event.motion.yrel < 0) {
	            		camera.pitch(0.5f);
	            	}
	            	break;

                default:
                    break;
            }
		}

		// transform.setScale(glm::vec3(1.0 * scale, 1.0 * scale , 1.0 * scale ));

		shaderProgram.bind();
		shaderProgram.update(transform.getModel(), camera.getView(), camera.getProjection(),
                            ambient, lightDirection, halfVector, shininess, strength);

		white.bind();
		axis.draw();

		// bricks.bind();
		// floorMesh.draw();
		// wallsMesh.draw();

		// solidOctahedron.draw();

		display.swapBuffers();
		SDL_Delay(1);

	}

	return 0;
}

Mesh createAxis() {
	ModelAsset model;

	model.addVertex(glm::vec3(0.0, 0.0, 0.0), glm::vec3(1.0, 0.0, 0.0), glm::vec2(0.0, 0.0), glm::vec3(0.0, 0.0, 0.0));
	model.addVertex(glm::vec3(1.0, 0.0, 0.0), glm::vec3(1.0, 0.0, 0.0), glm::vec2(0.0, 0.0), glm::vec3(0.0, 0.0, 0.0));

	model.addVertex(glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0), glm::vec2(0.0, 0.0), glm::vec3(0.0, 0.0, 0.0));
	model.addVertex(glm::vec3(0.0, 1.0, 0.0), glm::vec3(0.0, 1.0, 0.0), glm::vec2(0.0, 0.0), glm::vec3(0.0, 0.0, 0.0));

	model.addVertex(glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 0.0, 1.0), glm::vec2(0.0, 0.0), glm::vec3(0.0, 0.0, 0.0));
	model.addVertex(glm::vec3(0.0, 0.0, 1.0), glm::vec3(0.0, 0.0, 1.0), glm::vec2(0.0, 0.0), glm::vec3(0.0, 0.0, 0.0));

	std::vector<unsigned int> indices = {
		0, 1, 2, 3, 4, 5, 
	};

	model.addIndices(indices);	

	model.primitiveType = GL_LINES;

	return Mesh(model);
}

Mesh createWireOoctahedron() {
	ModelAsset model;

	model.addVertex(glm::vec3(1.0, 0.0, 0.0), glm::vec3(1.0, 1.0, 0.0), glm::vec2(0.0, 0.0), glm::vec3(1.0, 0.0, 0.0));
	model.addVertex(glm::vec3(0.0, 1.0, 0.0), glm::vec3(1.0, 1.0, 0.0), glm::vec2(0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
	model.addVertex(glm::vec3(0.0, 0.0, 1.0), glm::vec3(1.0, 1.0, 0.0), glm::vec2(0.0, 0.0), glm::vec3(0.0, 0.0, 1.0));
	model.addVertex(glm::vec3(-1.0, 0.0, 0.0), glm::vec3(1.0, 1.0, 0.0), glm::vec2(0.0, 0.0), glm::vec3(-1.0, 0.0, 0.0));
	model.addVertex(glm::vec3(0.0, -1.0, 0.0), glm::vec3(1.0, 1.0, 0.0), glm::vec2(0.0, 0.0), glm::vec3(0.0, -1.0, 0.0));
	model.addVertex(glm::vec3(0.0, 0.0, -1.0), glm::vec3(1.0, 1.0, 0.0), glm::vec2(0.0, 0.0), glm::vec3(0.0, 0.0, -1.0));

	std::vector<unsigned int> indices = {
		0, 1, 2, 1, 3, 1, 5, 1, 4, 0, 4, 2, 4, 3, 4, 5, 0, 2, 2, 3, 3, 5, 5, 0
	};

	model.addIndices(indices);	

	model.primitiveType = GL_LINES;

	return Mesh(model);
}

Mesh createSolidOoctahedron() {
	ModelAsset model;

	// UP
	model.addVertex(glm::vec3(0.0, 1.0, 0.0), glm::vec3(1.0, 1.0, 1.0), glm::vec2(0.5, 1.0), glm::vec3(0.0, 1.0, 0.0));

	model.addVertex(glm::vec3(1.0, 0.0, 0.0), glm::vec3(1.0, 1.0, 1.0), glm::vec2(1.0, 0.0), glm::vec3(1.0, 0.0, 0.0));
	model.addVertex(glm::vec3(1.0, 0.0, 0.0), glm::vec3(1.0, 1.0, 1.0), glm::vec2(0.0, 0.0), glm::vec3(1.0, 0.0, 0.0));

	model.addVertex(glm::vec3(0.0, 0.0, 1.0), glm::vec3(1.0, 1.0, 1.0), glm::vec2(1.0, 0.0), glm::vec3(0.0, 0.0, 1.0));
	model.addVertex(glm::vec3(0.0, 0.0, 1.0), glm::vec3(1.0, 1.0, 1.0), glm::vec2(0.0, 0.0), glm::vec3(0.0, 0.0, 1.0));

	model.addVertex(glm::vec3(-1.0, 0.0, 0.0), glm::vec3(1.0, 1.0, 1.0), glm::vec2(1.0, 0.0), glm::vec3(-1.0, 0.0, 0.0));
	model.addVertex(glm::vec3(-1.0, 0.0, 0.0), glm::vec3(1.0, 1.0, 1.0), glm::vec2(0.0, 0.0), glm::vec3(-1.0, 0.0, 0.0));

	model.addVertex(glm::vec3(0.0, 0.0, -1.0), glm::vec3(1.0, 1.0, 1.0), glm::vec2(1.0, 0.0), glm::vec3(0.0, 0.0, -1.0));
	model.addVertex(glm::vec3(0.0, 0.0, -1.0), glm::vec3(1.0, 1.0, 1.0), glm::vec2(0.0, 0.0), glm::vec3(0.0, 0.0, -1.0));

	// DOWN
	model.addVertex(glm::vec3(0.0, -1.0, 0.0), glm::vec3(1.0, 1.0, 1.0), glm::vec2(0.5, 1.0), glm::vec3(0.0, -1.0, 0.0));

	std::vector<unsigned int> indices = {
		2, 0, 3,	4, 0, 5,	6, 0, 7,	8, 0, 1,
		9, 2, 3,	9, 4, 5,	9, 6, 7,	9, 8, 1,
	};

	model.addIndices(indices);	

	model.primitiveType = GL_TRIANGLES;

	return Mesh(model);
}

Mesh createFloorMesh() {
	ModelAsset model;

	model.addVertex(glm::vec3(0.0, 0.0, 0.0), glm::vec3(1.0, 1.0, 1.0), glm::vec2(0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
	model.addVertex(glm::vec3(1.0, 0.0, 0.0), glm::vec3(1.0, 1.0, 1.0), glm::vec2(1.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
	model.addVertex(glm::vec3(0.0, 0.0, 1.0), glm::vec3(1.0, 1.0, 1.0), glm::vec2(0.0, 1.0), glm::vec3(0.0, 1.0, 0.0));
	model.addVertex(glm::vec3(1.0, 0.0, 1.0), glm::vec3(1.0, 1.0, 1.0), glm::vec2(1.0, 1.0), glm::vec3(0.0, 1.0, 0.0));

	std::vector<unsigned int> indices = {
		0, 3, 1, 0, 2, 3,
	};

	model.addIndices(indices);	

	model.primitiveType = GL_TRIANGLES;

	Transform transform;

	Mesh mesh(model);

	for (int i = 0; i < 10; ++i) {
		for (int j = 0; j < 10; ++j) {
			transform.setPos(glm::vec3(i, 0, j));
			mesh.addInstance(transform.getModel());
		}
	}

	return mesh;
}

Mesh createWallsMesh() {
	ModelAsset model;

	model.addVertex(glm::vec3(0.0, 0.0, 0.0), glm::vec3(1.0, 1.0, 1.0), glm::vec2(0.0, 0.0), glm::vec3(0.0, 0.0, 1.0));
	model.addVertex(glm::vec3(1.0, 0.0, 0.0), glm::vec3(1.0, 1.0, 1.0), glm::vec2(1.0, 0.0), glm::vec3(0.0, 0.0, 1.0));
	model.addVertex(glm::vec3(0.0, 1.0, 0.0), glm::vec3(1.0, 1.0, 1.0), glm::vec2(0.0, 1.0), glm::vec3(0.0, 0.0, 1.0));
	model.addVertex(glm::vec3(1.0, 1.0, 0.0), glm::vec3(1.0, 1.0, 1.0), glm::vec2(1.0, 1.0), glm::vec3(0.0, 0.0, 1.0));

	std::vector<unsigned int> indices = {
		0, 3, 1, 0, 2, 3,
	};

	model.addIndices(indices);	

	model.primitiveType = GL_TRIANGLES;

	Transform transform;

	Mesh mesh(model);

	int width = 5;
	int height = 5;

	for (int i = 0; i < width; ++i) {
		for (int j = 0; j < height; ++j) {
			transform.setPos(glm::vec3(width, height, 0));
			transform.setRot(glm::vec3(0, 0, 0));
			mesh.addInstance(transform.getModel());			

			// transform.setPos(glm::vec3(j, i, 10));
			// transform.setRot(glm::vec3(0, 180, 0));
			// mesh.addInstance(transform.getModel());

			// transform.setPos(glm::vec3(0, j, i));
			// transform.setRot(glm::vec3(0, 270, 0));
			// mesh.addInstance(transform.getModel());

			// transform.setPos(glm::vec3(10, i, j));
			// transform.setRot(glm::vec3(0, 90, 0));
			// mesh.addInstance(transform.getModel());
		}
	}

	return mesh;
}