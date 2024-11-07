

#define PLAY_IMPLEMENTATION
#define PLAY_USING_GAMEOBJECT_MANAGER
#include "Play.h"
#include "game.h"
#include "constants.h"

void SpawnBall() {
	Play::CreateManager(DISPLAY_WIDTH, DISPLAY_HEIGHT, DISPLAY_SCALE);
	const int objectId = Play::CreateGameObject(ObjectType::TYPE_BALL, { DISPLAY_WIDTH / 2, DISPLAY_HEIGHT - 60 }, 4, "ball");
	
	GameObject& ball = Play::GetGameObject(objectId);
	ball.velocity = normalize({ 1, -1 }) * ballSpeed;
	

}

	void StepFrame(float elapsedTime) {
		const std::vector<int> ballIds = Play::CollectGameObjectIDsByType(TYPE_BALL);
		for (int i = 0; i < ballIds.size(); i++) {
			GameObject& ball = Play::GetGameObject(ballIds[i]);
			Play::UpdateGameObject(ball);
			Play::DrawObject(ball);
			Play::PresentDrawingBuffer();
			
				
		
		}
		
	}