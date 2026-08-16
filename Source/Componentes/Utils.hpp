#pragma once

#include "../Game/GameContex.hpp"
#include "entt/entity/fwd.hpp"
#include "entt/entt.hpp"
#include <functional>
#ifndef INCLUDEComponentesUtilsUtilshpp_
#define INCLUDEComponentesUtilsUtilshpp_

namespace Utils {

/// Tag,s//////
struct TimeExpiredTag {};

////////////////////////////////
/// componentes
struct Temporizador {
  float tRestante;
  float tDuracion;
  bool Repite = false;
  bool Terminado = false;
  // Opcional callback para ejecutar cuando se termine la cuenta
  std::function<void(entt::entity &enti)> on_timeout = nullptr;
};

} // namespace Utils

#endif // INCLUDEComponentesUtilsUtils.hpp_
