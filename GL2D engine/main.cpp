#include "src/graphics/window.h"
#include "src/math/vector.h"

#include "src/graphics/shader.h"

#include "src/graphics/layers/tilelayer.h"
#include "src/graphics/sprite.h"

#include <time.h>
#include "src/utils/timer.h"

int main() {
	using namespace sparky; //engine namespace, should be changed to something other than sparky
	using namespace graphics; //contains most of the classes necessary to draw stuff
	using namespace math; //general math classes like vectors and matrices


	Window window("GL program", 960, 540); //Make a new Window object to draw stuff to
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); //Set the clear color of the window at the beginning of every draw loop (black)

	Shader shader("src/shaders/default.vert", "src/shaders/default.frag"); //create a new OpenGL shader using a vert and frag shader file
	shader.setUniform2f("light_pos", vec2(4.0f, 1.5f)); //Set a uniform(variable) light_pos to the center of the screen as a default light position

	TileLayer layer(&shader); //A special renderer just for simple sprites, very fast and uses batch renderer

	for (float y = -9.0f; y < 9.0f; y += 0.1f) {
		for (float x = -16.0f; x < 16.0f; x += 0.1f) {

			//We are looping through the entire orthographic screen space at 0.1f intervals
			// # of sprites = (18 / 0.1) * (32 / 0.1) = 57600
			layer.add(new Sprite(x, y, 0.08f, 0.08f, math::vec4(0.2f, 0.2f, 0.6f, 1.0f))); //add a sprite to our TileLayer, sprite: Sprite(x, y, xsize, ysize, color)
		}
	}


	Timer currentTime; //Start a timer which keeps track of the "currentTime" so the time since start of program
	float timer = 0.0f; //Compared to currentTime to tell when 1 second has passed

	double x, y; //x and y position of the mouse, which will be updated later
	int frames = 0; //Frames completed in 1 second

	while (!window.closed()) {

		window.clear();
		window.getMousePosition(x, y); // x and y are passed by reference and return the mouse position
		shader.setUniform2f("light_pos", vec2(x / 30 - 16, 9 - (y / 30))); //We convert the mouse position from pixels to OpenGL coords

		layer.render(); //Renders our TileLayer

		frames++;
		if (currentTime.elapsed() - timer > 1.0f) {
			timer += 1.0f; //The time elapsed will take another second to be greater than timer again
			printf("%d fps\n", frames); //Prints the fps every second
			frames = 0;
		}
		window.update(); //Push the buffer to the display and poll events
	}

	return 0;
}