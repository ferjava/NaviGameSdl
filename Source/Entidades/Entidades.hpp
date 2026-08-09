#pragma once

/**
 * @brief : Archivo de declaracion de entidades del juego
 **/
#include "../Game/GameContex.hpp"
#include "SDL3/SDL_render.h"
#include "entt/entity/fwd.hpp"
namespace Factory {
entt::entity createPlayer(entt::registry &reg, GameContext &ctx);
entt::entity createVersionText(entt::registry &reg, GameContext &ctx);
entt::entity creatBulletPlayer(entt::registry &reg, GameContext &ctx);
entt::entity creatBulletEnemy(entt::registry &reg, GameContext &ctx);
entt::entity createEnemy(entt::registry &reg, GameContext &ctx);
entt::entity createExplosion(entt::registry &reg, GameContext &ctx);
void createGroupEnemysStraight(
    entt::registry &reg, GameContext &ctx,
    int salida); // Crea grupos de enemigos del grupo straight
entt::entity createScoreText(entt::registry &reg, GameContext &ctx);
} // namespace Factory
namespace Efecto {
void Blink(SDL_Texture *sprite, float time, GameContext &ctx);
} // namespace Efecto
