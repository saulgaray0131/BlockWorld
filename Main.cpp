#include "BW\Application.h"
#include "BW\Gfx\TextureAtlas.h"
#include <thread>

int main(int argc, char** argv) {
	BW::Application::Config config;
	config.height = 1080;
	config.width = 1920;

	BW::Application blockworld;
	blockworld.start(config);

	return 0;
}