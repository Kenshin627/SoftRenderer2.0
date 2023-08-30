#pragma once
#include <glm/glm.hpp>

struct BoundingBox
{
	BoundingBox() = default;
	BoundingBox(const glm::vec2& min, const glm::vec2& max) :min(min), max(max) {}

	glm::vec2 min;
	glm::vec2 max;
};