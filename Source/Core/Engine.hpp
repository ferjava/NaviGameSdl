#pragma once

///
///@brief: Esta archivo contiene la contiene la declaracion de la clase engine
/// la cual es la encargada :
/// -Inicializar SDL con SDLContext
/// -Crear y Mantener una ventana y un redender
///
///@Version:0.0.1

#include "IGame.hpp"
#include "SDLContext.hpp"
#include <SDL3/SDL.h>
#include <memory>
#include <string>

using UniqueWindow = std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)>;
using UniqueRenderer =
    std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)>;

class Engine {
public:
  Engine(std::string title, int witdh, int height);

private:
  SDLContext _inicializador;
  int _witdh, _height;
  std::string _title;
  bool is_running = false;
  UniqueWindow _window;
  UniqueRenderer _renderer;
  std::unique_ptr<IGame> _game;

public:
  // Engine(std::string title, int witdh, int height);
  // Acciones
  //
  void Exit();
  // Getters
  int GetWindowHeight() const;
  float GetFWindowHeight() const;
  int GetWindowWidth() const;
  float GetFWindowWidth() const;
  SDL_Renderer *GetRenderer() { return _renderer.get(); };
  template <typename T> void Run() {
    _game = std::make_unique<T>();
    _game->OnInit(*this); // Inicialización del usuario

    // Variables para el tiempo
    Uint64 last_time = SDL_GetPerformanceCounter();
    Uint64 frequency = SDL_GetPerformanceFrequency();
    float delta_time = 0.0f;

    is_running = true;

    while (is_running) {
      // --- 1. Cálculo del Delta Time ---
      Uint64 current_time = SDL_GetPerformanceCounter();
      // Diferencia de ticks convertida a segundos (float)
      delta_time = static_cast<float>(current_time - last_time) /
                   static_cast<float>(frequency);
      last_time = current_time;

      // Limitar el delta_time para evitar "saltos" si la ventana se congela
      if (delta_time > 0.1f)
        delta_time = 0.1f;

      // --- 2. Procesar Eventos ---
      HandleEvents();

      // --- 3. Actualizar Lógica (pasando el tiempo) ---
      _game->OnUpdate(delta_time);

      // --- 4. Renderizado ---
      SDL_SetRenderDrawColor(_renderer.get(), 20, 20, 20,
                             255); // Fondo gris oscuro
      SDL_RenderClear(_renderer.get());

      _game->OnRender(_renderer.get());

      SDL_RenderPresent(_renderer.get());
    }

    _game->OnCleanup();
  };

private:
  void HandleEvents();

}; // End class
