#pragma once

namespace GC // Nnamespace GC (GameComponentes)
{

struct Posicion //< Determina uan poscion 2D (eje X y eje Y)
{
  float X;
  float Y;
};
//@brief  Determina cuantos pixel se movera la entidad en cada
// deltaTime
struct Velocidad

{
  float Vx; //< Velocidad en eje X
  float Vy; //< Velocidad en eje Y
};

} // namespace GC
