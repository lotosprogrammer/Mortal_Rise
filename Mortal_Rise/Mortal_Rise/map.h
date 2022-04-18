#pragma once

#include <SDL2/SDL_image.h>

#include "loadIMG.h"

#include <stdbool.h>

#define LVL_H 8
#define LVL_W 11

#define BLOCK_SIZE 100

typedef struct Block {
	bool shouldCollide, shouldRender;
}Block;

extern int lvl[LVL_H * LVL_W];
extern Block blocks[LVL_W * LVL_H];
void InitMap();

extern SDL_Texture* brickTex;
extern SDL_Rect blockRect;





