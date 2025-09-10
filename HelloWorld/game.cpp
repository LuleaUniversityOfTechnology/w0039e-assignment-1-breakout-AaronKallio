

#define PLAY_IMPLEMENTATION
#define PLAY_USING_GAMEOBJECT_MANAGER
#include "Play.h"
#include "game.h"
#include "constants.h"
#include "Paddle.h"
#include <iostream>
#include <fstream>
#include <string>
int currentScore = 0;

//used to reverse the sort into decending order
bool comp(int a, int b) {
	return a > b;
}

//counts how many lines in the text file
int lineCount() {
	int number_of_lines = 0;
	std::string line;
	std::fstream myfile("scores.txt");

	while (std::getline(myfile, line)) {
		++number_of_lines;
	}
	myfile.close();
	return number_of_lines;
}

int* resizeArray(int* arr, int oldSize, int newSize) {
	int* newArr = new int[newSize];
	for (int i = 0; i < oldSize && i < newSize; i++) {
		newArr[i] = arr[i];
	}
	delete[] arr; // free old memory
	return newArr;
}


int linecount = lineCount();
int currentLines() {
	return linecount;
}

//creates dynamic array
int* highscoresArray = new int[linecount+1];

int displayArray [5];

void createScoreArray() {
	for (int i = 0; i < 4; i++) {
		displayArray[i] = 0;
	}
}

//adds scores from file to array
void assignArray() {
	int count = lineCount();
	int loopCount = 0;
	fstream scoreFile("scores.txt");
	std::string score;
	while (std::getline(scoreFile, score)) {
		highscoresArray[loopCount] = stoi(score);
		loopCount++;
	}
	sort(highscoresArray, highscoresArray + count, comp);
	scoreFile.close();


}

void SpawnBall() { 
	createScoreArray();
	assignArray();
	int displayScoreAmount;
	Play::CreateManager(DISPLAY_WIDTH, DISPLAY_HEIGHT, DISPLAY_SCALE); //creates the game screen
	const int objectId = Play::CreateGameObject(ObjectType::TYPE_BALL, { 200, DISPLAY_HEIGHT - 240 }, 4, "ball"); //creates the ball
	GameObject& ball = Play::GetGameObject(objectId);
	ball.velocity = normalize({ 1, -1 }) * ballSpeed;
	if (linecount < 5) {
		displayScoreAmount = linecount;
	}
	else {
		displayScoreAmount = 5;
	}
	for (int i = 0; i < displayScoreAmount; i++) {
		displayArray[i] = highscoresArray[i];
	}
}
	void StepFrame(float elapsedTime) { //runs 60 times per second
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
			 
			if (ball.pos.y > DISPLAY_HEIGHT) {
				ball.velocity.y = ball.velocity.y * -1;
			}

			//if ball hits the bottom, display game over
			if(ball.pos.y < 0){   
				//sort(highscoresArray, highscoresArray + linecount, comp);
				//adds current score to the array
				//if (currentScore > highscoresArray[4]) { 
				//	highscoresArray[linecount - 1] = currentScore;
				//	sort(highscoresArray, highscoresArray + linecount, comp);
				//}
				//sort(highscoresArray, highscoresArray + linecount, comp);
				if (linecount == 0) {

					
					highscoresArray[0] = currentScore;
					std::string test = to_string(highscoresArray[0]);
					const char* icle = test.c_str();
					Play::DrawDebugText({ 100, 60 }, icle);
				}
				else{
					highscoresArray = resizeArray(highscoresArray, linecount, linecount + 1);
					highscoresArray[linecount] = currentScore;
					std::string test = to_string(highscoresArray[0]);
					const char* icle = test.c_str();
					Play::DrawDebugText({ 100, 60 }, icle);

				}
				linecount++;
				sort(highscoresArray, highscoresArray + linecount, comp);
				int displayScoreAmount;
				if (linecount < 5) {
					displayScoreAmount = linecount;
				}
				else {
					displayScoreAmount = 5;
				}
				for (int i = 0; i < displayScoreAmount; i++) {
					displayArray[i] = highscoresArray[i];
				}
				

				//resets everything
				currentScore = 0;
				Play::DestroyGameObject(ballIds[i]);
				const std::vector<int> brickIds = Play::CollectGameObjectIDsByType(TYPE_BRICK);
				for (int j = 0; j < brickIds.size(); j++) {
					Play::DestroyGameObject(brickIds[j]);
				}
				
					const int objectId = Play::CreateGameObject(ObjectType::TYPE_BALL, { 200, DISPLAY_HEIGHT - 240 }, 4, "ball"); //creates the ball
					GameObject& ball = Play::GetGameObject(objectId);
					ball.velocity = normalize({ 1, -1 }) * ballSpeed;
					SetupScene();
			}
			//if the ball collides with the paddle, bounces the ball 
			if (IsColliding(paddle,ball)) {
				ball.velocity.y = ball.velocity.y * -1;
			}
			//updates and draws the ball
		Play::UpdateGameObject(ball);
		Play::DrawObject(ball);		
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
		//sort(displayArray, displayArray + 5, comp);
		std::string score1 = std::to_string(displayArray[0]);
		const char* scoreOutput1 = score1.c_str();
		std::string score2 = std::to_string(displayArray[1]);
		const char* scoreOutput2 = score2.c_str();
		std::string score3 = std::to_string(displayArray[2]);
		const char* scoreOutput3 = score3.c_str();
		std::string score4 = std::to_string(displayArray[3]);
		const char* scoreOutput4 = score4.c_str();
		std::string score5 = std::to_string(displayArray[4]);
		const char* scoreOutput5 = score5.c_str();
		std::string score = std::to_string(currentScore);
		const char* scoreOutput = score.c_str();
		Play::DrawDebugText({ 930, 100 }, scoreOutput1);
		Play::DrawDebugText({ 930, 85 }, scoreOutput2);
		Play::DrawDebugText({ 930, 70 }, scoreOutput3);
		Play::DrawDebugText({ 930, 55 }, scoreOutput4);
		Play::DrawDebugText({ 930, 40 }, scoreOutput5);
		Play::DrawDebugText({ 30, 40 }, scoreOutput);

		

	}
	//adds scores to file and deletes array
	void ExitFunction(int linecount) {
		sort(highscoresArray, highscoresArray + linecount, comp);
		std::string text;
		fstream scoreFile("scores.txt");
		for (int k = 0; k < linecount; k++) {
			scoreFile << to_string(highscoresArray[k])  << "\n";
			text +=" " + to_string(highscoresArray[k]);
			//scoreFile << "why" << "\n";

		}
		//scoreFile << text << "\n";
		
		scoreFile.close();
		delete highscoresArray;
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

	