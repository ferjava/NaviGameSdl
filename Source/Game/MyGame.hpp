#pragma once
#include "../Core/Engine.hpp"
#include "../Core/IGame.hpp"
#include "../Core/TextureManager.hpp"
#include "SDL3/SDL_rect.h"
#include "SDL3/SDL_render.h"
#include "SDL3/SDL_scancode.h"
#include <memory>
class MyGame : public IGame {
private:
  std::shared_ptr<SDL_Texture> sprite;
  float velocidad = 200.0f; // 200 píxeles por segundo
  Engine *_engine = nullptr;
  TextureManager _texture;

public:
  void OnInit(Engine &engine) override {
    _engine = &engine;
    _texture.Init(engine.GetRenderer());
    sprite = _texture.getTexture("assets/images/Naveplayer1.png");
  }
  void OnUpdate(float deltaTime) override {
    // 1. Obtenemos el estado actual del teclado
    const bool *keys = SDL_GetKeyboardState(NULL);

    // 2. Definimos el vector de movimiento
    float moveX = 0.0f;
    float moveY = 0.0f;

    // 3. Revisamos las teclas (W, A, S, D)
    if (keys[SDL_SCANCODE_W])
      moveY -= 1.0f;
    if (keys[SDL_SCANCODE_S])
      moveY += 1.0f;
    if (keys[SDL_SCANCODE_A])
      moveX -= 1.0f;
    if (keys[SDL_SCANCODE_D])
      moveX += 1.0f;
    if (keys[SDL_SCANCODE_ESCAPE]) // Para salir
      _engine->Exit();
    // 4. Aplicamos el movimiento al cuadrado
    // Multiplicamos por velocidad y deltaTime para que sea fluido
  };

  void OnRender(SDL_Renderer *renderer) override {
    // 1. Elegir el color del cuadrado (R, G, B, A)
    SDL_FRect dest;
    dest.x = 0.0f;
    dest.y = 0.0f;
    dest.w = 100.0f;
    dest.h = 100.0f;
    SDL_FRect dest2{190.0f, 190.0f, 200.0f, 200.0f};
    SDL_FRect source{300.0f, 0.0f, 100.0f, 90.0f};

    SDL_RenderTexture(_engine->GetRenderer(), sprite.get(), &source, &dest);
    SDL_RenderTexture(_engine->GetRenderer(), sprite.get(), &source, &dest2);
  }

  void OnCleanup() override {
    // Aquí no tenemos nada que liberar manualmente (de momento)
    _texture.ClearUnused();
  }
};
