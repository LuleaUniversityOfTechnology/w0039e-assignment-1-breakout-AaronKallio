

#define PLAY_IMPLEMENTATION
#define PLAY_USING_GAMEOBJECT_MANAGER
#include "Play.h"
#include "game.h"
#include "constants.h"

void SpawnBall() {
	Play::CreateManager(DISPLAY_WIDTH, DISPLAY_HEIGHT, DISPLAY_SCALE);
	const int objectId = Play::CreateGameObject(ObjectType::TYPE_BALL, { DISPLAY_WIDTH / 2, DISPLAY_HEIGHT - 240 }, 4, "ball");//DISPLAY_WIDTH / 2
	
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

		const std::vector<int> brickIds = Play::CollectGameObjectIDsByType(TYPE_BRICK);
		for (int i = 0; i < brickIds.size(); i++) {
			GameObject& brick = Play::GetGameObject(brickIds[i]);
			//Play::UpdateGameObject(brick);
			//Play::DrawObject(brick);
			//Play::PresentDrawingBuffer();

			Play::UpdateGameObject(brick);
			Play::DrawObject(brick);

			for (int j = 0; j < ballIds.size(); j++) {
				GameObject& ball = Play::GetGameObject(ballIds[j]);
				if (Play::IsColliding(Play::GetGameObject(brickIds[i]),ball)) {
					Play::DestroyGameObject(i);
					
					ball.velocity.y = ball.velocity.y * -1;
					
				
				}

			}

		


		}
		Play::PresentDrawingBuffer();
	}

	void SetupScene() {
		int x = 50;
		int y = DISPLAY_HEIGHT - 120;
		for (int i = 0; i < 7; i++) {
			for (int j = 0; j < 43; j++) {
				Play::CreateGameObject(ObjectType::TYPE_BRICK, { x, y }, 6, "brick");
				x += 20;
			}
			y += 12;
			x = 50;

		}
	
	
	
	
	
	
	}