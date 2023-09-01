#pragma once
#include <glm/glm.hpp>

struct Vertex
{
	Vertex() = default;
	Vertex(const glm::vec4& p, const glm::vec3& c) :Position(p), Color(c) {}
	glm::vec4 Position;
	glm::vec3 Color;
};