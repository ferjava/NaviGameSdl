#pragma once

//@brief Interface clase de funciones neceserais para nuestra engine
// que deberemos heredar en nuestro juego
//
#ifndef IGAME_HPP
#define IGAME_HPP

#include <SDL3/SDL.h>

/**
 * @brief Interfaz base para cualquier juego.
 * Tu clase 'MyGame' deberá heredar de esta y sobreescribir sus métodos.
 */
class Engine;
class IGame {
public:
  // Destructor virtual: Asegura que al borrar un IGame* se llame
  // al destructor de la clase hija.
  virtual ~IGame() = default;

  /**
   * @brief Se llama una sola vez al arrancar el motor.
   * Ideal para cargar texturas, sonidos o inicializar variables.
   */
  virtual void OnInit(Engine &engine) = 0;

  /**
   * @brief Se llama en cada frame antes de renderizar.
   * Aquí va la lógica: movimiento, colisiones, IA.
   * @param deltaTime Tiempo transcurrido desde el último frame (opcional pero
   * recomendado).
   */
  virtual void OnUpdate(float deltaTime) = 0;

  /**
   * @brief Se llama en cada frame para dibujar.
   * @param renderer Puntero al renderer del Engine.
   */
  virtual void OnRender(SDL_Renderer *renderer) = 0;

  /**
   * @brief Se llama justo antes de que el motor se cierre.
   * Para liberar recursos específicos que no maneje el Engine.
   */
  virtual void OnCleanup() = 0;
};

#endif // IGAME_HPP
