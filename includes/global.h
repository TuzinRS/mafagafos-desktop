#ifndef _GLOBAL_H
#define _GLOBAL_H
#include <stdbool.h>
#include <SDL2/SDL.h>
#include "api/scene.h"

int G_CMD_THREAD;

SDL_Window* G_WINDOW;
int G_WINDOW_WIDTH;
int G_WINDOW_HEIGHT;
scene* G_SCENE;
bool G_APP_RUNNING;

void debug(const char *fmt, ...);
void warn(const char *fmt, ...);
void error(const char *fmt, ...);
void succ(const char *fmt, ...);
void info(const char *fmt, ...);
void glog(const char *fmt, ...);
#endif
