#include "Core/Engine.hpp"
#include "Game/MyGame.hpp"
#include "Version.h"
#include <exception>
int main(int argc, char *argv[]) {
  try {
    // 1. Crear el motor
    Engine engine(PROJECT_NAME, 800, 600);

    // 2. Crear el juego

    // 3. ¡A correr!
    engine.Run<MyGame>();

  } catch (const std::exception &e) {
    SDL_Log("Error: %s", e.what());
    return -1;
  }
  return 0;
}
