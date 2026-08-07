#include "MainScene.hpp"

#include "../Entidades/Entidades.hpp"
#include "../Sistemas/Sistemas.hpp"
#include "GameConfig.hpp"
#include "GameContex.hpp"
#include "NaviGame.hpp"
#include "SDL3/SDL_keyboard.h"
#include "SDL3/SDL_render.h"
#include "SDL3/SDL_scancode.h"
#include <random>
float next_oleada = 0.0f;
std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<int> dado(1, 6);
entt::entity puntuacion;
int oleada_actual = 0;
MainScene::MainScene(NaviGame *game) : _game(game) {}

bool MainScene::OnInit() {
  // Creamos una entityi)
  _texture.Init(NaviGame::ctx.render);
  NaviGame::ctx.tm = &_texture;
  Factory::createPlayer(_registro, NaviGame::ctx);
  // Factory::createGroupEnemysStraight(_registro, NaviGame::ctx, 1);
  Factory::createVersionText(_registro, NaviGame::ctx);
  return true;
}
void MainScene::OnUpdate(float dt) {

  const bool *keys = SDL_GetKeyboardState(NULL);
  if (keys[SDL_SCANCODE_ESCAPE])
    OnExit();
  // temporizador oleada
  next_oleada += dt;
  // crear un limite de oleadas
  if (oleada_actual < Game::NUMERO_DE_OLEADAS) {
    if (next_oleada >= Game::TIME_OLEADA) {
      next_oleada = 0.0f; // reinicio;
      Factory::createGroupEnemysStraight(_registro, NaviGame::ctx, dado(gen));
      oleada_actual++;
    }
  }
  Sistema::IA::GeneraBalas(_registro, dt);
  Sistema::Movimiento(_registro, dt);

  Sistema::Entrada_Teclado(_registro, dt);
  Sistema::Colisones(_registro);
  Sistema::Animaciones(_registro, dt);
  puntuacion = Factory::createScoreText(_registro, NaviGame::ctx);
  Sistema::Frontera(_registro, NaviGame::ctx.pantalla);
}
void MainScene::OnRender(SDL_Renderer *renderer) {

  renderer = NaviGame::ctx.render;
  Sistema::Dibujado(_registro, renderer);
  // Se necesita borrar el texto para volver a crearlo
  if (_registro.valid(puntuacion)) {
    _registro.destroy(puntuacion);
  }
}
void MainScene::OnExit() {
  // Liberamos los punteros
  _game->getEngine()->Exit();
}
void MainScene::OnCleanUp() {}
