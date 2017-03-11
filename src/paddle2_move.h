#ifndef COLLIDER_PADDLE2_MOVE_H
#define COLLIDER_PADDLE2_MOVE_H

#include <cmath>

int paddle2_move(
    float           delta,
    const Paddle    p1,
    const Paddle    p2,
    const Ball      ball,
    void*&          other
) {
    if (ball.get_speed().y != 0) {

        auto speed_addition = ball.get_speed().y * 1.0;
        auto ball_x = ball.get_pos().x;
        auto ball_y = ball.get_pos().y;

        if (ball_x < 640) {
            std::cout << "PING" << std::endl;
            if (ball_y + speed_addition > 1280) {
                ball_y = 1280 - (static_cast<int>(ball_y + speed_addition) % 1280);
            }
            else if (ball_y + speed_addition < 0) {
                ball_y = 0 + (static_cast<int>(ball_y + speed_addition) % 1280);
            }
        }

        if (ball_y > p2.get_pos().y) {
            return 1;
        } else if (ball_y < p2.get_pos().y) {
            return -1;
        } else {
            return 0;
        }
    }
}

#endif // COLLIDER_PADDLE2_MOVE_H
