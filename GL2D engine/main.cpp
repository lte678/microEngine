#include "src/graphics/window.h"
#include "src/math/vector.h"

#include "src/graphics/shader.h"

#include "src/graphics/layers/tilelayer.h"
#include "src/graphics/sprite.h"

#include <time.h>
#include "src/utils/timer.h"

int main() {
	using namespace sparky;
	using namespace graphics;
	using namespace math;

	

	Window window("GL program", 960, 540);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	mat4 ortho = mat4::orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);

	std::cout << ortho << std::endl;

	Shader shader("src/shaders/default.vert", "src/shaders/default.frag");
	shader.setUniform2f("light_pos", vec2(4.0f, 1.5f));

	TileLayer layer(&shader);

	for (float y = -9.0f; y < 9.0f; y += 0.1f) {
		for (float x = -16.0f; x < 16.0f; x += 0.1f) {
			layer.add(new Sprite(x, y, 0.08f, 0.08f, math::vec4(0.2f, 0.2f, 0.6f, 1.0f)));
		}
	}


	Timer currentTime;

	double x, y;
	int frames = 0;
	float timer = 0.0f;

	while (!window.closed()) {

		window.clear();
		window.getMousePosition(x, y);
		shader.setUniform2f("light_pos", vec2(x / 30 - 16, 9 - (y / 30)));

		layer.render();

		frames++;
		if (currentTime.elapsed() - timer > 1.0f) {
			timer += 1.0f;
			printf("%d fps\n", frames);
			frames = 0;
		}
		window.update();
	}

	return 0;
}