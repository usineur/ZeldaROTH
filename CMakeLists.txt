cmake_minimum_required(VERSION 2.8)

# VitaSDK defines
if( NOT DEFINED CMAKE_TOOLCHAIN_FILE )
  if( DEFINED ENV{VITASDK} )
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VITASDK}/share/vita.toolchain.cmake" CACHE PATH "toolchain file")
  else()
    message(FATAL_ERROR "Please define VITASDK to point to your SDK path!")
  endif()
endif()

# Project start
set(VITA_APPNAME ZeldaROTH)
set(VITA_TITLEID "ZERO00001")

project(${VITA_APPNAME})
include("${VITASDK}/share/vita.cmake" REQUIRED)

# Flags and includes
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-exceptions")

include_directories(
  ${VITASDK}/arm-vita-eabi/include/SDL
)

link_directories(
  ${CMAKE_CURRENT_BINARY_DIR}
)

# Builds
add_executable(${VITA_APPNAME}
  Audio.cpp
  Bouclier.cpp
  Caisse.cpp
  Carte.cpp
  Encyclopedie.cpp
  Ennemi.cpp
  Generique.cpp
  Jeu.cpp
  Joueur.cpp
  Keyboard.cpp
  Listable.cpp
  main.cpp
  Menu.cpp
  Monde.cpp
  Objet.cpp
  Personnage.cpp
  Pnj.cpp
  Projectile.cpp
  Snipe.cpp
  Statut.cpp
  Texte.cpp
  ZoneRect.cpp
)

target_link_libraries(${VITA_APPNAME}
  SDL_gfx
  SDL_mixer
  SDL_image
  SDL
  vorbisfile
  vorbis
  ogg
  mikmod
  jpeg
  png
  webp
  pthread
  imgui
  vitaGL
  vitashark
  mathneon
  z
  SceAppMgr_stub
  SceAppUtil_stub
  SceAudio_stub
  SceCtrl_stub
  SceCommonDialog_stub
  SceDisplay_stub
  SceGxm_stub
  SceHid_stub
  ScePower_stub
  SceShaccCg_stub
  SceSysmodule_stub
  SceTouch_stub
)

file(GLOB_RECURSE ASSETS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} data/*)

set(DATA "")

FOREACH(ITEM ${ASSETS})
  list(APPEND DATA "FILE")
  list(APPEND DATA ${ITEM})
  list(APPEND DATA ${ITEM})
ENDFOREACH()

# Create Vita artifacts
vita_create_self(eboot.bin ${VITA_APPNAME} UNSAFE)
vita_create_vpk(${VITA_APPNAME}.vpk ${VITA_TITLEID} eboot.bin
  NAME ${VITA_APPNAME}
  FILE res/icon0.png sce_sys/icon0.png
  FILE res/bg.png sce_sys/livearea/contents/bg.png
  FILE res/startup.png sce_sys/livearea/contents/startup.png
  FILE res/template.xml sce_sys/livearea/contents/template.xml
  ${DATA}
)
