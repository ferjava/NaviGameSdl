cmake_minimum_required(VERSION 4.3)
set(GAME_NAME NaviGameSDL)
project(${GAME_NAME}
        VERSION 0.0.0
        DESCRIPTION "Creacion de un juego de naves "
)
#Ponemos en modo debug
set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
#Carpeta de assets
set(ASSETS_SOURCE_DIR  "${CMAKE_SOURCE_DIR}/assets")
set(ASSETS_DESTINY_DIR "${CMAKE_BINARY_DIR}/assets")
#Añadir ccache para compilacion mas rapida
set(AX_ENABLE_PCH ON CACHE BOOL "Enable precompiled headers "FORCE)
find_program(CCACHE_PROGRAM ccache)
if(CACHE_PROGRAM)
  set(CMAKE_CXX_COMPILER_LAUNCHER ${CCACHE_PROGRAM})
  set(CMAKE_C_COMPILER_LAUNCHER ${CCACHE_PROGRAM})
endif()
# configurar una VERSION
configure_file(
"${CMAKE_SOURCE_DIR}/Source/Version.h.in"
"${CMAKE_BINARY_DIR}/Generated/Version.h"
)


# Usar FetchContent
include(FetchContent)
fetchcontent_declare(
  SDL3
  GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
  GIT_TAG main
)
fetchcontent_declare(
  SDL3_image
  GIT_REPOSITORY https://github.com/libsdl-org/SDL_image.git
  GIT_TAG main
)
fetchcontent_declare(
  SDL3_ttf
  GIT_REPOSITORY https://github.com/libsdl-org/SDL_ttf.git
  GIT_TAG main
)
fetchcontent_declare(
  EnTT
  GIT_REPOSITORY https://github.com/skypjack/entt.git
  GIT_TAG main
)
fetchcontent_makeavailable(SDL3 SDL3_image SDL3_ttf EnTT)

# Añadimos los archivos para compilar globales

file(GLOB_RECURSE  GAME_HEADER
  Source/*.h Source/*.hpp
)
file(GLOB_RECURSE  GAME_SOURCE
Source/*.c Source/*.cpp
)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}Source/)

add_executable(${GAME_NAME})

target_include_directories(${GAME_NAME} PRIVATE
  "${CMAKE_BINARY_DIR}/Generated")
target_sources(${GAME_NAME} PRIVATE ${GAME_SOURCE})
target_link_libraries(${GAME_NAME} PRIVATE
  SDL3::SDL3-shared
  SDL3_image::SDL3_image-shared
  SDL3_ttf::SDL3_ttf-shared
  EnTT::EnTT)

add_custom_command(
  TARGET ${GAME_NAME} COMMENT "Copiando carpeta assets"
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory
  ${ASSETS_SOURCE_DIR}
  ${ASSETS_DESTINY_DIR}
)

