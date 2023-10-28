#pragma once
#include "SDL2/SDL_render.h"
#include "SDL2/SDL_surface.h"
#include <iostream>

using namespace std;

SDL_Surface* LoadSurface(const char *image_path);
SDL_Surface* getTextSurface(char *text);
SDL_Texture* surfaceToTexture(SDL_Renderer* renderer, SDL_Surface* sur); 
