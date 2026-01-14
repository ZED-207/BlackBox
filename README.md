# 🛡️ BlackBox - Enregistreur de Vol

**Projet Groupe 2 - Programmation Système en C**

Système d'enregistrement embarqué simulant une boîte noire de véhicule avec gestion mémoire optimisée (buffer circulaire).

---

## 📋 Description

Ce projet implémente un enregistreur de données de type "boîte noire" pour véhicule, capable de :
- **Enregistrer en continu** les paramètres vitaux (vitesse, température moteur)
- **Conserver uniquement les 10 dernières secondes** grâce à un buffer circulaire
- **Sauvegarder automatiquement** les données en cas d'incident
- **Analyser** les données post-mortem

---

## ✨ Fonctionnalités

### 🔄 Gestion Mémoire (Buffer Circulaire)
- Liste chaînée dynamique sans tableaux statiques
- Rotation FIFO automatique après 10 trames
- Libération sécurisée de la mémoire

### 🚗 Simulation Physique
- Cinématique : Accélération et freinage réalistes
- Thermodynamique : Calcul de température avec chauffe/refroidissement
- Détection de surchauffe (> 110°C)

### 💾 Analyse Post-Mortem
- Export automatique en fichier binaire (`crash.bin`)
- Statistiques : vitesse moyenne et température maximale
- Historique complet des 10 dernières secondes

---

## 🚀 Installation

### Prérequis
- **Compilateur C** : GCC (version 4.8+)
- **Système** : Linux, macOS, ou Windows (avec MinGW)

### Compilation

```bash
# Cloner le dépôt
git clone https://github.com/VOTRE_USERNAME/BlackBox.git
cd BlackBox

# Compiler
gcc -o blackbox main.c memory.c physics.c files.c -lm -Wall -Wextra -std=c99

# Exécuter
./blackbox
```

---

## 🎮 Utilisation

### Mode Simulation
```
Choix : 1

Actions disponibles :
- [A] Accélérer (+20 km/h)
- [F] Freiner (-30 km/h)
- [Q] Quitter et sauvegarder
```

### Mode Analyse
```
Choix : 2
→ Affiche les statistiques du dernier crash
```

---

## 📁 Structure du Projet

```
BlackBox/
├── blackbox.h       # Déclarations et structures
├── main.c           # Point d'entrée et menu
├── memory.c         # Gestion du buffer circulaire
├── physics.c        # Simulation physique
├── files.c          # Sauvegarde/Lecture binaire
├── .gitignore       # Fichiers ignorés par Git
└── README.md        # Documentation
```

---

## 🔬 Démonstration

### Rotation du Buffer
```
→ Enregistrement Frame [1736789123] (Mémoire : 1/10)
→ Enregistrement Frame [1736789124] (Mémoire : 2/10)
...
→ Enregistrement Frame [1736789132] (Mémoire : 10/10)
⚠️  Rotation : Frame ancienne écrasée
→ Enregistrement Frame [1736789133] (Mémoire : 10/10)
```

### Analyse Post-Mortem
```
╔═══════════════════════════════════════════╗
║   ANALYSE POST-MORTEM                    ║
╚═══════════════════════════════════════════╝

📊 Analyse des 10 dernières secondes :

Timestamp    | Vitesse      | Température
─────────────────────────────────────────────────
1736789123   |     20.0 km/h |       25.5 °C
1736789124   |     40.0 km/h |       32.8 °C
...

═══════════════════════════════════════════
  STATISTIQUES
═══════════════════════════════════════════
  Vitesse moyenne    : 85.20 km/h
  Température max    : 102.50 °C
═══════════════════════════════════════════
```

---

## 🎯 Concepts Techniques

### Buffer Circulaire (FIFO)
Le système maintient exactement 10 trames en mémoire. À chaque nouvelle trame :
1. Si `nb_frames < 10` → Ajout simple
2. Si `nb_frames == 10` → Suppression de la plus ancienne (tête) puis ajout

### Gestion Mémoire Sécurisée
```c
// Recâblage AVANT free() pour éviter les segfaults
Frame *ancienne = b->debut;
free(ancienne);                 // ← Puis libérer

```

### Sauvegarde Binaire

Le fichier `crash.bin` contient :
- **4 octets** : Nombre de frames (int)

- **Pour chaque frame** :
  - 8 octets : Timestamp (long)
  - 4 octets : Vitesse (float)
  - 4 octets : Température (float)


---


## 📊 Validation du Projet


### ✅ Critères Respectés
- [x] Gestion mémoire dynamique (pas de tableaux statiques)
- [x] Buffer circulaire avec rotation FIFO

- [x] Simulation physique (cinématique + thermodynamique)
- [x] Sauvegarde en fichier binaire
- [x] Analyse post-mortem avec statistiques

- [x] Code modulaire et commenté
- [x] Compilation sans warnings

### 🧪 Tests
```bash
# Vérifier les fuites mémoire
valgrind --leak-check=full ./blackbox


# Résultat attendu :
# All heap blocks were freed -- no leaks are possible
```

---

## 🎥 Vidéo de Démonstration


📹 **Lien YouTube** : [À compléter avec votre lien]

La vidéo montre :
- Compilation du projet
- Simulation avec rotation du buffer
- Génération du fichier crash.bin
- Analyse post-mortem
- Vérification mémoire (Valgrind)

---

---

## 📝 Licence

Projet académique - Tous droits réservés

---

## 🔗 Ressources

- [Documentation C99](https://en.cppreference.com/w/c)
- [Gestion mémoire en C](https://www.gnu.org/software/libc/manual/html_node/Memory.html)
- [Fichiers binaires en C](https://www.cprogramming.com/tutorial/c/lesson10.html)

---

## 🐛 Signaler un Bug

Ouvrez une **issue** sur ce dépôt en décrivant :
1. Le comportement attendu
2. Le comportement observé
3. Les étapes pour reproduire

---

**⭐ Si ce projet vous a été utile, n'hésitez pas à lui donner une étoile !**
