#include "../../Componentes/Componentes.hpp"
#include "Entidades.hpp"
#include "SDL3/SDL_rect.h"
#include "entt/entity/fwd.hpp"
#include "entt/entt.hpp"
entt::entity Factory::Title::createTitleImagen(entt::registry &reg,
                                               GameContext &ctx) {
  auto title_sp = ctx.tm->getTexture("assets/images/Title.png");
  SDL_FRect title_src{0.0f, 0.0f, (float)title_sp->w, (float)title_sp->h};
  SDL_FRect title_dest{0.0f, 0.0f, (float)title_sp->w * 2,
                       (float)title_sp->h * 2};
  auto title_img = reg.create();
  reg.emplace<GC::Posicion>(title_img, ctx.pantalla.w / 2 - (float)title_sp->w,
                            ctx.pantalla.h / 3 - (float)title_sp->h);
  reg.emplace<GC::Sprite>(title_img, title_sp, title_src, title_dest);
  reg.emplace<::Title::TitleImage>(title_img);

  return title_img;
}
