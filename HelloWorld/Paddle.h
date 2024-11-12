#pragma once
#define PLAY_USING_GAMEOBJECT_MANAGER
#include "Play.h"

struct Paddle {
	int x;
	int y;
};

extern Paddle paddle;

void DrawPaddle(struct Paddle&);
void UpdatePaddle(struct Paddle&);
