#pragma once
#include "SDL2/SDL_rect.h"
#include <iostream>

using namespace std;

struct AttackResponse {

};

SDL_Rect attack(int mouseX, int mouseY, SDL_Rect player_rect);

SDL_Rect moveToDest(SDL_Rect dest_rect, SDL_Rect current_rect);
