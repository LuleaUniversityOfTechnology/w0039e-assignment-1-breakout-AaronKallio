#include "game.h"
//#include "constants.h"

// The entry point for a PlayBuffer program
void MainGameEntry( PLAY_IGNORE_COMMAND_LINE )
{
	SpawnBall();
	SetupScene();
	
}
//std::string score = std::to_string(highscoresArray[0]);
//const char* scoreOutput = score.c_str();

// Called by PlayBuffer every frame (60 times a second!)
bool MainGameUpdate( float elapsedTime )
{
	Play::ClearDrawingBuffer( Play::cBlack );
	Play::PresentDrawingBuffer();
	
	StepFrame(elapsedTime);

	//Play::DrawDebugText({ 100, 100 }, scoreOutput);
	
	return 0;
	
}

// Gets called once when the player quits the game 
int MainGameExit(void){
	Play::DestroyManager();
	return 0;
}