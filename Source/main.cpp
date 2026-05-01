#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

int main(int argc, char *argv[]) {
  // 1. Inicializar SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    SDL_Log("No se pudo inicializar SDL: %s", SDL_GetError());
    return 1;
  }

  // 2. Crear Ventana y Renderizador (SDL3 simplifica esto)
  SDL_Window *window = nullptr;
  SDL_Renderer *renderer = nullptr;
  if (SDL_CreateWindowAndRenderer("Ejemplo SDL3", 800, 600, 0, &window,
                                  &renderer) < 0) {
    SDL_Log("No se pudo crear ventana/render: %s", SDL_GetError());
    return 1;
  }

  bool running = true;
  SDL_Event event;

  // 3. Bucle principal
  while (running) {
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_EVENT_QUIT) {
        running = false;
      }
    }

    // 4. Dibujar
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255); // Azul
    SDL_RenderClear(renderer);                        // Limpiar pantalla
    SDL_RenderPresent(renderer);                      // Mostrar
  }

  // 5. Limpieza
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
