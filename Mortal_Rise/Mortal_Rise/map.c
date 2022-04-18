#include <SDL2/SDL_image.h>

#include "map.h"
#include "loadIMG.h"

#include <stdbool.h>

SDL_Texture* brickTex;
SDL_Rect blockRect;

Block blocks[LVL_W * LVL_H];

lvl[LVL_W * LVL_H] = {
	1,0,0,0,0,1,0,0,0,0,1,
	0,1,0,0,0,1,0,0,0,1,0,
	0,0,1,0,0,1,0,0,1,0,0,
	0,0,0,1,1,1,1,1,0,0,0,
	0,0,0,1,1,1,1,1,0,0,0,
	0,0,1,0,0,1,0,0,1,0,0,
	0,1,0,0,0,1,0,0,0,1,0,
	1,0,0,0,0,1,0,0,0,0,1,
};


void InitMap() {
	brickTex = LoadIMG("spr/blocks/brick.png");

	blockRect.w = BLOCK_SIZE;
	blockRect.h = BLOCK_SIZE;
}