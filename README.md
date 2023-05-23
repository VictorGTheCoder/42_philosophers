# 42_philosophers

## Introduction

Ce projet est une réalisation de l'école 42. Le but du projet "Philosophers" est de résoudre le problème de la synchronisation des processus dans un contexte de programmation multithread.

## Contexte du Projet

Dans ce projet, nous avons plusieurs philosophes assis autour d'une table, qui font trois choses : ils mangent, dorment et pensent. Ils ont un bol de spaghettis au centre de la table. Ils ont besoin de deux fourchettes pour manger leurs spaghettis. Cependant, il y a le même nombre de fourchettes que de philosophes, donc si tous les philosophes prennent une fourchette à gauche et à droite en même temps, il y a une impasse et personne ne peut manger. Le défi est de créer un programme en C qui simule ce scénario et qui s'assure que chaque philosophe peut manger sans qu'il y ait de deadlock.

## Compilation et Execution

Pour compiler le projet, entrer dans philo/ et utilisez la commande `make`.

Pour exécuter le projet, utilisez la commande suivante :

```shell
./philosophers [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep]
```
Où :

**number_of_philosophers** est le nombre de philosophes et aussi le nombre de fourchettes.

**time_to_die** si un philosophe ne commence pas à manger time_to_die millisecondes après le début de son dernier repas, il meurt en millisecondes.

**time_to_eat** représente le temps qu'il faut pour un philosophe pour manger. Pendant ce temps, il devra garder les deux fourchettes en millisecondes.

**time_to_sleep** représente le temps que le philosophe passera à dormir en millisecondes.
