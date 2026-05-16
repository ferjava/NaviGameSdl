# TODO

## [VERSION 0.0.01]

> [!NOTE]
> Este archivo  contiene los objetivos que se marcan para cada version

* [V] Crear una Engine encargada de inicio y manejo de [SDL3] (Ventana , Render).
* [V] Crear una Game encargado de cargar los recursos del juego
  y manejarlos (escenas , images ,etc).
* [V] Crear una base para nuestras [IScene] para crear escenas
* [V] Utilizar un [SceneManager] para manejar las escenas
* [V] Realizar un pequeña prueba de que todo funciona.

## VERSION 0.0.02

> [!NOTE]
>Objetivo principal para esta version.Hacer que un sprite
>(nave)se mueva por la pantalla al pulsar las [teclas AWSD]

[V] Integrar [Entt] y crear etiquetas,sistemas y entidades
[V] Crear el sistema de movimiento asociado a l teclado
[V] Crear las etiqueta Gráfica asociada a un [SDL_Texture] como un smart_Pointer
[V] Permitir que el [TextureManager] podamos añadirle una textura
creada como (un texto , un rectángulo , circulo ,etc )
[V] Comprobar no tener fugas de memoria.

## VERSION 0.0.03

> [!NOTE]
> Limitaremos el movimiento de nuestra nave a la pantalla
>(sin salirse por los bordes) .Y crearemos las entidad del jugador

* [V] Limitar el movimiento al area de la pantalla
* [V] Limitar aun cuando hagamos [FULLSCREEN]
* [V] Crear la entidad Player
* [V] Mostrar Texto de version en esquina inferior derecha
* [V] Comprobar si ha fugas y depuración

## VERSION 0.0.04

> [!NOTE]
> Crear animaciones para el movimiento de la nave de derecha e izquierda.
>Ademas añadiremos una nueva entidad bala (un circulo blanco) que se
>mostrara en pantalla cuando el jugador pulse la tecla space

* [] Crear las animaciones para el movimiento
* [V] Crear [SDL_Texture] (circulo) y añadirlo al [TextureManager]
* [V] Asociar la bala con la pulsación del teclado
* [V] Colocar la bala/s con el sprite de la nave
* [] Comprobación de fugas de memoria y depuración
