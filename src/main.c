#include <stdbool.h>
#include <pthread.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include "api/scene.h"
#include "global.h"
#include "scene/LogoScreen.h"
#include "api/screen.h"

void* log_thread(void* arg) {
	bool is_running = true;
	glog("CMD Thread is %i",G_CMD_THREAD);
	while (is_running && G_APP_RUNNING) {
		//check for SDL errors:
		if (!(SDL_GetError() == NULL) && (SDL_GetError()[0] != '\0')) {
			error(SDL_GetError());
		}
	}
	return 0;
}

void setup_threads() {
	pthread_create(&G_CMD_THREAD, NULL, log_thread, NULL);
}

int main(int argc, char* argv[]) {
 	// Initialize SDL with video
 	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);
  	atexit(SDL_Quit);

  	G_WINDOW = SDL_CreateWindow("Vendetta", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN_DESKTOP | SDL_WINDOW_ALLOW_HIGHDPI);
  	SDL_GLContext context = SDL_GL_CreateContext(G_WINDOW);
  	SDL_GetRendererOutputSize(G_WINDOW,&G_WINDOW_WIDTH,&G_WINDOW_HEIGHT);
  	SCREEN_update_dpi(G_WINDOW_WIDTH,G_WINDOW_HEIGHT);
  	
  	debug("Set window to %ix%i",G_WINDOW_WIDTH, G_WINDOW_HEIGHT);
	
	
  	SDL_Event event;	 // used to store any events from the OS
  	G_APP_RUNNING = true;
	setup_threads();
	
  	glClearColor(0, 0, 0, 1);
  	SCENE_setScene(LogoScreen());
  	
  	while(G_APP_RUNNING) {
    	// poll for events from SDL
    	while(SDL_PollEvent(&event)) {
      		G_APP_RUNNING = event.type != SDL_QUIT;
    	}
    	
		glClear(GL_COLOR_BUFFER_BIT);
		SDL_GL_SwapWindow(G_WINDOW);
		
		// GAME START
		G_SCENE->render();
  	}
	

	// Destroy window
	//error(SDL_GetError());
	SCENE_destroy();
	SDL_GL_DeleteContext(context);
  	SDL_DestroyWindow(G_WINDOW);
  	SDL_Quit();
	
	return 0;
}
