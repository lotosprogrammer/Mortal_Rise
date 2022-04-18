
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <stdio.h>

#include "window.h"
#include "player.h"
#include "map.h"


SDL_Window* window;
SDL_Renderer* renderer;

int monitorX;
int monitorY;

void InitWindow() {

	SDL_DisplayMode DM;
	SDL_GetCurrentDisplayMode(0, &DM);
	monitorX = DM.w;
	monitorY = DM.h;

	window = SDL_CreateWindow("Mortal rise", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, monitorX, monitorY, SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN);

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);		
}

void RefreshWindow() {
	SDL_SetRenderDrawColor(renderer, 192, 16, 16, 255);
	SDL_RenderClear(renderer);


	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderFillRect(renderer, &pRect);

	RenderMap();

	SDL_RenderPresent(renderer);

}

void RenderMap() {
	int atX = 0;
	int atY = 0;
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	for (int i = 0; i < LVL_W * LVL_H; i++) {
		if (atX == LVL_W) {
			atX = 0;
			atY++;
		}

		if (lvl[i] != 0 && blocks[i].shouldRender) {
			blockRect.x = floor(atX * BLOCK_SIZE - px + PLAYER_STARTING_OFFSET_X);
			blockRect.y = floor(atY * BLOCK_SIZE - py + PLAYER_STARTING_OFFSET_Y);

			if (lvl[i] == 1) {
				SDL_RenderCopy(renderer, brickTex, NULL, &blockRect);
			}
		}

		atX++;
	}
}

void CloseWindow() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
}
