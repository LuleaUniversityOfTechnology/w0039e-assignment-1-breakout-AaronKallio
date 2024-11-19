

#define PLAY_IMPLEMENTATION
#define PLAY_USING_GAMEOBJECT_MANAGER
#include "Play.h"
#include "game.h"
#include "constants.h"
#include "Paddle.h"
int currentScore = 0;
//int highscoresArray[5] = { 5,4,3,2,1 };

int* highscoresArray = new int[5];

void assignArray() {
	int count = 5;
	for (int i = 0; i<= 5; i++) {
		highscoresArray[i] = count;
		count--;
	}
}



bool lost = false;
void SpawnBall() { 
	Play::CreateManager(DISPLAY_WIDTH, DISPLAY_HEIGHT, DISPLAY_SCALE); //creates the game screen
	const int objectId = Play::CreateGameObject(ObjectType::TYPE_BALL, { 200, DISPLAY_HEIGHT - 240 }, 4, "ball"); //creates the ball
	
	GameObject& ball = Play::GetGameObject(objectId);
	ball.velocity = normalize({ 1, -1 }) * ballSpeed;
	assignArray();

}

bool comp(int a, int b) {
	return a > b;
}

	void StepFrame(float elapsedTime) { //runs 60 times per second

		std::string score1 = std::to_string(highscoresArray[0]);
		const char* scoreOutput1 = score1.c_str();
		std::string score2 = std::to_string(highscoresArray[1]);
		const char* scoreOutput2 = score2.c_str();
		std::string score3 = std::to_string(highscoresArray[2]);
		const char* scoreOutput3 = score3.c_str();
		std::string score4 = std::to_string(highscoresArray[3]);
		const char* scoreOutput4 = score4.c_str();
		std::string score5 = std::to_string(highscoresArray[4]);
		const char* scoreOutput5 = score5.c_str();

		std::string score = std::to_string(currentScore);
		const char* scoreOutput = score.c_str();
		

		Play::DrawDebugText({ 930, 100 }, scoreOutput1);
		Play::DrawDebugText({ 930, 85 }, scoreOutput2);
		Play::DrawDebugText({ 930, 70 }, scoreOutput3);
		Play::DrawDebugText({ 930, 55 }, scoreOutput4);
		Play::DrawDebugText({ 930, 40 }, scoreOutput5);

		Play::DrawDebugText({ 30, 40 }, scoreOutput);
		//moves the paddle if needed and then draws it 
		UpdatePaddle(paddle);
		DrawPaddle(paddle);

		
		//accesses the ball 
		const std::vector<int> ballIds = Play::CollectGameObjectIDsByType(TYPE_BALL);
		for (int i = 0; i < ballIds.size(); i++) {
			GameObject& ball = Play::GetGameObject(ballIds[i]);
		//bounces ball if it hits the sides 
			if (ball.pos.x > DISPLAY_WIDTH || ball.pos.x < 0) {
				ball.velocity.x = ball.velocity.x * -1;
			}
			 
			//if (ball.pos.y > DISPLAY_HEIGHT || ball.pos.y < 0) {  // code for bouncing on the bottom too
			//bounces ball on the top of the screen
			if (ball.pos.y > DISPLAY_HEIGHT) {
				ball.velocity.y = ball.velocity.y * -1;
			}
			//if ball hits the bottom, display game over
			if(ball.pos.y < 0){
				Play::DrawDebugText({ DISPLAY_WIDTH / 2, DISPLAY_HEIGHT / 2 }, "YOU LOST!!!");
				if (currentScore > highscoresArray[4] && lost == false) {
					highscoresArray[4] = currentScore;
					sort(highscoresArray, highscoresArray + 5, comp);
					lost = true;
				}

			}

			//if the ball collides with the paddle, bounces the ball 
			if (IsColliding(paddle,ball)) {
				//ball.velocity.y = ball.velocity.y-5 * -1; //adds some variation to the bounces 
				ball.velocity.y = ball.velocity.y * -1;
				//Play::DrawDebugText({ DISPLAY_WIDTH / 2, DISPLAY_HEIGHT / 2 }, "bounce");
			}
			//updates and draws the ball
		Play::UpdateGameObject(ball);
		Play::DrawObject(ball);		
		Play::PresentDrawingBuffer();
		}

		//goes through each brick 
		const std::vector<int> brickIds = Play::CollectGameObjectIDsByType(TYPE_BRICK);
		for (int i = 0; i < brickIds.size(); i++) {
			GameObject& brick = Play::GetGameObject(brickIds[i]);
			//updates and draws bricks
			Play::UpdateGameObject(brick);
			Play::DrawObject(brick);
			//if the ball hits a brick, destroys the brick
			for (int j = 0; j < ballIds.size(); j++) {
				GameObject& ball = Play::GetGameObject(ballIds[j]);
				if (Play::IsColliding(Play::GetGameObject(brickIds[i]), ball)) {
					Play::DestroyGameObject(brickIds[i]);
					currentScore += 1;
					//changes velocity of ball on hit
					ball.velocity.y = ball.velocity.y * -1;

				}

			}

		}
		//updates everything on screen 
		Play::PresentDrawingBuffer();
	}

	//sets up the bricks in a 7x43 grid pattern
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

	