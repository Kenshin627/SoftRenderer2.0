#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>
Camera::Camera(const glm::vec3& eye, const glm::vec3& center, const glm::vec3& up):
	position(eye),
	view(glm::identity<glm::mat4>()),
	projection(glm::identity<glm::mat4>()),
	viewProjection(glm::identity<glm::mat4>())
{
	ConstructViewMatrix(eye, center, up);
}

void Camera::ConstructViewMatrix(const glm::vec3& eye, const glm::vec3& center, const glm::vec3& up)
{
	glm::vec3 z = glm::normalize(eye - center);
	glm::vec3 x = glm::cross(glm::normalize(up), z);
	glm::vec3 y = glm::cross(z, x);

	glm::mat4 rotation = {
		{ x,       0 },
		{ y,       0 },
		{ z,       0 },
		{ 0, 0, 0, 1 }
	};

	glm::mat4 translate = {
		{ 1,     0,     0,     0 },
		{ 0,     1,     0,     0 },
		{ 0,     0,     1,     0 },
		{ eye.x, eye.y, eye.z, 1 }
	};

	
	//view = invert(translate * rotation) = invert(rotation) * invert(translate)
	//invRotation = transpose(rotation)
	glm::mat4 invRotation = {
		{ x.x, y.x, z.x, 0 },
		{ x.y, y.y, z.y, 0 },
		{ x.z, y.z, z.z, 0 },
		{ 0,   0,   0,   1 }
	};

	glm::mat4 invTranslate = {
		{ 1,      0,      0,      0 },
		{ 0,      1,      0,      0 },
		{ 0,      0,      1,      0 },
		{ -eye.x, -eye.y, -eye.z, 1 }
	};

	view = invRotation * invTranslate;
}

void Perpective(float fov, float aspect, float near, float far)
{
	
}