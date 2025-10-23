# Mini Lib - Bibliothèque C Standard Simplifiée 📚

## 📋 Description

Ce projet consiste en une **mini-bibliothèque C** réimplémentant les fonctionnalités essentielles de la bibliothèque standard (stdio.h, stdlib.h, string.h). L'objectif est de comprendre en profondeur :

- 🧠 La gestion manuelle de la mémoire
- 📂 Les opérations d'entrée/sortie bufferisées
- 🔧 Les appels système bas niveau (read, write, open, close, brk/sbrk)
- 💾 La manipulation de structures de données (listes chaînées)

### 🎯 Objectifs pédagogiques

- Comprendre l'implémentation réelle de `malloc()`, `free()`, `printf()`, `fopen()`, etc.
- Maîtriser la gestion de buffers pour optimiser les I/O
- Développer une bibliothèque réutilisable et modulaire
- Approfondir la programmation système en C

## ✨ Fonctionnalités implémentées

### 🧩 Gestion de la mémoire

| Fonction | Description | Équivalent standard |
|----------|-------------|---------------------|
| `mini_calloc()` | Allocation mémoire initialisée à zéro | `calloc()` |
| `mini_free()` | Libération de mémoire allouée | `free()` |

**Particularités** :
- Gestion d'une liste chaînée de blocs mémoire (`malloc_element`)
- Suivi de l'état de chaque bloc (libre/occupé)
- Réutilisation des blocs libérés

### 📝 Entrées/Sorties standard

| Fonction | Description | Équivalent standard |
|----------|-------------|---------------------|
| `mini_printf()` | Affichage formaté sur stdout | `printf()` |
| `mini_scanf()` | Lecture depuis stdin | `scanf()` |
| `mini_perror()` | Affichage des erreurs système | `perror()` |
| `mini_exit()` | Terminaison propre du programme | `exit()` |

### 🔤 Manipulation de chaînes

| Fonction | Description | Équivalent standard |
|----------|-------------|---------------------|
| `mini_strlen()` | Calcul de longueur de chaîne | `strlen()` |
| `mini_strcopy()` | Copie de chaîne | `strcpy()` |
| `mini_strcmp()` | Comparaison de chaînes | `strcmp()` |

### 📂 Gestion de fichiers bufferisée

| Fonction | Description | Équivalent standard |
|----------|-------------|---------------------|
| `mini_fopen()` | Ouverture de fichier | `fopen()` |
| `mini_fclose()` | Fermeture de fichier | `fclose()` |
| `mini_fread()` | Lecture bufferisée | `fread()` |
| `mini_fwrite()` | Écriture bufferisée | `fwrite()` |
| `mini_fflush()` | Vidage du buffer | `fflush()` |
| `mini_fgetc()` | Lecture d'un caractère | `fgetc()` |
| `mini_fputc()` | Écriture d'un caractère | `fputc()` |

**Architecture** :
- Structure `MYFILE` personnalisée remplaçant `FILE*`
- Double buffering (lecture et écriture séparés)
- Gestion d'une liste de fichiers ouverts
- Optimisation des appels système par bufferisation

## 🏗️ Structure du projet

```
TP-system/
├── mini_lib.h          # Fichier d'en-tête (prototypes et structures)
├── mini_memory.c       # Gestion mémoire (calloc, free)
├── mini_io.c           # Entrées/sorties et gestion de fichiers
├── mini_string.c       # Manipulation de chaînes
├── main.c              # Programme de démonstration
├── Makefile            # Compilation automatisée
├── mini_readme.txt     # Documentation technique
└── README.md           # Ce fichier
```

## 🚀 Installation et utilisation

### Prérequis

- GCC (version 7.0+)
- Make
- Système Unix/Linux (ou WSL)

### Compilation

```bash
# Cloner le dépôt
git clone https://github.com/amauol/TP-system.git
cd TP-system

# Compiler le projet
make

# Exécuter le programme de démonstration
./main
```

## 🔍 Détails techniques

### Structure `malloc_element`

```c
typedef struct malloc_element {
    void* addr;              // Adresse du bloc mémoire
    size_t size;             // Taille du bloc
    int statut;              // 0 = libre, 1 = occupé
    struct malloc_element *next_malloc;  // Liste chaînée
} malloc_element;
```

**Algorithme de gestion** :
1. Recherche d'un bloc libre de taille suffisante (First Fit)
2. Si aucun bloc disponible → demande au système via `sbrk()`
3. Marquage du bloc comme occupé
4. Retour de l'adresse mémoire

### Structure `MYFILE`

```c
typedef struct MYFILE {
    int fd;                  // Descripteur de fichier
    void* buffer_read;       // Buffer de lecture
    void* buffer_write;      // Buffer d'écriture
    int ind_read;            // Index de lecture dans le buffer
    int ind_write;           // Index d'écriture dans le buffer
    struct MYFILE* next_myfile;  // Liste chaînée de fichiers ouverts
} MYFILE;
```

**Optimisations** :
- Buffers de 4 Ko pour minimiser les appels système
- Écriture différée jusqu'au `fflush()` ou fermeture
- Gestion automatique du remplissage/vidage des buffers

## 🧪 Démonstration

Le programme `main.c` inclut permet de tester toutes les fonctionnalités de la bibliothèque :

```bash
make
./main
```

Le programme démontre :
- ✅ Allocation et libération de mémoire
- ✅ Lecture et écriture sur stdin/stdout
- ✅ Manipulation de chaînes de caractères
- ✅ Opérations de fichiers avec bufferisation

## 🎓 Concepts avancés explorés

- **Allocation mémoire dynamique** : implémentation d'un allocateur simple
- **Bufferisation I/O** : réduction des syscalls coûteux
- **Listes chaînées** : gestion de structures dynamiques
- **Appels système** : `read()`, `write()`, `open()`, `close()`, `brk()`
- **Gestion d'erreurs** : codes de retour et `errno`

## ⚠️ Limitations connues

- Pas de support des formats complexes dans `mini_printf()` (seulement `%s`, `%d`)
- Allocateur mémoire basique (pas de coalescence des blocs libres)
- Pas de gestion multi-threading (pas thread-safe)
- Modes de fichiers limités ('r', 'w', 'a')

## 🛠️ Améliorations futures

- [ ] Implémentation de `mini_malloc()` et `mini_realloc()`
- [ ] Support complet du formatage dans `mini_printf()`
- [ ] Coalescence des blocs mémoire libres
- [ ] Ajout de `mini_fprintf()` et `mini_fscanf()`
- [ ] Tests unitaires automatisés
- [ ] Gestion des modes binaires pour les fichiers
- [ ] Optimisation de l'allocateur (Best Fit, Buddy System)

## 📚 Ressources

- [Linux System Call Table](https://chromium.googlesource.com/chromiumos/docs/+/master/constants/syscalls.md)
- Entraide entre étudiants
- `man 2 brk`, `man 2 read`, `man 2 write`

## 👤 Auteur

[@amauol](https://github.com/amauol)

Projet réalisé dans le cadre du module **Programmation Système** à l'INSA Centre Val de Loire.

