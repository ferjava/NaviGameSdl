#include "MainScene.hpp"

#include "../Entidades/Entidades.hpp"
#include "../Sistemas/Sistemas.hpp"
#include "GameConfig.hpp"
#include "GameContex.hpp"
#include "MainScene.hpp"
#include "NaviGame.hpp"
#include "SDL3/SDL_keyboard.h"
#include "SDL3/SDL_render.h"
#include "SDL3/SDL_scancode.h"
float next_oleada = 0.0f;
entt::entity puntuacion;
int oleada_actual = 0;
MainScene::MainScene(NaviGame *game) : _game(game) {}

bool MainScene::OnInit() {
  // Creamos una entity)
  _texture.Init(NaviGame::ctx.render);
  NaviGame::ctx.tm = &_texture;
  // Retraso para dar ttiemp a la cargta
  _registro.clear();
  Game::Player::SCORE = 0.0f;
  oleada_actual = 0;
  OnStart();

  return true;
}
void MainScene::OnUpdate(float dt) {
  // Limpiamos las entidades para eliminar
  for (auto enti : NaviGame::ctx.elimina_entidad) {
    if (_registro.valid(enti)) {
      _registro.destroy(enti);
    }
  }
  const bool *keys = SDL_GetKeyboardState(NULL);
  if (keys[SDL_SCANCODE_ESCAPE])
    OnMenuIntro();
  // temporizador oleada
  next_oleada += dt;
  // crear un limite de oleadas
  if (oleada_actual < Game::NUMERO_DE_OLEADAS) {
    if (next_oleada >= Game::TIME_OLEADA) {
      next_oleada = 0.0f; // reinicio;
      Factory::createGroupEnemysStraight(_registro, NaviGame::ctx,
                                         Utils::Dado(1, 6));
      if (oleada_actual % 3 == 0 && oleada_actual != 0) {
        Factory::createEnemyRaptor(_registro, NaviGame::ctx);
      }
      oleada_actual++;
    }
  } else if (oleada_actual == Game::NUMERO_DE_OLEADAS) {

    Factory::creatEnemyBoss(_registro, NaviGame::ctx);
    oleada_actual++;
  }

  Sistema::IA::UpdateSystemIA(_registro, dt, NaviGame::ctx);
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
void MainScene::OnMenuIntro() {
  if (!NaviGame::ctx.director->isEmpty())
    NaviGame::ctx.director->Pop();
}
void MainScene::OnExit() { _registro.clear(); }
void MainScene::OnCleanUp() {}
void MainScene::OnStart() {
  _registro.clear();
  Factory::createVersionText(_registro, NaviGame::ctx);
  Factory::createIconVida(_registro, NaviGame::ctx);
  Factory::createPlayer(_registro, NaviGame::ctx);
  // Factory::creatEnemyBoss(_registro, NaviGame::ctx);
}
