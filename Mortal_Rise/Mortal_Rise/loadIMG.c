#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "loadIMG.h"
#include "window.h"

SDL_Texture* LoadIMG(char* path) {
	SDL_Surface* surface = IMG_Load(path);
	if (surface == NULL) {
		printf("Failed to load image because %s\n", SDL_GetError());
		return NULL;
	}

	SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, surface);
	if (tex == NULL) {
		printf("Failed to create texture from surface because %s\n", SDL_GetError());
		return NULL;
	}

	return tex;
}