#include "src/graphics/window.h"
#include "src/math/vector.h"

#include "src/graphics/shader.h"

#include "src/utils/timer.h"

#include "src/graphics/layers/tilelayer.h"
#include "src/graphics/sprite.h"

#include "src/graphics/layers/group.h"
#include "src/graphics/texture.h"
#include "src/graphics/label.h"


int main() {
	using namespace sparky;
	using namespace graphics;
	using namespace math;

	

	Window window("GL program", 960, 540);

	mat4 ortho = mat4::orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);

	Shader shader("src/shaders/default.vert", "src/shaders/default.frag");
	Shader unlit("src/shaders/unlit.vert", "src/shaders/unlit.frag");

	TileLayer layer(&shader);
	TileLayer ui(&unlit);


	Group* scene = new Group(mat4::translation(vec3(-15.0f, 2.0f, 0.0f)));
	Group* fpsCounterGroup = new Group(mat4::translation(vec3(-15.0f, 8.0f, 0.0f)));
	Group* background = new Group(mat4::translation(vec3(0, 0, 0)));

	Texture texture1("biohazard.png");
	Texture texture2("checkered.jpg");
	Texture sparkyLogo("sparky.png");

	Label fpsCounter("0 fps", 0.0f, 0.0f, vec4(1, 1, 1, 1));
	Sprite fpsCounterBackdrop(-0.3f, -0.3f, 3.5f, 1.2f, vec4(0, 0, 0, 0.3f));

	scene->add(new Sprite(0, 0, 6, 6, &texture1));
	scene->add(new Sprite(6, 0, 6, 6, &texture2));
	
	fpsCounterGroup->add(&fpsCounterBackdrop);
	fpsCounterGroup->add(&fpsCounter);

	background->add(new Sprite(-16, -9, 32, 18, &sparkyLogo));

	layer.add(scene);
	ui.add(fpsCounterGroup);
	ui.add(background);

	GLint texIDs[] = {
		0, 1, 2, 3, 4, 5, 6, 7, 8, 9
	};

	shader.enable();
	shader.setUniform1iv("textures", texIDs, 10);
	unlit.enable();
	unlit.setUniform1iv("textures", texIDs, 10);

	Timer currentTime;

	double x, y;
	int frames = 0;
	float timer = 0.0f;

	while (!window.closed()) {
		window.clear();
		window.getMousePosition(x, y);
		
		shader.enable();
		shader.setUniform2f("light_pos", vec2(x * 32.0f / window.getWidth() - 16, 9 - (y * 18.0f / window.getHeight())));

		if (window.isKeyTouched(GLFW_KEY_SPACE)) {
			glClearColor(0.0f, 0.5f, 0.0f, 1.0f);
		} else {
			glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		}
		

		layer.render();
		ui.render();

		frames++;
		if (currentTime.elapsed() - timer > 1.0f) {
			timer += 1.0f;
			fpsCounter.text = std::to_string(frames) + " fps";
			printf("%d fps\n", frames);
			frames = 0;
		}
		window.update();
	}

	
	return 0;
}

