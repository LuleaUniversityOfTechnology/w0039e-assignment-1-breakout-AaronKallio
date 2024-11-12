#pragma once
#define PLAY_USING_GAMEOBJECT_MANAGER
#include "Play.h"

struct Paddle {
	int x;
	int y;
	int height = 16;
	int width = 128;
};

extern Paddle paddle;

void DrawPaddle(struct Paddle&);
void UpdatePaddle(struct Paddle&);
bool IsColliding(const Paddle& paddle, const Play::GameObject& obj);
