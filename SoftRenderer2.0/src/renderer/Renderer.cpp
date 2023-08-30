#include "Renderer.h"
#include "../window/Window.h"

void Renderer::SetDrawHandle(Window* win)
{
	winHandle = win;
}

void Renderer::Draw()
{
	Rasterize();
}

void Renderer::Rasterize()
{
	std::array<glm::vec4, 4> screenSpaceVertices;
	for (size_t i = 0; i < 3; i++)
	{
		screenSpaceVertices[i] = viewport.transform * triangleVertices[i];
	}
	BoundingBox bbox = CalcBoundingBox(screenSpaceVertices.data());
	for (size_t y = bbox.min.y; y <= bbox.max.y; y++)
	{
		for (size_t x = bbox.min.x; x <= bbox.max.x; x++)
		{
			glm::vec2 p { x + 0.5f, y + 0.5f };
			glm::vec3 baryCentric = BaryCentric(screenSpaceVertices.data(), p);
			if (baryCentric.x <0 || baryCentric.y < 0 || baryCentric.z < 0)
			{
				continue;
			}
			winHandle->DrawPoint(p.x, p.y, drawColor);
		}
	}
}

BoundingBox Renderer::CalcBoundingBox(glm::vec4* triangleVertices)
{
	BoundingBox bbox;
	glm::vec2 min { 0, 0 };
	glm::vec2 max { viewport.width - 1, viewport.height - 1 };
	bbox.min = min;
	bbox.max = max;
	
	for (size_t i = 0; i < 3; i++)
	{
		bbox.min.x = glm::min(bbox.min.x, triangleVertices[i].x);
		bbox.min.y = glm::min(bbox.min.y, triangleVertices[i].y);
		bbox.max.x = glm::max(bbox.max.x, triangleVertices[i].x);
		bbox.max.y = glm::max(bbox.max.y, triangleVertices[i].y);
	}

	bbox.min.x = glm::max(min.x, bbox.min.x);
	bbox.min.y = glm::max(min.y, bbox.min.y);
	bbox.max.x = glm::min(max.x, bbox.max.x);
	bbox.max.y = glm::min(max.y, bbox.max.y);
	return bbox;
}

glm::vec3 Renderer::BaryCentric(const glm::vec4* triangleVertices, const glm::vec2& p)
{
	glm::vec2 v0 { triangleVertices[0] };
	glm::vec2 v1 { triangleVertices[1] };
	glm::vec2 v2 { triangleVertices[2] };

	glm::vec2 v01 = v1 - v0;
	glm::vec2 v02 = v2 - v0;
	glm::vec2 vp0 = v0 - p;
	glm::vec3 vwz = glm::cross(glm::vec3(v01.x, v02.x, vp0.x), glm::vec3(v01.y, v02.y, vp0.y));
	if (vwz.z < 1e-2)
	{
		return { -1, 1, 1 };
	}
	float v = vwz.x / vwz.z;
	float w = vwz.y / vwz.z;
	float u = 1.0 - (v + w);
	return { u, v, w };
}

void Renderer::SetViewport(uint32_t x, uint32_t y, uint32_t w, uint32_t h)
{
	viewport.Set(x, y, w, h);
}



