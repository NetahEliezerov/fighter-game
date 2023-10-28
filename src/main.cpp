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
#include <string>

#include "SDL2/SDL_stdinc.h"
#include "SDL2/SDL_surface.h"
#include "SDL2/SDL_timer.h"
#include "utils/image_helper.h"
#include "movement/player.h"


// SDL_Renderer *renderer;
SDL_Window *window;
SDL_Renderer* renderer;

const int WIDTH=1200, HEIGHT=600;

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

bool returnToPlayerColor = false;
bool isAttackingBack = false;

Uint32 hitCallback(Uint32 interval, void* param){

  returnToPlayerColor = true;

  return 0;
}

Uint32 attackBackCallback(Uint32 interval, void* param) {
  isAttackingBack = true;
  return 0;
}

int main(int argv, char** args) {
  if(!init()) {
    std::cout << "Couldnt initiate" << std::endl;
    return 1;
  }

  SDL_Event windowEvent;

  SDL_Surface* player_sur = LoadSurface("assets/Idle__001.png");
  SDL_Surface* bg_sur = LoadSurface("assets/bg.png");
  SDL_Surface* enemy_sur = LoadSurface("assets/Enemy_Idle_1.png");
  SDL_Surface* health_sur = getTextSurface("HP: one hundred");


  SDL_Texture* player_tex = SDL_CreateTextureFromSurface(renderer, player_sur);
  if(player_tex == NULL) {
    std::cout << "failed creating player texture" << std::endl;
    return EXIT_FAILURE;
  }
  SDL_Rect player_rect = { 400, 400, 125, 175 };
  SDL_Rect dest_player_rect = player_rect;

  SDL_Texture* enemy_tex = SDL_CreateTextureFromSurface(renderer, enemy_sur);
  if(player_tex == NULL) {
    std::cout << "failed creating enemy texture" << std::endl;
    return EXIT_FAILURE;
  }

  SDL_Texture* bg_tex = SDL_CreateTextureFromSurface(renderer, bg_sur);
  if(bg_tex == NULL) {
    std::cout << "failed creating bg texture" << std::endl;
    return EXIT_FAILURE;
  }


  SDL_Texture* health_tex = surfaceToTexture(renderer, health_sur);
  SDL_Rect health_rect = { 25, 25, 230, 70 };

  SDL_Rect enemy_rect = { 200, 375, 150, 200 };
  SDL_Rect dest_enemy_rect = enemy_rect;

  bool amIAttacking = true;
  //SDL_SetTextureColorMod(enemy_tex, 1.0f, 1.0f, 1.0f);


  SDL_FreeSurface(player_sur);
  SDL_FreeSurface(enemy_sur);
  SDL_FreeSurface(health_sur);
  SDL_FreeSurface(bg_sur);

  int mouseX, mouseY;
  


  while(true) {

    if(SDL_PollEvent(&windowEvent)) {
      SDL_GetMouseState(&mouseX, &mouseY);
      switch(windowEvent.type) {
        case SDL_QUIT:
          break;
        case SDL_MOUSEBUTTONDOWN:
          if(windowEvent.button.button == SDL_BUTTON_LEFT) {
            dest_player_rect = attack(mouseX, mouseY, player_rect);
          }
          break;
      }
    }

    player_rect = moveToDest(dest_player_rect, player_rect);
    enemy_rect = moveToDest(dest_enemy_rect, enemy_rect);


    SDL_bool didPlayerHitHim = SDL_HasIntersection(&player_rect, &enemy_rect);

    if(didPlayerHitHim) {
      std::cout << "Collision" << std::endl;
      SDL_SetTextureColorMod(enemy_tex, 124, 64, 64);
      SDL_TimerID returnToNormal = SDL_AddTimer(750, hitCallback, const_cast<SDL_Texture*>(player_tex));

      if(mouseX > player_rect.x) {
        if((player_rect.x + 355) < 1200) {
          dest_enemy_rect.x = (player_rect.x + 255);
        } else {
          dest_enemy_rect.x = (player_rect.x - 255);
        }
      } else {
        if((player_rect.x - 355) > 0) {
          dest_enemy_rect.x = (player_rect.x - 255);
        } else {
          dest_enemy_rect.x = (player_rect.x + 255);
        }
      }      
    }

    if(returnToPlayerColor == true) {
      SDL_SetTextureColorMod(enemy_tex, 255, 255, 255);
      returnToPlayerColor = false;
    }

    if(isAttackingBack) {
      std::cout << "Attack back";
    }

    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, bg_tex, NULL, NULL);

    if(mouseX > player_rect.x) {
      SDL_RenderCopy(renderer, player_tex, NULL, &player_rect);
    } else {
      SDL_RenderCopyEx(renderer, player_tex, NULL, &player_rect, NULL, NULL, SDL_FLIP_HORIZONTAL);
    }

    SDL_RenderCopy(renderer, enemy_tex, NULL, &enemy_rect);
    SDL_RenderCopy(renderer, health_tex, NULL, &health_rect);
    SDL_RenderPresent(renderer);

  }

  SDL_DestroyTexture(player_tex);
  SDL_DestroyTexture(enemy_tex);
  SDL_DestroyTexture(bg_tex);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  TTF_Quit();
  IMG_Quit();
  SDL_Quit();


  return EXIT_SUCCESS;
}
