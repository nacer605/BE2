#!/bin/bash

echo "🔧 Compilation rapide avec X11..."

g++ -std=c++17 -o test_app \
  test_app.cpp \
  Bestiole.cpp \
  Milieu.cpp \
  BestioleFactory.cpp \
  BestioleCamouflage.cpp \
  BestioleOreille.cpp \
  BestioleYeux.cpp \
  BestioleNageoire.cpp \
  BestioleCarapace.cpp \
  Multiple.cpp \
  gregaire.cpp \
  Kamikaze.cpp \
  Peureuse.cpp \
  prevoyant.cpp \
  Aquarium.cpp \
  -I. -lm -lX11

# Vérifie si compilation réussie
if [ $? -eq 0 ]; then
  echo " Compilation réussie. Résultat :"
  ./test_app
else
  echo " Erreur de compilation"
fi
