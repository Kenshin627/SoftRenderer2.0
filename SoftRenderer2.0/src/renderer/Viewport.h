#pragma once
#include <cstdint>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

struct Viewport
{
	Viewport() = default;
	Viewport(uint32_t x, uint32_t y, uint32_t w, uint32_t h):width(w), height(h)
	{
		Set(x, y, w, h);
	}
	void Set(uint32_t x, uint32_t y, uint32_t w, uint32_t h)
	{
		width  = w;
		height = h;
		transform =
		{
			{ w / 2,         0,              0, 0 },
			{ 0,             h / 2,          0, 0 },
			{ 0,             0,              1, 0 },
			{ width / 2 + x, height / 2 + y, 0, 1 },
		};
	}

	uint32_t width = 0;
	uint32_t height = 0;
	glm::mat4 transform = glm::identity<glm::mat4>();
};