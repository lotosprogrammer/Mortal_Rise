#include <stdio.h>
#include <stdbool.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "player.h"
#include "map.h"

float px;
float py;

float pvx;
float pvy;

float playerAngle;

SDL_Rect pRect;



float lastCheckedX;
float lastCheckedY;

bool playerCollidingTop = false;
bool playerCollidingBottom = false;
bool playerCollidingRight = false;
bool playerCollidingLeft = false;

int windowX = 0;
int windowY = 0;

void InitPlayer(int windowX_, int windowY_) {
	px = PLAYER_STARTING_OFFSET_X;
	py = PLAYER_STARTING_OFFSET_Y;

	pvx = 0;
	pvy = 0;

	playerAngle = 0;

	pRect.w = PLAYER_WIDTH;
	pRect.h = PLAYER_HEIGHT;
	pRect.x = floor(px);
	pRect.y = floor(py);

	lastCheckedX = px;
	lastCheckedY = py;


	windowX = windowX_;
	windowY = windowY_;

	UpdateNearBlocks();
}

void PlayerMovement(int dt) {
	const Uint8* keys = SDL_GetKeyboardState(NULL);

	bool horizontal = false;
	bool vertical = false;

	if (keys[SDL_SCANCODE_A] && !playerCollidingLeft) {
		horizontal = true;
		pvx -= PLAYER_SPEED * dt;
		playerCollidingRight = false;
	}
	if (keys[SDL_SCANCODE_D] && !playerCollidingRight) {
		horizontal = true;
		pvx += PLAYER_SPEED * dt;
		playerCollidingLeft = false;
	}
	if (keys[SDL_SCANCODE_W] && !playerCollidingTop) {
		vertical = true;
		pvy -= PLAYER_SPEED * dt;
		playerCollidingBottom = false;
	}
	if (keys[SDL_SCANCODE_S] && !playerCollidingBottom) {
		vertical = true;
		pvy += PLAYER_SPEED * dt;
		playerCollidingTop = false;
	}

	if (!horizontal) {
		pvx = 0;
	}
	if (!vertical) {
		pvy = 0;
	}

	if (pvx > PLAYER_SPEED) {
		pvx = PLAYER_SPEED;
	}
	else if (pvx < -PLAYER_SPEED) {
		pvx = -PLAYER_SPEED;
	}

	if (pvy > PLAYER_SPEED) {
		pvy = PLAYER_SPEED;
	}
	else if (pvy < -PLAYER_SPEED) {
		pvy = -PLAYER_SPEED;
	}

	if (pvx != 0 && pvy != 0) {
		float normalVal = sqrt(fabsf(pvx * pvx) + fabsf(pvy * pvy)) / 2;
		

		pvx *= normalVal;
		pvy *= normalVal;
	}

	px += pvx * dt;
	py += pvy * dt;

	int distX;
	int distY;

	distX = fabsf(px - lastCheckedX);
	distY = fabsf(py - lastCheckedY);

	if (horizontal || vertical) {
		if (distX >= COLLISION_BLOCK_UPDATE_DIST || distY >= COLLISION_BLOCK_UPDATE_DIST) {
			UpdateNearBlocks();
			lastCheckedX = px;
			lastCheckedY = py;

		}
	}

}


void UpdateNearBlocks() {
	int atX = 0;
	int atY = 0;


	for (int i = 0; i < LVL_W * LVL_H; i++) {
		if (atX == LVL_W) {
			atX = 0;
			atY++;
		}
		if (lvl[i] != 0) {
			int blockX = atX * BLOCK_SIZE;
			int blockY = atY * BLOCK_SIZE;

			int distX;
			int distY;

			distX = fabsf(px - blockX);
			distY = fabsf(py - blockY);

			if (distX <= windowX / 2 + BLOCKS_TO_RENDER_MARGIN && distY <= windowY / 2 + BLOCKS_TO_RENDER_MARGIN) {

				blocks[i].shouldRender = true;

				if (distX <= COLLISION_RADIUS && distY <= COLLISION_RADIUS) {
					
					blocks[i].shouldCollide = true;
				}
				else {
					blocks[i].shouldCollide = false;
				}
			}
			else {
				blocks[i].shouldRender = false;
				blocks[i].shouldCollide = false;
			}

		}
		atX++;
	}
}

void PlayerWorldCollision() {
	for (int i = 0; i < LVL_W * LVL_H; i++) {

		if (blocks[i].shouldCollide) {
			int blockX = (i % LVL_W) * BLOCK_SIZE;
			int blockY = floor(i / LVL_W) * BLOCK_SIZE;


			if (!playerCollidingRight) {
				if (px + PLAYER_WIDTH >= blockX && px + PLAYER_WIDTH <= blockX + COLLISION_MARGIN && py + PLAYER_HEIGHT > blockY + 1 && py < blockY + BLOCK_SIZE - 1) {
					playerCollidingRight = true;
					px = blockX - PLAYER_WIDTH;
					if (pvx > 0)
						pvx = 0;
				}

			}
			else if (py > blockY + BLOCK_SIZE || py + PLAYER_HEIGHT < blockY) {
				playerCollidingRight = false;
			}
			if (!playerCollidingLeft) {
				if (px >= blockX + BLOCK_SIZE - COLLISION_MARGIN && px <= blockX + BLOCK_SIZE && py + PLAYER_HEIGHT > blockY + 1 && py < blockY + BLOCK_SIZE - 1) {
					playerCollidingLeft = true;
					px = blockX + BLOCK_SIZE;
					if (pvx < 0)
						pvx = 0;
				}
			}
			else if (py > blockY + BLOCK_SIZE || py + PLAYER_HEIGHT < blockY) {
				playerCollidingLeft = false;
			}

			if (!playerCollidingBottom) {
				if (px + PLAYER_WIDTH >= blockX + 1 && px <= blockX + BLOCK_SIZE - 1 && py + PLAYER_HEIGHT > blockY && py < blockY - BLOCK_SIZE + BLOCK_SIZE) {
					playerCollidingBottom = true;
					py = blockY - PLAYER_HEIGHT;
					if (pvy > 0)
						pvy = 0;
				}

			}
			else if (px + PLAYER_WIDTH < blockX || px > blockX + BLOCK_SIZE) {
				playerCollidingBottom = false;
			}
			if (!playerCollidingTop) {
				if (px + PLAYER_WIDTH >= blockX + 1 && px <= blockX + BLOCK_SIZE - 1 && py < blockY + BLOCK_SIZE && py > blockY - PLAYER_HEIGHT + COLLISION_MARGIN) {
					playerCollidingTop = true;
					py = blockY + BLOCK_SIZE;
					if (py < 0)
						pvy = 0;
				}
			}
			else if (px + PLAYER_WIDTH < blockX || px > blockX + BLOCK_SIZE) {
				playerCollidingTop = false;
			}
		}
		
	}
}




