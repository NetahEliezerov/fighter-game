#include "SDL2/SDL_rect.h"
#include "player.h"
#include <iostream>

using namespace std;

SDL_Rect attack(int mouseX, int mouseY, SDL_Rect player_rect) {
  cout << "attacked ";

  SDL_Rect new_player_rect = player_rect;

  if(mouseX > player_rect.x) {
    cout << "right" << endl;
  } else {
    cout << "left" << endl;
  }

  new_player_rect.x = mouseX;
  std::cout << mouseX << " " << mouseY << std::endl;

  return new_player_rect;
}

SDL_Rect moveToDest(SDL_Rect dest_rect, SDL_Rect current_rect) {
  if(dest_rect.x != current_rect.x) {
    if(dest_rect.x > current_rect.x) {
      current_rect.x += 1;
    } else {
      current_rect.x -= 1;
    }
  }
  return current_rect;
}
