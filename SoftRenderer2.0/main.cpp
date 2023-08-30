#include "src/window/Window.h"
#include <glm/gtc/type_ptr.hpp>

int main(int argc, char* argv[])
{
	uint32_t width  = 800;
	uint32_t height = 600;
	Renderer renderer;
	renderer.SetViewport(0, 0, width, height);

	Window win{ "SoftRenderer", width, height };
	win.SetRenderer(&renderer);
	renderer.SetDrawHandle(&win);
	win.Run();
	win.ShutDowm();
	return 0;
}