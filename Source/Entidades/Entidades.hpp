#pragma once

/**
 * @brief : Archivo de declaracion de entidades del juego
 **/
#include "../Componentes/Componentes.hpp"
#include "../Game/GameContex.hpp"
#include "SDL3/SDL_render.h"
#include "Title/Entidades.hpp"
#include "Utils/Utils.hpp"
#include "entt/entity/fwd.hpp"
namespace Factory {
entt::entity createPlayer(entt::registry &reg, GameContext &ctx);
entt::entity createVersionText(entt::registry &reg, GameContext &ctx);
entt::entity creatBulletPlayer(entt::registry &reg, GameContext &ctx);
// entt::entity creatBulletEnemy(entt::registry &reg, GameContext &ctx);
entt::entity createEnemy(entt::registry &reg, GameContext &ctx);
entt::entity createExplosion(entt::registry &reg, GameContext &ctx);
void createGroupEnemysStraight(
    entt::registry &reg, GameContext &ctx,
    int salida); // Crea grupos de enemigos del grupo straight
entt::entity createScoreText(entt::registry &reg, GameContext &ctx);
void createIconVida(entt::registry &reg, GameContext &ctx);
entt::entity createGameOver(entt::registry &reg, GameContext &ctx);
entt::entity createEnemyRaptor(entt::registry &reg, GameContext &ctx);
entt::entity createBullet(entt::registry &reg, GameContext &ctx,
                          GC::Velocidad direccion);
} // namespace Factory
namespace Acciones {
void moveRaptor(entt::registry &reg, float dt);
}
