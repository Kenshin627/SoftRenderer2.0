#pragma once
#include "Viewport.h"
#include "BoundingBox.h"
#include <array>

class Window;
class Renderer
{
public:
	Renderer() = default;
	~Renderer() = default;
	void SetDrawHandle(Window* win);
	void Draw();
	void Rasterize();
	BoundingBox CalcBoundingBox(glm::vec4* triangleVertices);
	glm::vec3 BaryCentric(const glm::vec4* triangleVertices, const glm::vec2& p);
	void SetViewport(uint32_t x, uint32_t y, uint32_t w, uint32_t h);
private:
	Viewport viewport{};
	Window* winHandle = nullptr;
	std::array<glm::vec4, 3> triangleVertices = { 
		glm::vec4( -0.5f, -0.5f, 0.0f, 1.0f),
		glm::vec4(  0.5f, -0.5f, 0.0f, 1.0f),
		glm::vec4(  0.0f,  0.5f, 0.0f, 1.0f)
	};
	glm::vec3 drawColor { 230, 80, 50 };
};