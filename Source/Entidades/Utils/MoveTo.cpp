#include "../../Game/GameConfig.hpp"
#include "Utils.hpp"
///
///@brief esta funcion se encarga de mover de un Vec2 pos a Vec2 destino con una
/// Velocidad (Vec2)
///
///@param  pos = GC::Posicion (Vec2) posicion donde esta el objeto que vamos a
/// mover
///@param _dest = Posicion en 2d donde llegaremos
///@param vel = velocidad (que coombinada con pos nos da la direccion )
///@return false no se ha alcanzado el punto
/// return true si se ha alcanzado la posicion

bool Utils::Move_To(GC::Posicion &pos, GC::Posicion &_dest,
                    GC::Velocidad &vel) {
  float dx = _dest.X - pos.X;
  float dy = _dest.Y - pos.Y;
  float distancia = std::hypot(dx, dy);
  if (distancia < 0.5f)
    return true;

  pos.X += (dx / distancia);
  pos.Y += (dy / distancia);
  return false;
}
