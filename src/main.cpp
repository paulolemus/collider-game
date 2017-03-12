#include <iostream>
#include <string>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <thread>

#include "SDL2/SDL.h"
#include "SDL2/SDL_mixer.h"

#include "base/system.h"
#include "base/TexturePool.h"
#include "base/Text.h"
#include "Paddle.h"
#include "Ball.h"

#include "paddle1_move.h"
#include "paddle2_move.h"

///Mix_Music *gMusic = nullptr;
///Mix_Chunk *gScratch = nullptr;
///Mix_Chunk *gHigh = nullptr;
///Mix_Chunk *gMedium = nullptr;
///Mix_Chunk *gLow = nullptr;

int check_ball(Ball& ball) {
  if (ball.get_pos().x < 8) {
    return -1;
  } else if (ball.get_pos().x > 1280 - 32 + 8) {
    return 1;
  }
  return 0;
}

int main(int argc, char** argv) {
  int p1score = 0;
  int p2score = 0;
  std::string score;

  std::srand(std::time(NULL));
  // Setup base system.
  BaseSystem base_system("Collision Pong", 1280, 720, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
  // Setup texture pool with "img" directory
  TexturePool tp(base_system.get_renderer(), "img");
  // Setup textures.
  tp.load_texture("bg.png");
  tp.load_texture("square.png");
  tp.load_texture("paddle_blue.png");
  tp.load_texture("paddle_red.png");
  tp.load_texture("background.png");
  tp.load_texture("ball.png");
  // Setup text/TTF.
  Font dejavu_sans_mono("font/DejaVu_Sans/DejaVuSansMono.ttf", 42);
  // Setup the text.
  Text text(base_system.get_renderer(), dejavu_sans_mono, {128, 128, 0, 128});
  // Setup the text texture.
  SDL_Texture* text_texture;

  // Initialize the audio channel.
  ///if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
  ///  std::cout << "SDL_mixer could not initialize! SDL_mixer error: " << Mix_GetError() << std::endl;
  ///  throw std::runtime_error(Mix_GetError());
  ///}

  // Load the music.
  ///gMusic = Mix_LoadMUS("sound/music.mp3");
  ///gScratch = Mix_LoadWAV("sound/scratch.wav");
  ///gHigh = Mix_LoadWAV("sound/high.wav");
  ///gMedium = Mix_LoadWAV("sound/medium.wav");
  ///gLow = Mix_LoadWAV("sound/low.wav");

  // Set the renderer draw mode.
  SDL_SetRenderDrawBlendMode(base_system.get_renderer(), SDL_BLENDMODE_BLEND);

  // Setup the paddles and the bal.
  Paddle p2(32, 720/2 - 32, tp.get("paddle_blue.png"));
  Paddle p1(1280 - 48, 720/2 - 32, tp.get("paddle_red.png"));
  Ball ball(1280/2 - 8, 720/2 - 8, tp.get("ball.png"));

  // Setup the event.
  SDL_Event e;
  bool done = false;

  // Setup the timer.
  auto t1 = std::chrono::high_resolution_clock::now();
  auto t2 = std::chrono::high_resolution_clock::now();
  std::chrono::duration<float> delta = t2-t1;

  int fps = 0;

  // Setup the SDL Key input.
  const auto * keys = SDL_GetKeyboardState(NULL);

  // Start playing the music.
  ///Mix_PlayMusic(gMusic, -1);

  auto switch_t1 = std::chrono::high_resolution_clock::now();
  auto switch_t2 = std::chrono::high_resolution_clock::now();
  std::chrono::duration<float> switch_delta = std::chrono::duration<float>(std::chrono::seconds(5));

  void* paddle1_data = NULL; 
  void* paddle2_data = NULL; 

  // Main loop.
  while(!done) {
    // While we are getting basic events,
    // quite if we get a SDL_QUIT signal.
    while(SDL_PollEvent(&e)) {
      if(e.type == SDL_QUIT) {
        done = true;
      }    
    }

    SDL_PumpEvents();

    // Get input

    // Attach the controls to speed changes.
    if (keys[SDL_SCANCODE_UP]) {
      p1.set_speed(0, -60000 * delta.count());
    }
    if (keys[SDL_SCANCODE_DOWN]) {
      p1.set_speed(0, 60000 * delta.count());
    }
    if (keys[SDL_SCANCODE_LEFT]) {
      p1.set_speed(-60000 * delta.count(), 0);
    }
    if (keys[SDL_SCANCODE_RIGHT]) {
      p1.set_speed(60000 * delta.count(), 0);
    }

    if (!keys[SDL_SCANCODE_UP] &&
        !keys[SDL_SCANCODE_DOWN] &&
        !keys[SDL_SCANCODE_LEFT] &&
        !keys[SDL_SCANCODE_RIGHT]) {
      p1.set_speed(0, 0);
    }

    if (keys[SDL_SCANCODE_W]) {
      p2.set_speed(0, -60000 * delta.count());
    }
    if (keys[SDL_SCANCODE_S]) {
      p2.set_speed(0, 60000 * delta.count());
    }
    if (keys[SDL_SCANCODE_A]) {
      p2.set_speed(-60000 * delta.count(), 0);
    }
    if (keys[SDL_SCANCODE_D]) {
      p2.set_speed(60000 * delta.count(), 0);
    }

    if (!keys[SDL_SCANCODE_W] &&
        !keys[SDL_SCANCODE_S] &&
        !keys[SDL_SCANCODE_A] &&
        !keys[SDL_SCANCODE_D]) {
      p2.set_speed(0, 0);
    }

    switch_t1 = switch_t2;
    switch_t2 = std::chrono::high_resolution_clock::now();
    switch_delta += switch_t2-switch_t1;

    auto switch_duration = std::chrono::duration_cast<std::chrono::milliseconds>(switch_delta);

    // Pressing space or enter changes the ball acceleration randomly.
    if (keys[SDL_SCANCODE_SPACE]) {
      if (switch_duration.count() > 5000) {
        ball.inv_speed(true, true);
        ball.set_accel(std::rand() % 300 - 150, std::rand() % 300 - 150);
        switch_delta = std::chrono::duration<float>::zero();
      }
    }

    if (keys[SDL_SCANCODE_KP_ENTER]) {
      if (switch_duration.count() > 5000) {
        ball.inv_speed(true, true);
        ball.set_accel(std::rand() % 300 - 150, std::rand() % 300 - 150);
        switch_delta = std::chrono::duration<float>::zero();
      }
    }

    if (keys[SDL_SCANCODE_ESCAPE]) {
      ball.set_pos(1280/2 - 8, 720/2 - 8);
      ball.set_speed(0,0);
      ball.set_accel(0,0);
    }

    if (keys[SDL_SCANCODE_R]) {
      p1score = 0;
      p2score = 0;
    }

    int move_p1 = paddle1_move(delta.count(), p1, p2, ball, paddle1_data);
    int move_p2 = paddle2_move(delta.count(), p1, p2, ball, paddle2_data);

    if (move_p1 == 1) {
      p1.set_speed(0, 60000 * delta.count());
    } else if (move_p1 == -1) {
      p1.set_speed(0, -60000 * delta.count());
    } else if (move_p1 == 0) {
      p1.set_speed(0, 0);
    }

    if (move_p2 == 1) {
      p2.set_speed(0, 60000 * delta.count());
    } else if (move_p2 == -1) {
      p2.set_speed(0, -60000 * delta.count());
    } else if (move_p2 == 0) {
      p2.set_speed(0, 0);
    }

    // Update the balls.
    p1.update(delta.count());
    p2.update(delta.count());

    vec3 collision_info;
    float remaining_time = delta.count();
   
    // Get the collision information.
    collision_info = swept_collision(static_cast<Unit>(Ball(ball)), p1, delta.count());
    if (collision_info.z < delta.count()/49.0) {
      remaining_time = 1.0f - collision_info.z;
      ball.update(collision_info.z * delta.count());
      int speedx = static_cast<int>(ball.get_speed().x + 1);
        if (speedx < 0) speedx = -speedx;
      ball.inv_accel(true, false);
      ball.inv_speed(true, false);
      ball.add_speed(std::rand() % speedx - speedx / 2, p1.get_speed().y);
      ball.update(remaining_time * delta.count());
      ///Mix_PlayChannel(-1, gHigh, 0);
      std::cout << "P1\n";
      std::cout << "RIGHT COLLISION TIME: " << collision_info.z << std::endl;
    } else {
      collision_info = swept_collision(static_cast<Unit>(Ball(ball)), p2, delta.count());
      if (collision_info.z < delta.count()/49.0) {
        remaining_time = 1.0f - collision_info.z;
        ball.update(collision_info.z * delta.count());
        int speedx = static_cast<int>(ball.get_speed().x + 1);
          if (speedx < 0) speedx = -speedx;
        ball.inv_accel(true, false);
        ball.inv_speed(true, false);
        ball.add_speed(std::rand() % speedx - speedx/2, p2.get_speed().y);
        ball.update(remaining_time * delta.count());
        ///Mix_PlayChannel(-1, gLow, 0);
        std::cout << "P2\n";
        std::cout << "LEFT COLLISION TIME: " << collision_info.z << std::endl;
      } else {
        ball.update(delta.count());
      }
    }

    //CALCULATE THE VOLUME ACCORDING TO THE SPEED
    float speed = ball.get_speed().x * ball.get_speed().x +
                  ball.get_speed().y * ball.get_speed().y;
    if (speed < 0) {
      speed = -speed;
    }
    speed = std::sqrt(speed);
    int volume = static_cast<int>((speed / 2000.0) * 128.0 + 26.0);
    

    // Set the volume according to the music.
    ///Mix_VolumeMusic(volume);
    
    if(check_ball(ball) > 0) {
      //P2 SCORES
      ++p2score;
      ball.set_pos(1280/2 - 8, 720/2 - 8);
      ball.set_speed(0,0);
      ball.set_accel(0,0);
      ///Mix_PlayChannel(-1, gScratch, 0);
    } else if (check_ball(ball) < 0) {
      //P1 SCORES
      ++p1score;
      ball.set_pos(1280/2 - 8, 720/2 - 8);
      ball.set_speed(0,0);
      ball.set_accel(0,0);
      ///Mix_PlayChannel(-1, gScratch, 0);
    }

    // Create the score string.
    score = std::to_string(p2score).append(std::string(" | ")).append(std::to_string(p1score));
    // Render the score string.
    text.render_text(score);
    // Set the text texture.
    text_texture = text.get_texture();
    // Set the texture blend model.
    SDL_SetTextureBlendMode(text_texture, SDL_BLENDMODE_BLEND);

    // Sleep until we're done with the frame.
    std::this_thread::sleep_until(t2 + std::chrono::microseconds(16666));

    delta = std::chrono::high_resolution_clock::now() - t2;
    t2 = std::chrono::high_resolution_clock::now();

    if (std::chrono::duration_cast<std::chrono::milliseconds>(t2-t1).count() >= 1000) {
      std::cout << "DELTA: " << delta.count() << std::endl;
      std::cout << "FPS: " << fps << std::endl;
      std::cout << "========== BALL==========" << std::endl;
      std::cout << "POS (X,Y) " << "(" << ball.get_pos().x << "," << ball.get_pos().y << ")" << std::endl;
      std::cout << "SPEED (X,Y) " << "(" << ball.get_speed().x << "," << ball.get_speed().y << ")" << std::endl;
      std::cout << "ACCEL (X,Y) " << "(" << ball.get_accel().x << "," << ball.get_accel().y << ")\n" << std::endl;

      fps = 0;
      t1 = t2;
    }

    // Set the text rectange to render in.
    SDL_Rect text_rect = {1280/2 - text.get_dim().x/2, 720/2 - text.get_dim().y/2, text.get_dim().x, text.get_dim().y};

    //Render unit and background
    SDL_RenderClear(base_system.get_renderer());
    SDL_RenderCopy(base_system.get_renderer(), tp.get("background.png"), nullptr, nullptr);
    SDL_RenderCopy(base_system.get_renderer(), text_texture, nullptr, &text_rect);
    SDL_RenderCopy(base_system.get_renderer(), p1.get_texture(), nullptr, p1.get_rect());
    SDL_RenderCopy(base_system.get_renderer(), p2.get_texture(), nullptr, p2.get_rect());
    SDL_RenderCopy(base_system.get_renderer(), ball.get_texture(), nullptr, ball.get_rect());
    
    SDL_RenderPresent(base_system.get_renderer());

    ++fps;
  }

  // Free the music and the sound effects.
  ///Mix_FreeChunk(gScratch);
  ///Mix_FreeChunk(gHigh);
  ///Mix_FreeChunk(gMedium);
  ///Mix_FreeChunk(gLow);
  ///gScratch = nullptr;
  ///gHigh = nullptr;
  ///gMedium = nullptr;
  ///gLow = nullptr;

  ///Mix_FreeMusic(gMusic);
  ///gMusic = nullptr;


  return 0;
}
