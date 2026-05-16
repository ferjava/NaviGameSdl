#pragma once

/**
 * @brief : Archivo de declaracion de entidades del juego
 **/
#include "../Game/GameContex.hpp"
#include "entt/entity/fwd.hpp"
namespace Factory {
entt::entity createPlayer(entt::registry &reg, GameContext &ctx);
entt::entity createVersionText(entt::registry &reg, GameContext &ctx);
entt::entity creatBullet(entt::registry &reg, GameContext &ctx);
} // namespace Factory
