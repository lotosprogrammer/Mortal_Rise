
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <stdbool.h>

#include "window.h"
#include "player.h"
#include "map.h"

/* NOTES FOR FUTURE ME :
-windowX and monitorX are the same thing
*/

int main(int argc, char** argv) {
	SDL_Init(SDL_INIT_VIDEO);
	IMG_Init(IMG_INIT_PNG);

	InitWindow();
	SDL_Delay(100);

	InitPlayer(400, 400);
	InitMap();

	bool isRunning = true;
	SDL_Event event;

	int dt = 0;
	int prevFrame = 0;

	while (isRunning) {
		while (SDL_PollEvent(&event)) {
			const Uint8* keys = SDL_GetKeyboardState(NULL);
			if (keys[SDL_SCANCODE_ESCAPE] || event.type == SDL_QUIT) {
				isRunning = false;
				break;
			}
		}
		dt = SDL_GetTicks() - prevFrame;
		prevFrame = SDL_GetTicks();

		if (SDL_GetWindowFlags(window) & SDL_WINDOW_INPUT_FOCUS) {
			PlayerMovement(dt);
			
			PlayerWorldCollision();
			RefreshWindow();
		}
	}
	CloseWindow();

	IMG_Quit();
	SDL_Quit();

	return 0;
}