#include "SceneManager.hpp"

/**
 *@brief:Añade una nueve scene encima (Pausa la anterior)
 **/
void SceneManager::Push(std::unique_ptr<IScene> newscene) {
  stack.push_back(std::move(newscene));
}
/**
 * @brief:Quita la escena y vuelve a la anterior
 **/
void SceneManager::Pop() {
  if (!stack.empty()) {
    stack.back()->OnExit();
    stack.pop_back();
    stack.back()->OnInit();
  }
}
/**
 * @brief: Cambia radicalmente la escena (Borra todo lo anterior)
 *
 **/
void SceneManager::Change(std::unique_ptr<IScene> newscene) {
  while (!stack.empty()) {
    Pop();
  }
  Push(std::move(newscene));
  stack.back()->OnInit();
}
/**
 * @brief: Retorna la scene que apunta el vector ,si no esta vacio
 * si a vacio return nullptr
 * @return: nullptr (si vector esta vacio)
 * @return:Scene*
 * **/
IScene *SceneManager::Current() {
  return stack.empty() ? nullptr : stack.back().get();
}
