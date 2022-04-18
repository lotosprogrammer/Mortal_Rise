#pragma once

#include <stdio.h>
#include <stdbool.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "map.h"

#define PLAYER_SPEED 1	
#define PLAYER_WIDTH 35
#define PLAYER_HEIGHT 35
#define PLAYER_STARTING_OFFSET_X 1920/2 - PLAYER_WIDTH/2
#define PLAYER_STARTING_OFFSET_Y 1080/2 - PLAYER_HEIGHT/2
#define COLLISION_RADIUS BLOCK_SIZE * 2
#define COLLISION_BLOCK_UPDATE_DIST BLOCK_SIZE / 2
#define COLLISION_MARGIN 10
#define BLOCKS_TO_RENDER_MARGIN BLOCK_SIZE * 1.5 // kinda confusing


void InitPlayer(int windowX_, int windowY_);
void PlayerMovement(int dt);
void UpdateNearBlocks();
void PlayerWorldCollision();

extern float playerAngle;

extern float px;
extern float py;

extern float pvx;
extern float pvy;

extern SDL_Rect pRect;

extern float lastCheckedX;
extern float lastCheckedY;

extern bool playerCollidingTop;
extern bool playerCollidingBottom;
extern bool playerCollidingRight;
extern bool playerCollidingLeft;

extern int windowX;
extern int windowY;