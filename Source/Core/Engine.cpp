#include "Engine.hpp"
#include "SDL3/SDL_error.h"
#include "SDL3/SDL_render.h"
#include "SDL3/SDL_video.h"
#include "SDLContext.hpp"

Engine::Engine(std::string title, int width, int height)
    : _inicializador(), _witdh(width), _height(height), _title(title),
      _window(nullptr, SDL_DestroyWindow),    // Pasamos la función de limpieza
      _renderer(nullptr, SDL_DestroyRenderer) // Pasamos la función de limpieza
{
  _window.reset(SDL_CreateWindow(_title.c_str(), _witdh, _height, 0));
  if (!_window)
    throw std::runtime_error(SDL_GetError());

  _renderer.reset(SDL_CreateRenderer(_window.get(), NULL));
  if (!_renderer)
    throw std::runtime_error(SDL_GetError());
  SDL_SetRenderLogicalPresentation(_renderer.get(), 1920, 1080,
                                   SDL_LOGICAL_PRESENTATION_LETTERBOX);
  is_running = true;
}
void Engine::HandleEvents() {
  SDL_Event event;

  // SDL_PollEvent retorna true mientras haya eventos en la cola
  while (SDL_PollEvent(&event)) {
    if (event.type == SDL_EVENT_QUIT) {
      is_running = false;
    }

    if (event.type == SDL_EVENT_WINDOW_CLOSE_REQUESTED) {
      is_running = false;
    }

    // Aquí podrías pasar el evento a un InputManager
    // o directamente al objeto game si lo necesitas.
  }
}

void Engine::Exit() { is_running = false; }
