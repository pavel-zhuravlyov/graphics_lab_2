#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <iostream>

struct Camera
{
public:
	Camera(const glm::vec3& position, const glm::vec3& lookAt, const glm::vec3& up, float fov, float aspect, float zNear, float zFar)
	{
		this->position = position;
		this->lookAt = lookAt;
		this->up = glm::normalize(up);
		// this->forward = glm::normalize(lookAt - position);
		// this->right = glm::normalize(glm::cross(forward, up));
		this->projection = glm::perspective(fov, aspect, zNear, zFar);
	}

	inline glm::mat4 getViewProjection() const
	{
		return projection * glm::lookAt(position, lookAt, up);
	}

	void moveForward(float amount)
	{
		position += glm::normalize(lookAt - position) * amount;
	}

	void moveRight(float amount)
	{
		position += glm::normalize(glm::cross(glm::normalize(lookAt - position), up)) * amount;
		lookAt += glm::normalize(glm::cross(glm::normalize(lookAt - position), up)) * amount;
	}

	void yaw(float angle)
	{
		glm::mat4 rotation = glm::rotate(angle, glm::vec3(0.0, 1.0, 0.0));
		glm::vec3 delta = glm::vec3(lookAt.x, 0.0, lookAt.z) - glm::vec3(position.x, 0.0, position.z);
		glm::vec3 rotated = glm::vec3(rotation * glm::vec4(delta, 0.0)) + glm::vec3(position.x, 0.0, position.z);
		lookAt = glm::vec3(rotated.x, lookAt.y, rotated.z);
	}

	// void pitch(float angle) {
	// 	glm::mat4 rotation = glm::rotate(angle, up);

	// 	lookAt = glm::vec3(glm::normalize(rotation * glm::vec4(lookAt, 0.0)));
	// 	up = glm::vec3(glm::normalize(rotation * glm::vec4(up, 0.0)));
	// }

	// void changePitch(float angle) {
 //    	glm::vec3 right = glm::normalize(glm::cross(glm::normalize(lookAt - position), up));
 //    	glm::vec3 forward = glm::normalize(lookAt - position);

	// 	forward = glm::vec3(glm::normalize(glm::rotate(angle, right) * glm::vec4(forward, 0.0)));
	// 	up = glm::normalize(glm::cross(forward, right));
	// 	lookAt = glm::normalize(forward + position);
	// }

	void printVec3(std::string str, glm::vec3 vec) {
		printf("%s: %f %f %f\n", str.c_str(), vec.x, vec.y, vec.z);
	}

private:
	glm::mat4 projection;

	glm::vec3 position;
	glm::vec3 lookAt;
	glm::vec3 up;

	// glm::vec3 forward;
	// glm::vec3 right;
};

#endif
