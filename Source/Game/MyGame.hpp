#pragma once
#include "../Core/Engine.hpp"
#include "../Core/IGame.hpp"
#include "SDL3/SDL_scancode.h"
class MyGame : public IGame {
private:
  SDL_FRect cuadrado; // Usamos FRect (float) para mayor precisión con deltaTime
  float velocidad = 200.0f; // 200 píxeles por segundo
  Engine *_engine = nullptr;

public:
  void OnInit(Engine &engine) override {
    _engine = &engine;
    // Inicializamos el cuadrado en el centro (o donde prefieras)
    cuadrado.x = 100.0f;
    cuadrado.y = 100.0f;
    cuadrado.w = 50.0f;
    cuadrado.h = 50.0f;
  }

  /* void OnUpdate(float deltaTime) override {
     // Movimiento automático a la derecha usando el Delta Time
     cuadrado.x += velocidad * deltaTime;

     // Rebote simple en los bordes (asumiendo 800 de ancho)
     if (cuadrado.x + cuadrado.w > 800.0f || cuadrado.x < 0) {
       velocidad *= -1; // Invertir dirección
     }*/
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
    cuadrado.x += moveX * velocidad * deltaTime;
    cuadrado.y += moveY * velocidad * deltaTime;
  };

  void OnRender(SDL_Renderer *renderer) override {
    // 1. Elegir el color del cuadrado (R, G, B, A)
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // Verde brillante

    // 2. Dibujar el cuadrado relleno
    SDL_RenderFillRect(renderer, &cuadrado);

    // Opcional: Dibujar solo el borde de otro cuadrado
    SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255); // Blanco
    SDL_FRect borde = {cuadrado.x - 2, cuadrado.y - 2, cuadrado.w + 4,
                       cuadrado.h + 4};
    SDL_RenderRect(renderer, &borde);
  }

  void OnCleanup() override {
    // Aquí no tenemos nada que liberar manualmente (de momento)
  }
};
