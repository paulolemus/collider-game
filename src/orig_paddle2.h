#ifndef COLLIDER_PADDLE2_MOVE_H
#define COLLIDER_PADDLE2_MOVE_H

/* Welcome to Pong-gramming!
 * 
 * This function is called every frame to control in which direction
 * your paddle should move. Here is a quick "How-to" guide for reference.
 *
 ************ Function parameters ***************
 * 
 * delta = The time elapsed since previous call to this function (frame delta)
 * Paddle p1 = The right-side paddle
 * Paddle p2 = The left-side paddle
 * Ball ball = The ball (duh)
 * void*& other = A pointer that you can use to store data between each
 *                call to this function.
 *
 * ******* Ball and Paddle Functions ************
 * get_pos().x
 * get_pos().y   
 * get_speed().x 
 * get_speed().y 
 * get_accel().x 
 * get_accel().y 
 *
 * *********How to move your Paddle *************
 *
 * So this function will return an int. Once you 
 * have decided which way your paddle can move, you can:
 *
 * return  1; := Paddle moves DOWN
 * return -1; := Paddle moves UP
 * return  0; := Paddle does not move
 * return  2; := Give control back to player
 *
 * Good luck!
 */


int paddle2_move(
    float   delta,
    const   Paddle p1,
    const   Paddle p2,
    const   Ball ball,
    void*&       other
) {

    float* ptr = static_cast<float*>(other);
    if (ptr != nullptr) {
        // can retrieve/change stored data
    }

    // Player controls this paddle
    return 2;
}

#endif // COLLIDER_PADDLE2_MOVE_H
