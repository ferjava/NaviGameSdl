#pragma once
#include "../../Game/GameContex.hpp"
#include "entt/entity/fwd.hpp"

namespace Factory {
namespace Title {

entt::entity createTitleImagen(entt::registry &reg, GameContext &ctx);
entt::entity createPress(entt::registry &reg, GameContext &ctx);

} // Namespace Title

} // namespace Factory
