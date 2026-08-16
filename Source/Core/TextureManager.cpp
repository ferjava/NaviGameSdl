#include "TextureManager.hpp"
#include "SDL3/SDL_error.h"
#include "SDL3/SDL_render.h"
#include "SDL3_image/SDL_image.h"
#include <iostream>
#include <memory>

std::shared_ptr<SDL_Texture>
TextureManager::getTexture(const std::string &path) {
  // 1. Comprobamos si lara cargamos antes
  auto it = _textures.find(path);
  if (it != _textures.end()) {
    return it->second; // devolvemos el que existe
  }
  // 2 Sino exixte la Textura
  SDL_Texture *rawtexture = IMG_LoadTexture(_renderer, path.c_str());
  if (!rawtexture) {
    std::cerr << "Error cargando :" << path << "->" << SDL_GetError()
              << std::endl;
    return nullptr;
  }
  // 3 Envolvemos la texture con su SDL_DestroyTexture
  std::shared_ptr<SDL_Texture> smartTex(rawtexture, SDL_DestroyTexture);
  // 4. La guardamos en el mapa y la devolvemos
  _textures[path] = smartTex;
  return smartTex;
}

void TextureManager::ClearUnused() {
  // Elimina las texturas que nadie mas este usando
  // count==1

  for (auto it = _textures.begin(); it != _textures.end();) {
    if (it->second.use_count() == 1) {
      it = _textures.erase(it);

    } else {
      ++it;
    }
  }
}
// Añadimos una textura creada por nosotros al textureManager (Texto , circulos
// ,cuadrados )
void TextureManager::Add(SDL_Texture *texture, const std::string &name) {

  if (texture != nullptr) {
    std::shared_ptr<SDL_Texture> smartTex(texture, SDL_DestroyTexture);
    _textures[name] = smartTex;
  }
}
