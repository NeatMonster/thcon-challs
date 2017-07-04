# M.I.P.S. V.M.

- Auteur : Alexandre Adamski (<alexandre.adamski@etu.enseeiht.fr>)
- Type : Reverse

## Description

"Hey dude,

Last night was terrible.. In my drunken stupor, I hid my beloved `flag.txt` inside multiple layers of pure hassle. Sadly, I can't recall any specifics. I heard you might want to score some points, so bring me back my flag, and don't forget any of my cryptomaterial!

Yours drunkenly."

### Fichiers fournis

- `bin/unpack`

## Utilisation

Pour construire le challenge, il est nécessaire de disposer de la *GNU toolchain for MIPS processors*.

Ensuite, il n'y a plus qu'à utiliser le fichier `Makefile` fourni :

- `make payload` construit le *payload*, qui n'est qu'une archive ZIP paddée contenant un fichier `flag.txt`.
- `make challenge` construit le binaire au format MIPS qui déchiffre le *payload* avec le LFSR.
- `make mipsvm` construit le binaire au format i386 de la machine virtuelle émulant un processeur MIPS.
- `make unpack` construit le binaire du format i386 du *packer* qui contient tous les binaires précédents.

`make build` exécute toutes les étapes précédentes, tandis que `make clean` nettoie tous les fichiers produits. Pour se faciliter la vie, une construction automatisée est possible avec Docker à l'aide de la commande `make export`.

## État

En cours de construction

### Relecture

### Test

### Déploiement

### Relecture Déploiement

### Test Déploiement

### Docker-compose
