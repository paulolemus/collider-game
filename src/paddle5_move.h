#ifndef COLLIDER_PADDLE1_MOVE_H
#define COLLIDER_PADDLE1_MOVE_H

// - Time elapsed since last call
// Positions, speed, acceleration for:
// - Paddle Left
// - Paddle Right
// - Ball




// - Optional void*& that you can use to hold data between frames.


int paddle1_move(
    float   delta,
    const   Paddle p1,
    const   Paddle p2,
    const   Ball ball,
    void*&       other
) {

    float* ptr = static_cast<float*>(other);
    if (ptr != nullptr) {
        
    }

    float finalXPos = ball.get_pos().x;
    float finalYPos = ball.get_pos().y;

    if(ball.get_speed().x > 0){
	float xPos = ball.get_pos().x;
	float yPos = ball.get_pos().y;
	float xVel = ball.get_speed().x;
	float yVel = ball.get_speed().y;
	float xAcc = ball.get_accel().x;
	float yAcc = ball.get_accel().y;

	while(finalXPos < 1248){
	    

	    float deltaX = xVel * delta + 0.5 * xAcc * delta * delta;
	    if(yPos >= 703 && yVel > 0){
		yVel *= -1;
		yAcc *= -1;
	    }
	    if(yPos <= 17 && yVel < 0){
		yVel *= -1;
		yAcc *= -1;
	    }
	    float deltaY = yVel * delta + 0.5 * yAcc * delta * delta;
	    finalXPos += deltaX;
	    finalYPos += deltaY;
	}

	if(finalYPos < p1.get_pos().y - 5) return -1;
	else if(finalYPos > p1.get_pos().y + 5) return 1;
	else return 0;
    }

    else if(ball.get_speed().x < 0){
	if(ball.get_pos().y > p1.get_pos().y) return 1;
	else if(ball.get_pos().y < p1.get_pos().y) return -1;
	else return 0;
    }

    
/*
    if (ball.get_speed().y != 0) {
        if (ball.get_pos().y > p1.get_pos().y) {
            return 1;
        } else if (ball.get_pos().y < p1.get_pos().y) {
            return -1;
        } else {
            return 0;
        }
    }
    */
}

#endif // COLLIDER_PADDLE1_MOVE_H
