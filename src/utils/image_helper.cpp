#include "SDL2/SDL_pixels.h"
#include "SDL2/SDL_surface.h"
#include "SDL2/SDL_ttf.h"
#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>

using namespace std;

SDL_Surface* LoadSurface(char *image_path) {
  SDL_Surface* sur = IMG_Load(image_path);
  if(sur == NULL) {
    cout << "Cant load image " << image_path << endl;
  }
  return sur;
}

SDL_Surface* getTextSurface(char *text)
{
  SDL_Color color = { 255, 255, 255 };
  TTF_Font* font = TTF_OpenFont("assets/Harukaze.ttf", 22);
	SDL_Surface* surface = TTF_RenderText_Solid(font, text, color);
  if(surface == NULL) {
    cout << "Cant load text " << text << endl;
  }
	return surface;
}

SDL_Texture* surfaceToTexture(SDL_Renderer* renderer, SDL_Surface* sur) {
  SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, sur);
  if(tex == NULL) {
    std::cout << "failed creating enemy texture" << std::endl;
  }
  return tex;
}
