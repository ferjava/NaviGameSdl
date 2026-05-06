#pragma once

#include "SDL3/SDL_render.h"
#include <memory>
#include <string>
#include <unordered_map>

class TextureManager {

public:
  void Init(SDL_Renderer *render) { _renderer = render; };
  void Add(SDL_Texture *texture, std::string &name);
  std::shared_ptr<SDL_Texture> getTexture(const std::string &path);
  void ClearUnused();

private:
  std::unordered_map<std::string, std::shared_ptr<SDL_Texture>> _textures;
  SDL_Renderer *_renderer;
};
