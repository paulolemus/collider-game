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
    if (ball.get_speed().y != 0) {
        if (ball.get_pos().y > p1.get_pos().y) {
            return 1;
        } else if (ball.get_pos().y < p1.get_pos().y) {
            return -1;
        } else {
            return 0;
        }
    }
}

#endif // COLLIDER_PADDLE1_MOVE_H
