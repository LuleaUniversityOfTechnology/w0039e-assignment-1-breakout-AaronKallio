#define PLAY_USING_GAMEOBJECT_MANAGER
#include "Play.h"
#include "Paddle.h"
#include "constants.h"

Paddle paddle;

void DrawPaddle(Paddle& paddle) { //draws the paddle and makes it green
	
	
	Play::DrawRect({paddle.x,paddle.y}, { paddle.x + paddle.width,paddle.y + paddle.height }, Play::cGreen,TRUE);
}

void UpdatePaddle(Paddle& paddle) { //when the user imputs either the left or right key, the paddle moves but cannot move out of the play area
	
	bool left = Play::KeyDown(Play::KEY_LEFT);
	bool right = Play::KeyDown(Play::KEY_RIGHT);

	if (left) { //moves left
		if (paddle.x>= 12) {
			paddle.x -= 12;
		}
	}
	if (right) { //moves right
		if (paddle.x <= DISPLAY_WIDTH-140) {
			paddle.x += 12;
		}
	}

}


int Max(int number1, int number2) {  //returns the larger number 
	int result = (number1 > number2) ? number1 : number2;
	return result;

}

int Min(int number1, int number2) {  //returns the smaller number
	int result = (number1 < number2) ? number1 : number2;
	return result;

}

bool IsColliding(const Paddle& paddle, const Play::GameObject& obj) { //checks for collsion between the paddle and an object and returns true if collison occurs
	const float dx = obj.pos.x - Max(paddle.x, Min(obj.pos.x, paddle.x+paddle.width));
	const float dy = obj.pos.y - Max(paddle.y+paddle.height, Min(obj.pos.y, paddle.y));
	return (dx * dx + dy * dy) < (obj.radius * obj.radius);

}
