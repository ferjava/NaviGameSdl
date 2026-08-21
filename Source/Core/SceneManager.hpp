#pragma once
#ifndef __SCENEMANAGER__HPP__
#define __SCENEMANAGER__HPP__
#include "IScene.hpp"
#include <memory>
#include <vector>
class SceneManager {
private:
  std::vector<std::unique_ptr<IScene>> stack;
  std::unique_ptr<IScene> pendiente = nullptr;
  bool deberiaLimpiar = false;

public:
  void Push(std::unique_ptr<IScene>
                newscene); ///< Añade una escena encima de la anterior
  void Pop();              ///< Quita la escena nueva y vuelve a class anterior
  void Change(std::unique_ptr<IScene> newscene);
  ///< Cambia radicalmente de scene
  IScene *Current(); ///< Scene actual
  bool isEmpty() const { return stack.empty(); };
  void ChangePending();
};
#endif //__SCENEMANAGER_HPP__
