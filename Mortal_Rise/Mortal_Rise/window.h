#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <stdio.h>

#include "player.h"
#include "map.h"

void InitWindow();
void RefreshWindow();
void CloseWindow();

void RenderMap();

extern SDL_Window* window;
extern SDL_Renderer* renderer;

extern int monitorX;
extern int monitorY;