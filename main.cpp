#include <iostream>
#include <cmath>
#include <SDL2/SDL.h>

#include "display.h"
#include "shader.h"
#include "mesh.h"
#include "texture.h"
#include "transform.h"
#include "camera.h"

#define DISPLAY_WIDTH 800
#define DISPLAY_HEIGHT 600

Mesh createAxis();
Mesh createWireOoctahedron();
Mesh createSolidOoctahedron();

// void draw() {
// // 	std::vector<Mesh> meshes;

// 	Mesh axis = createAxis();
// 	axis.transform()

// 	Mesh octahedron = createSolidOoctahedron();
// }

int main(int argc, char const *argv[])
{
	Display display(DISPLAY_WIDTH, DISPLAY_HEIGHT, "Labs");
	ShaderProgram shaderProgram("./resourses/shaders/newShader");
	Texture texture("./resourses/textures/bricks.jpg");
	Transform transform;
	Camera camera(  glm::vec3(0.0f, 0.5f, 1.0f), 				// position
					glm::vec3(0.0f, 0.0f, -1.0f), 				// lookAt
					glm::vec3(0.0f, 1.0f, 0.0f), 				// up
				 	70.0f, 										// fovy
				 	(float)DISPLAY_WIDTH/(float)DISPLAY_HEIGHT, // aspect
				 	0.1f, 										// zNear
				 	100.0f);									// zFar
	
	Mesh axis = createAxis();
	Transform axisTransform;
	// axisTransform.setPos(glm::vec3(0.1, 0.1, 0.1));
	axis.addInstance(axisTransform.getModel());
	// Mesh octahedron = createSolidOoctahedron();
	
	bool stateMachine = false;

	float motion_x = 0.0f;
	float motion_y = 0.0f;
	float scale = 1.0f;

	int x = 0, y = 0;

	// SDL_SetRelativeMouseMode(SDL_TRUE);
	SDL_Event event;

	bool isRunning = true;

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
       				if (event.key.keysym.sym == SDLK_UP) {
       					camera.moveForward(0.1f);
       				} else if (event.key.keysym.sym == SDLK_DOWN) {
       					camera.moveForward(-0.1f);
       				} else if (event.key.keysym.sym == SDLK_LEFT) {
       					camera.moveRight(-0.1f);
       				} else if (event.key.keysym.sym == SDLK_RIGHT) {
       					camera.moveRight(0.1f);
       				} else if (event.key.keysym.sym == SDLK_d) {
       					camera.yaw(-10.0f);
       				} else if (event.key.keysym.sym == SDLK_a) {
       					camera.yaw(10.0f);
       				} 
            		break;

				case SDL_MOUSEWHEEL: 
					if (event.wheel.y >= 0){  
						scale += 0.01;
					} else {
						scale -= 0.01;
					}
					break;

	            case SDL_MOUSEBUTTONDOWN:
	            {
	                if(event.button.button == SDL_BUTTON_LEFT)
	                {
	                    if(stateMachine == false)
	                    {
	                        stateMachine = true;
	                        SDL_GetMouseState(&x, &y);
	                    }
	                }
	                break;
	            }
	            case SDL_MOUSEMOTION:
	            {

	            	if (event.motion.xrel > 0) {
	            		camera.yaw(-1.0f);
	            	} else if (event.motion.xrel < 0) {
	            		camera.yaw(1.0f);
	            	} 
	            	if (event.motion.yrel > 0) {
	            		
	            	} else if (event.motion.yrel < 0) {
	            		
	            	}

	                if(stateMachine == true)
	                {
	                    motion_x += event.motion.x - x;
	                    motion_y += event.motion.y - y;
	                    break;
	                }
	            }
	            case SDL_MOUSEBUTTONUP:
	            {
	                if(event.button.button == SDL_BUTTON_LEFT)
	                {
	                	float motion_x = 0.0f;
						float motion_y = 0.0f;
	                    if(stateMachine != false)
	                    {
	                        stateMachine = false;
	                    }
	                }
	            }
                default:
                    break;
            }
		}
		
		transform.setScale(glm::vec3(1.0 * scale, 1.0 * scale , 1.0 * scale ));

		shaderProgram.bind();
		shaderProgram.update(camera.getView(), camera.getProjection());
		
		axis.draw();

		// texture.bind();
		// octahedron.draw();

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
	model.addVertex(glm::vec3(0.0, 1.0, 0.0), glm::vec3(0.0, 0.0, 0.0), glm::vec2(0.5, 1.0), glm::vec3(0.0, 1.0, 0.0));

	model.addVertex(glm::vec3(1.0, 0.0, 0.0), glm::vec3(0.0, 0.0, 0.0), glm::vec2(1.0, 0.0), glm::vec3(1.0, 0.0, 0.0));
	model.addVertex(glm::vec3(1.0, 0.0, 0.0), glm::vec3(0.0, 0.0, 0.0), glm::vec2(0.0, 0.0), glm::vec3(1.0, 0.0, 0.0));
	

	model.addVertex(glm::vec3(0.0, 0.0, 1.0), glm::vec3(0.0, 0.0, 0.0), glm::vec2(1.0, 0.0), glm::vec3(0.0, 0.0, 1.0));
	model.addVertex(glm::vec3(0.0, 0.0, 1.0), glm::vec3(0.0, 0.0, 0.0), glm::vec2(0.0, 0.0), glm::vec3(0.0, 0.0, 1.0));

	model.addVertex(glm::vec3(-1.0, 0.0, 0.0), glm::vec3(0.0, 0.0, 0.0), glm::vec2(1.0, 0.0), glm::vec3(-1.0, 0.0, 0.0));
	model.addVertex(glm::vec3(-1.0, 0.0, 0.0), glm::vec3(0.0, 0.0, 0.0), glm::vec2(0.0, 0.0), glm::vec3(-1.0, 0.0, 0.0));

	model.addVertex(glm::vec3(0.0, 0.0, -1.0), glm::vec3(0.0, 0.0, 0.0), glm::vec2(1.0, 0.0), glm::vec3(0.0, 0.0, -1.0));
	model.addVertex(glm::vec3(0.0, 0.0, -1.0), glm::vec3(0.0, 0.0, 0.0), glm::vec2(0.0, 0.0), glm::vec3(0.0, 0.0, -1.0));

	// DOWN
	model.addVertex(glm::vec3(0.0, -1.0, 0.0), glm::vec3(0.0, 0.0, 0.0), glm::vec2(0.5, 1.0), glm::vec3(0.0, -1.0, 0.0));

	std::vector<unsigned int> indices = {
		2, 0, 3,	4, 0, 5,	6, 0, 7,	8, 0, 1,
		9, 2, 3,	9, 4, 5,	9, 6, 7,	9, 8, 1,
	};

	model.addIndices(indices);	

	model.primitiveType = GL_TRIANGLES;

	return Mesh(model);
}


