#pragma once
#define PLAY_USING_GAMEOBJECT_MANAGER

#include "Play.h"
void SpawnBall();
void SetupScene();
void StepFrame(float elapsedTime);
void assignArray();
int lineCount();
void ExitFunction(int linecount);
int* resizeArray(int* arr, int oldSize, int newSize);
void createScoreArray();
int currentLines();