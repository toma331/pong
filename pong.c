#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_mouse.h>
#include <SDL2/SDL_mutex.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>

#define SCREEN_HEIGHT 480
#define SCREEN_WIDTH 640

static int MOVE_SPEED = 5;

typedef struct Speed {
  int x;
  int y;

} Speed;

typedef struct BALL {

  int x, y;
  int h, w;
  int dx, dy;
} BALL;

static void move_rect(SDL_Surface *surface, SDL_Rect *rect, Speed *speed) {
  SDL_FillRect(surface, rect, 0x00000000);
  rect->x += speed->x;
  rect->y += speed->y;
  SDL_FillRect(surface, rect, 0xffffffff);
}



// direction must be +-1


static void move_player(SDL_Surface *surface, SDL_Rect *pl, int direction) {
  if (direction < 0 && pl->y <= 0)
    return;

  if (direction > 0 && pl->y >= (surface->h - pl->h))
    return;

  Speed speed = (Speed){0, direction * MOVE_SPEED};
  move_rect(surface, pl, &speed);
}

int main() {
  SDL_InitSubSystem(SDL_INIT_VIDEO);

  SDL_Window *window =
      SDL_CreateWindow("Pong Game", SDL_WINDOWPOS_CENTERED,
                       SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
  SDL_Surface *surface = SDL_GetWindowSurface(window);

  Uint32 color = 0xffffffff;

  SDL_Rect pl1 = (SDL_Rect){40, 40, 40, 200};
  SDL_FillRect(surface, &pl1, color);

  SDL_Rect pl2 = (SDL_Rect){560, 250, 40, 200};
  SDL_FillRect(surface, &pl2, color);

  SDL_Rect ball = (SDL_Rect){320, 240, 20, 20};
  SDL_FillRect(surface, &ball, color);

  SDL_Rect border = (SDL_Rect){320, 0, 1, 480};
  SDL_FillRect(surface, &border, color);

  int running = 1;
  SDL_Event event;

  while (running) {
    SDL_PollEvent(&event);

    if (event.type == SDL_QUIT) {

      running = 0;
    }
    if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_DOWN) {

      move_player(surface, &pl1, 1);
    }
    if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_UP) {

      move_player(surface, &pl1, -1);
    }
    if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_LCTRL) {

      move_player(surface, &pl2, 1);
    }
    if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_LSHIFT) {

      move_player(surface, &pl2, -1);
    }

    SDL_UpdateWindowSurface(window);
    SDL_Delay(10);
  }
}
