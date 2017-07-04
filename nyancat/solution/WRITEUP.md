# Write-up

Ce challenge est relativement facile, une fois que l'on a la bonne idée. Tout commence avec une vidéo `challenge.mp4` dans laquelle l'on peut apercevoir un chat éclairé par une lumière de différentes couleurs, qui changent chaque seconde.

Pour résoudre ce challenge, il faut commencer par relever les couleurs. Ensuite, à chacune de ces couleurs correspond un code binaire qui est calculé selon le tableau ci-dessous. Enfin, on reconstituant la *bit string* et en la convertissant en ASCII, on obtient le drapeau.

Color | Hexa | Code
----- | ---- | ----
black | #000000 | 000
blue | #0000ff | 001
green | #00ff00 | 010
cyan | #00ffff | 011
red | #ff0000 | 100
magenta | #ff00ff | 101
yellow | #ffff00 | 110
white | #ffffff | 111

Le résultat de ces opérations sur la vidéo est présenté dans le tableau récapitulatif ci-dessous.

Time | Color | Code | Time | Color | Code | Time | Color | Code | Time | Color | Code
---- | ----- | ---- | ---- | ----- | ---- | ---- | ----- | ---- | ---- | ----- | ----
0s | green | 010 | 18s | green | 010 | 36s | white | 111 | 54s | white | 111 |
1s | magenta | 101 | 19s | yellow | 110 | 37s | blue | 001 | 55s | blue | 001 |
2s | black | 000 | 20s | white | 111 | 38s | white | 111 | 56s | cyan | 011 |
3s | red | 100 | 21s | blue | 001 | 39s | blue | 001 | 57s | black | 000 |
4s | red | 100 | 22s | white | 111 | 40s | cyan | 011 | 58s | green | 010 |
5s | blue | 001 | 23s | blue | 001 | 41s | black | 000 | 59s | yellow | 110 |
6s | black | 000 | 24s | cyan | 011 | 42s | green | 010 | 60s | white | 111 |
7s | cyan | 011 | 25s | black | 000 | 43s | yellow | 110 | 61s | blue | 001 |
8s | cyan | 011 | 26s | green | 010 | 44s | white | 111 | 62s | white | 111 |
9s | yellow | 110 | 27s | yellow | 110 | 45s | blue | 001 | 63s | blue | 001 |
10s | yellow | 110 | 28s | white | 111 | 46s | white | 111 | 64s | cyan | 011 |
11s | yellow | 110 | 29s | blue | 001 | 47s | blue | 001 | 65s | black | 000 |
12s | white | 111 | 30s | white | 111 | 48s | cyan | 011 | 66s | green | 010 |
13s | blue | 001 | 31s | blue | 001 | 49s | black | 000 | 67s | yellow | 110 |
14s | white | 111 | 32s | cyan | 011 | 50s | green | 010 | 68s | white | 111 |
15s | blue | 001 | 33s | black | 000 | 51s | yellow | 110 | 69s | blue | 001 |
16s | cyan | 011 | 34s | green | 010 | 52s | white | 111 | 70s | white | 111 |
17s | black | 000 | 35s | yellow | 110 | 53s | blue | 001 | 71s | magenta | 101 |


```
010101000100100001000011011110110110111001111001011000010110111001111001011000010110111001111001011000010110111001111001011000010110111001111001011000010110111001111001011000010110111001111001011000010110111001111101
```

La *bit string* résultante ci-dessus donne une fois décodée le drapeau suivant : `THC{nyanyanyanyanyanyanyan}`.
