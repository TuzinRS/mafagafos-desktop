#include "global.h"
#include "api/scene.h"
#include "api/screen.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL_image.h>

SDL_Texture* logo = NULL;
SDL_Surface* surface = NULL;
SDL_Renderer* renderer = NULL;
SDL_Rect logo_bounds;

void LogoScreen_create() {
	debug("Initialized LogoScreen");
	renderer = SDL_CreateRenderer(G_WINDOW, -1, SDL_RENDERER_ACCELERATED);
	surface = IMG_Load("assets/gui/button.png"); 
	logo = SDL_CreateTextureFromSurface(renderer, surface);
	
	logo_bounds.x = 0;
	logo_bounds.y = 0;
	logo_bounds.w = 30 * dpi;
	logo_bounds.h = 30 * dpi;
}

void LogoScreen_render() {
  	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	
	SDL_RenderCopy(renderer, logo, NULL, &logo_bounds);
	SDL_RenderPresent(renderer);
}

void LogoScreen_input(int key) {
	
}

void LogoScreen_close() {
}

scene* LogoScreen() {
	return SCENE_create(LogoScreen_create,LogoScreen_render,LogoScreen_close,LogoScreen_input);
}
