

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
			//if (Play::IsLeavingDisplayArea(ball, Play::VERTICAL)) {
			if (ball.pos.x > DISPLAY_WIDTH || ball.pos.x < 0) {
				ball.velocity.x = ball.velocity.x * -1;
			}
			//if (Play::IsLeavingDisplayArea(ball, Play::HORIZONTAL)) {
			if (ball.pos.y > DISPLAY_HEIGHT || ball.pos.y < 0) {
				ball.velocity.y = ball.velocity.y * -1;
				
			}
			Play::UpdateGameObject(ball);
			Play::DrawObject(ball);
			Play::PresentDrawingBuffer();
			
				
		
		}
		
	}

	void SetupScene() {
		int x = 20;
		int y = DISPLAY_HEIGHT - 20;
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 10; j++) {
				Play::CreateGameObject(ObjectType::TYPE_BRICK, { x, y }, 6, "brick");
				x += 10;
			}
			y += 10;

		}
	
	
	
	
	
	
	}