#define PLAY_USING_GAMEOBJECT_MANAGER
#include "Play.h"
#include "Paddle.h"
#include "constants.h"
//#include "constants.h"
//Play::Point2D paddle = 
Paddle paddle;
void DrawPaddle(Paddle& paddle) {
	
	//int height = 16;
	//int width = 128;
	Play::DrawRect({paddle.x,paddle.y}, { paddle.x + paddle.width,paddle.y + paddle.height }, Play::cGreen,TRUE);
}

void UpdatePaddle(Paddle& paddle) {
	
	bool left = Play::KeyDown(Play::KEY_LEFT);
	bool right = Play::KeyDown(Play::KEY_RIGHT);

	if (left) {
		if (paddle.x>= 12) {
			paddle.x -= 12;
		}
	}
	if (right) {
		if (paddle.x <= DISPLAY_WIDTH-140) {
			paddle.x += 12;
		}
	}

}

//bool IsColliding(Paddle paddle, ) {

//}
