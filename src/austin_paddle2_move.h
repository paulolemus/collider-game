#ifndef COLLIDER_PADDLE2_MOVE_H
#define COLLIDER_PADDLE2_MOVE_H

#include <iostream>
#include <cmath>

bool eq_epsilon(double operand, double target, double epsilon) {
    return (operand <= target + epsilon)
        && (operand >= target - epsilon);
}




double solve_quadratic_eq(
    double A,
    double B,
    double C
) {
    auto neg_B  = -B;
    auto discrim = B*B - 4.0*A*C;

    // If 0, 1 solution
    if (eq_epsilon(discrim, 0.0, 0.01)) {
        discrim = 0.0;
        return neg_B / (2.0 * A);

    // If +, 2 solutions
    } else if (discrim > 0.0) {
        return (neg_B + std::sqrt(discrim)) / (2.0 * A);

    // If -, no real solutions
    } else {
        return 0;
    }
}

                        

int paddle2_move(
    float           delta,
    const Paddle    p1,
    const Paddle    p2,
    const Ball      ball,
    void*&          other
) {
    // If moving towards us, yes!
    if (ball.get_speed().x <= 0) {
        std::cout << ball.get_accel().x << ' ';
        std::cout << ball.get_speed().x << ' ';
        std::cout << ball.get_pos().x << std::endl;

        auto time_x = (32 - ball.get_pos().x) / ball.get_speed().x;

        auto expected_pos_y =
            ball.get_pos().y
            - ball.get_speed().y * time_x
            - (0.5) * ball.get_accel().y * time_x * time_x;

        while (expected_pos_y > 1280) {
            expected_pos_y -= 1280;
        }


        std::cout << "time_x: " << time_x << std::endl;
        std::cout << "expected_pos_y: " << expected_pos_y << std::endl;

        if (p2.get_pos().y > expected_pos_y) {
            return 1;
        } else if (p2.get_pos().y < expected_pos.y) {
            return -1;
        } else {
            return 0;
        }

    // Otherwise, moving away from us.
    } else {

        return -1;
    }
}

#endif // COLLIDER_PADDLE2_MOVE_H
