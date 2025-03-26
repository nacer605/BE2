# Simulation d'un Écosystème de Bestioles 🦠

## Description 📖
Ce projet est une simulation d'un écosystème de bestioles avec différents comportements et accessoires. Chaque bestiole interagit avec son environnement en fonction de ses capteurs et de son comportement.

## Fonctionnalités 🛠️
- **Comportements des bestioles** :
  - Grégaire 🐟 : Suit les autres bestioles proches.
  - Peureuse 😨 : Fuit lorsqu'elle détecte une autre bestiole.
  - Kamikaze 💥 : Fonce vers les autres bestioles pour les percuter.
  - Prévoyante 🧐 : Anticipe les collisions et ajuste sa trajectoire.
  - Multiple 🔄 : Alterne entre plusieurs comportements aléatoirement.
  
- **Capteurs** 🦻👀 :
  - **Yeux** : Permettent de détecter d’autres bestioles dans un certain rayon et sous un certain angle.
  - **Oreilles** : Permettent de détecter d’autres bestioles dans un certain rayon.

- **Accessoires** 🦺:
  - **Nageoires** : Améliorent la vitesse.
  - **Camouflage** : Réduit la visibilité de la bestiole.
  - **Carapace** : Augmente la résistance aux collisions.

## Architecture du Projet 🏗️
- **`BestioleFactory`** : Utilise le design pattern *Factory* pour créer les bestioles.
- **`IComportement` & sous-classes** : Implémentent le design pattern *Stratégie* pour gérer les différents comportements.
- **`Milieu`** : Gère la logique de la simulation et stocke les bestioles.
- **`Aquarium`** : Supervise la simulation et gère l'affichage graphique.
- **Utilisation de `CImg`** 🎨 : Bibliothèque graphique pour afficher la simulation.

## Installation et Exécution 🚀
### Prérequis 📌
- **GCC** (ou un compilateur C++ compatible)
- **XQuartz** (nécessaire pour l'affichage avec CImg)

### Compilation 🔧
```bash
git clone https://github.com/nacer605/BE2.git
make
./main
```

### Auteurs ✨
- Amaury Bernardin
- Aymen Sarhane
- Hamidou Kane
- Nacer  El Harti
- Thomas Favre
