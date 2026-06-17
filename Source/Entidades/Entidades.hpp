#pragma once

/**
 * @brief : Archivo de declaracion de entidades del juego
 **/
#include "../Game/GameContex.hpp"
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
} // namespace Factory
