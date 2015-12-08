#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <iostream>

struct Camera
{
public:
	Camera(const glm::vec3& position, const glm::vec3& forward, const glm::vec3& up, float fov, float aspect, float zNear, float zFar)
	{
		this->position = position;
		this->up = glm::normalize(up);
		this->forward = glm::normalize(forward);
		// this->right = glm::normalize(glm::cross(forward, up));
		this->projection = glm::perspective(fov, aspect, zNear, zFar);
	}

	inline glm::mat4 getView() const
	{
		return glm::lookAt(position, position + forward, up);
	}

	inline glm::mat4 getProjection() const
	{
		return projection;
	}

	void moveForward(float amount)
	{
		position += forward * amount;
	}

	void moveRight(float amount)
	{
		position += glm::normalize(glm::cross(forward, up)) * amount;
	}

	void yaw(float angle)
	{
		glm::mat4 rotation = glm::rotate(angle, up);
		forward = glm::vec3(glm::normalize(rotation * glm::vec4(forward, 0.0)));
	}

	void pitch(float angle)
	{
		glm::vec3 right = glm::normalize(glm::cross(forward, up));
		forward = glm::vec3(glm::normalize(glm::rotate(angle, right) * glm::vec4(forward, 0.0)));
	}

	void printVec3(std::string str, glm::vec3 vec) {
		printf("%s: %f %f %f\n", str.c_str(), vec.x, vec.y, vec.z);
	}

private:
	glm::mat4 projection;

	glm::vec3 position;
	glm::vec3 up;
	glm::vec3 forward;
};

#endif
