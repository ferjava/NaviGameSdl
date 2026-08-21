#include "Utils.hpp"
#include <random>
//
//@brief Obtiene valor aleatorio de entre dos valores
//@param Valor_min valor minimo
//@param Valor_max Valor Maximo
//@return Valor aleatorio
//
int Utils::Dado(int Valor_min, int Valor_max) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<int> dado(Valor_min, Valor_max);
  return dado(gen);
}
