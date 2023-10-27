#include "SDL2/SDL_events.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_mouse.h"
#include "SDL2/SDL_rect.h"
#include "SDL2/SDL_render.h"
#include <iostream>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_ttf.h>

#include "SDL2/SDL_stdinc.h"
#include "SDL2/SDL_surface.h"
#include "utils/image_helper.h"
#include "movement/player.h"


// SDL_Renderer *renderer;
SDL_Window *window;
SDL_Renderer* renderer;

const int WIDTH=800, HEIGHT=600;

bool init() {
  SDL_Init(SDL_INIT_EVERYTHING);

  window = SDL_CreateWindow("Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);

  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

  if(window == NULL) {
    std::cout << "Cant create window " << SDL_GetError() << std::endl;
    return 0;
  }

  if(IMG_Init(IMG_INIT_PNG) == 0) {
    std::cout << "cant initialize sdl2_image" << std::endl;
    return 0;
  }

  //if(TTF_Init() == 0) {
   // std::cout << "cant initialize sdl2_ttf " << SDL_GetError() << TTF_GetError() << std::endl;
    //return 0;
  //}
  TTF_Init();


  return 1;
}

int main(int argv, char** args) {
  if(!init()) {
    std::cout << "Couldnt initiate" << std::endl;
    return 1;
  }

  SDL_Event windowEvent;

  SDL_Surface* player_sur = LoadSurface("assets/player.png");
  SDL_Surface* enemy_sur = LoadSurface("assets/enemy.png");
  SDL_Surface* health_sur = getTextSurface("HP: one hundred");


  SDL_Texture* player_tex = SDL_CreateTextureFromSurface(renderer, player_sur);
  if(player_tex == NULL) {
    std::cout << "failed creating player texture" << std::endl;
    return EXIT_FAILURE;
  }
  SDL_Rect player_rect = { 400, 400, 50, 50 };
  SDL_Rect dest_player_rect = player_rect;

  SDL_Texture* enemy_tex = SDL_CreateTextureFromSurface(renderer, player_sur);
  if(player_tex == NULL) {
    std::cout << "failed creating enemy texture" << std::endl;
    return EXIT_FAILURE;
  }

  SDL_Texture* health_tex = surfaceToTexture(renderer, health_sur);
  SDL_Rect health_rect = { 25, 25, 230, 70 };

  SDL_Rect enemy_rect = { 100, 250, 50, 200 };
  SDL_Rect dest_enemy_rect = enemy_rect;

  SDL_bool amIAttacking = true;


  SDL_FreeSurface(player_sur);
  SDL_FreeSurface(enemy_sur);
  SDL_FreeSurface(health_sur);

  int mouseX, mouseY;

  while(true) {

    if(SDL_PollEvent(&windowEvent)) {
      SDL_GetMouseState(&mouseX, &mouseY);
      switch(windowEvent.type) {
        case SDL_QUIT:
          break;
        case SDL_MOUSEBUTTONDOWN:
          dest_player_rect = attack(mouseX, mouseY, player_rect);
          break;
      }
    }

    player_rect = moveToDest(dest_player_rect, player_rect);
    enemy_rect = moveToDest(dest_enemy_rect, enemy_rect);

    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, player_tex, NULL, &player_rect);
    SDL_RenderCopy(renderer, enemy_tex, NULL, &enemy_rect);
    SDL_RenderCopy(renderer, health_tex, NULL, &health_rect);
    SDL_RenderPresent(renderer);
  }

  SDL_DestroyTexture(player_tex);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  TTF_Quit();
  IMG_Quit();
  SDL_Quit();


  return EXIT_SUCCESS;
}
