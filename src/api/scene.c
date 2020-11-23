#include "api/scene.h"
#include "global.h"

scene* SCENE_create(void (* create)(), void (* render)(), void(* close)(), void(* input)(int)) {
	scene* result;
	result->create = create;
	result->render = render;
	result->close = close;
	result->input = input;
	return result;
}

void SCENE_setScene(scene* screen) {
	if (!G_SCENE) {
	} else {
		G_SCENE->close();
	}
	G_SCENE = screen;
	G_SCENE->create();
}

void SCENE_destroy() {
	if (!G_SCENE) {
		warn("No scene selected!");
	} else {
		G_SCENE->close();
	}
	G_SCENE = NULL;
}
