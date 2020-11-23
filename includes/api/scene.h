#ifndef _API_SCENE_H
#define _API_SCENE_H
typedef struct __SCENE {
	void (*create)();
	void (*render)();
	void (*close)();
	void (*input)(int);
} scene;

scene* SCENE_create(void (* create)(), void (* render)(), void(* close)(), void(* input)(int));
void SCENE_setScene(scene* screen);
void SCENE_destroy();
#endif
