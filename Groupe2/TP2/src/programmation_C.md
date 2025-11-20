# Rapport de synthèse - Programmation en C

**Année:** 2025-2026  
**Auteurs:** [Votre nom]  
**Date:** Novembre 2025

---

## Table des matières

1. [Introduction](#introduction)
2. [Débogage avec GDB](#débogage-avec-gdb)
3. [Chaîne de compilation en C avec GCC](#chaîne-de-compilation-en-c-avec-gcc)
4. [Manipulation de chaînes de caractères](#manipulation-de-chaînes-de-caractères)
5. [Gestion des structures de données](#gestion-des-structures-de-données)
6. [Recherche dans les fichiers](#recherche-dans-les-fichiers)
7. [Conclusion](#conclusion)

---

## Introduction

Ce rapport présente une synthèse des concepts fondamentaux de la programmation en C abordés dans le cadre du TP2. Nous explorerons les techniques de débogage, la chaîne de compilation, la manipulation de chaînes de caractères, ainsi que la gestion des structures et des fichiers.

---

## Débogage avec GDB

### Qu'est-ce que GDB ?

GDB (GNU Debugger) est un outil puissant permettant de déboguer les programmes C. Il permet d'examiner l'état d'un programme pendant son exécution, d'identifier les erreurs et de comprendre le comportement du code.

### Compilation pour le débogage

Pour utiliser GDB efficacement, il faut compiler le programme avec les symboles de débogage :

```bash
gcc -ggdb3 programme.c -o programme
```

L'option `-ggdb3` génère des informations de débogage détaillées.

### Commandes essentielles de GDB

| Commande | Description |
|----------|-------------|
| `r` ou `run` | Exécute le programme |
| `break fichier.c:ligne` | Place un point d'arrêt |
| `n` ou `next` | Exécute la ligne suivante |
| `s` ou `step` | Entre dans une fonction |
| `p variable` | Affiche la valeur d'une variable |
| `bt` ou `backtrace` | Affiche la pile d'appels |
| `continue` | Continue l'exécution |
| `quit` | Quitte GDB |

### Exemple pratique

Dans l'exercice 2.1, nous avons identifié une erreur classique :

```c
for (int compteur = 0; compteur < sizeof(tableau); compteur++)
```

Le problème : `sizeof(tableau)` retourne la taille en **octets** (400 pour un tableau de 100 int), pas le nombre d'éléments. La correction :

```c
for (int compteur = 0; compteur < 100; compteur++)
// ou
for (int compteur = 0; compteur < sizeof(tableau)/sizeof(int); compteur++)
```

### Workflow de débogage

1. Compiler avec `-ggdb3`
2. Lancer GDB : `gdb programme`
3. Placer des points d'arrêt aux endroits suspects
4. Exécuter et inspecter les variables
5. Avancer pas à pas pour localiser l'erreur
6. Corriger le code source

---

## Chaîne de compilation en C avec GCC

### Vue d'ensemble

La compilation en C se déroule en plusieurs étapes distinctes :

```
Code source (.c) → Préprocesseur → Compilation → Assemblage → Édition de liens → Exécutable
```

### Les 4 étapes principales

#### 1. Prétraitement

Le préprocesseur gère les directives commençant par `#` :
- `#include` : inclusion de fichiers
- `#define` : définition de macros
- `#ifdef` : compilation conditionnelle

```bash
gcc -E aire.c -o aire.i
```

Produit un fichier `.i` avec toutes les inclusions et macros remplacées.

#### 2. Compilation

Transformation du code C en code assembleur :

```bash
gcc -S aire.i -o aire.s
```

Options d'optimisation :
- `-O0` : aucune optimisation (débogage)
- `-O1`, `-O2` : optimisations standards
- `-O3` : optimisations agressives

#### 3. Assemblage

Conversion du code assembleur en code machine (fichier objet) :

```bash
gcc -c aire.s -o aire.o
```

Produit un fichier `.o` contenant du code binaire non exécutable.

#### 4. Édition de liens (Linking)

Combine les fichiers objets et les bibliothèques pour créer l'exécutable :

```bash
gcc aire.o -lm -o aire
```

L'option `-lm` lie la bibliothèque mathématique.

### Compilation en une seule commande

```bash
gcc -O2 aire.c -lm -o aire
```

### Exemple multi-fichiers

Pour un projet avec plusieurs fichiers sources :

```
sphere/
├── sphere.h        (définitions)
├── main.c          (programme principal)
├── surface.c       (calculs de surface)
└── volume.c        (calculs de volume)
```

Compilation :

```bash
# Compiler chaque fichier séparément
gcc -O3 -c main.c -o main.o
gcc -O3 -c volume.c -o volume.o
gcc -O3 -c surface.c -o surface.o

# Lier tous les objets
gcc main.o volume.o surface.o -lm -o sphere
```

### Avantages de la compilation séparée

- **Rapidité** : recompiler uniquement les fichiers modifiés
- **Modularité** : organisation claire du code
- **Réutilisabilité** : partage de fichiers objets

---

## Manipulation de chaînes de caractères

### Représentation des chaînes en C

En C, une chaîne est un tableau de caractères terminé par `\0` (caractère nul) :

```c
char nom[20] = "Bonjour";
// Stocké comme : 'B' 'o' 'n' 'j' 'o' 'u' 'r' '\0'
```

### Opérations de base

#### 1. Calcul de longueur

Sans fonction de bibliothèque :

```c
int longueur = 0;
while(chaine[longueur] != '\0') {
    longueur++;
}
```

Avec la bibliothèque standard :

```c
#include <string.h>
int longueur = strlen(chaine);
```

#### 2. Copie de chaîne

Méthode manuelle :

```c
int i = 0;
while(source[i] != '\0') {
    destination[i] = source[i];
    i++;
}
destination[i] = '\0';  // Important : terminer la chaîne
```

Avec la bibliothèque :

```c
strcpy(destination, source);
```

#### 3. Concaténation

Méthode manuelle :

```c
// Trouver la fin de chaine1
int i = 0;
while(chaine1[i] != '\0') {
    i++;
}

// Copier chaine2 à la fin de chaine1
int j = 0;
while(chaine2[j] != '\0') {
    chaine1[i] = chaine2[j];
    i++;
    j++;
}
chaine1[i] = '\0';
```

Avec la bibliothèque :

```c
strcat(chaine1, chaine2);
```

### Lecture de chaînes avec espaces

Problème avec `scanf("%s", ...)` : s'arrête au premier espace.

Solutions :

```c
// Méthode 1 : scanf avec format spécial
scanf(" %[^\n]", chaine);

// Méthode 2 : fgets
fgets(chaine, sizeof(chaine), stdin);
```

### Fonctions de la bibliothèque `string.h`

| Fonction | Description |
|----------|-------------|
| `strlen(s)` | Longueur de la chaîne |
| `strcpy(dest, src)` | Copie une chaîne |
| `strcat(dest, src)` | Concatène deux chaînes |
| `strcmp(s1, s2)` | Compare deux chaînes |
| `strstr(s1, s2)` | Recherche une sous-chaîne |

---

## Gestion des structures de données

### Définition d'une structure

Une structure permet de regrouper plusieurs variables de types différents :

```c
struct Etudiant {
    char nom[50];
    char prenom[50];
    char adresse[100];
    float notes[5];
};
```

### Déclaration et initialisation

```c
// Déclaration d'une variable
struct Etudiant etudiant1;

// Initialisation avec strcpy
strcpy(etudiant1.nom, "Dupont");
strcpy(etudiant1.prenom, "Jean");

// Initialisation directe des notes
etudiant1.notes[0] = 15.5;
etudiant1.notes[1] = 16.0;
```

### Tableau de structures

Pour gérer plusieurs entités :

```c
struct Etudiant etudiants[5];

// Accès aux membres
etudiants[0].notes[2] = 14.5;
```

### Parcours et manipulation

```c
// Parcourir tous les étudiants
for(int i = 0; i < 5; i++) {
    printf("Nom : %s\n", etudiants[i].nom);
    
    // Calculer la moyenne
    float somme = 0;
    for(int j = 0; j < 5; j++) {
        somme += etudiants[i].notes[j];
    }
    float moyenne = somme / 5;
    printf("Moyenne : %.2f\n", moyenne);
}
```

### Avantages des structures

- **Organisation** : regroupement logique des données
- **Lisibilité** : code plus clair et maintenable
- **Modularité** : facilite le passage de paramètres complexes
- **Évolutivité** : ajout facile de nouveaux champs

### Utilisation avec des fichiers d'en-tête

Bonne pratique : définir les structures dans un fichier `.h` :

```c
// etudiant.h
#ifndef ETUDIANT_H
#define ETUDIANT_H

struct Etudiant {
    char nom[50];
    char prenom[50];
    char adresse[100];
    float notes[5];
};

#endif
```

Utilisation :

```c
// main.c
#include "etudiant.h"

int main() {
    struct Etudiant e1;
    // ...
}
```

---

## Recherche dans les fichiers

### Ouverture et fermeture de fichiers

#### Modes d'ouverture

| Mode | Description |
|------|-------------|
| `"r"` | Lecture seule |
| `"w"` | Écriture (écrase le contenu) |
| `"a"` | Ajout à la fin |
| `"r+"` | Lecture et écriture |

#### Exemple

```c
FILE *fichier = fopen("data.txt", "r");

if (fichier == NULL) {
    printf("Erreur d'ouverture\n");
    return 1;
}

// ... utilisation du fichier ...

fclose(fichier);
```

### Lecture ligne par ligne

La fonction `fgets()` permet de lire une ligne complète :

```c
char ligne[500];

while (fgets(ligne, sizeof(ligne), fichier) != NULL) {
    // Traiter la ligne
    printf("%s", ligne);
}
```

### Recherche de phrases

#### Méthode 1 : avec `strstr()`

```c
#include <string.h>

char *position = strstr(ligne, phrase_recherche);
if (position != NULL) {
    printf("Phrase trouvée !\n");
}
```

#### Méthode 2 : recherche manuelle

```c
int trouver_phrase(char *ligne, char *phrase) {
    int i = 0, j;
    
    while (ligne[i] != '\0') {
        j = 0;
        while (phrase[j] != '\0' && ligne[i + j] == phrase[j]) {
            j++;
        }
        
        if (phrase[j] == '\0') {
            return 1;  // Trouvé
        }
        i++;
    }
    
    return 0;  // Non trouvé
}
```

### Comptage d'occurrences

Pour compter toutes les occurrences d'une phrase :

```c
int count = 0;
char *position = ligne;

while ((position = strstr(position, phrase)) != NULL) {
    count++;
    position++;  // Avancer pour chercher la suivante
}
```

### Programme complet de recherche

Structure typique :

1. Demander le nom du fichier et la phrase
2. Ouvrir le fichier avec vérification
3. Lire ligne par ligne avec `fgets()`
4. Pour chaque ligne, compter les occurrences
5. Afficher les résultats avec numéro de ligne
6. Fermer le fichier

### Gestion des erreurs

Toujours vérifier :

```c
// Vérification d'ouverture
if (fichier == NULL) {
    perror("Erreur");
    return 1;
}

// Vérification de lecture
if (fgets(ligne, sizeof(ligne), fichier) == NULL) {
    if (feof(fichier)) {
        printf("Fin du fichier\n");
    } else {
        printf("Erreur de lecture\n");
    }
}
```

---

## Conclusion

### Compétences acquises

Au cours de ce TP, nous avons développé des compétences essentielles en programmation C :

1. **Débogage** : utilisation de GDB pour identifier et corriger les erreurs
2. **Compilation** : compréhension de la chaîne de compilation avec GCC
3. **Chaînes** : manipulation avancée des chaînes de caractères
4. **Structures** : organisation des données complexes
5. **Fichiers** : lecture et traitement de fichiers texte

### Bonnes pratiques retenues

- Toujours compiler avec les warnings : `gcc -Wall -Wextra`
- Utiliser `-ggdb3` pour faciliter le débogage
- Vérifier les retours de fonctions (fopen, scanf, etc.)
- Terminer les chaînes par `\0`
- Commenter le code pour améliorer la lisibilité
- Organiser le code en modules (fichiers .h et .c séparés)

### Perspectives

Ces connaissances constituent une base solide pour :
- Développer des applications C plus complexes
- Comprendre les langages de bas niveau
- Optimiser les performances des programmes
- Travailler sur des systèmes embarqués

### Ressources utiles

- Documentation GCC : https://gcc.gnu.org/onlinedocs/
- Manuel GDB : https://sourceware.org/gdb/documentation/
- Référence C : https://en.cppreference.com/w/c
- The C Programming Language (K&R)

---

