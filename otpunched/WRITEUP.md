# Write-up

Ce challenge est composé de deux images, `card1.png` et `card2.png`.

Il s'agit de deux [cartes perforées](https://fr.wikipedia.org/wiki/Carte_perfor%C3%A9e) de même type que celles utilisées par les ordinateurs [IBM System/360](https://fr.wikipedia.org/wiki/IBM_360_et_370) des années 1960. L'encodage des caractères n'est pas de l'[ASCII](https://fr.wikipedia.org/wiki/American_Standard_Code_for_Information_Interchange) mais de l'[EBCDIC](https://fr.wikipedia.org/wiki/Extended_Binary_Coded_Decimal_Interchange_Code). Il faut donc commencer par extraire les données que les cartes contiennent.

Pour ce faire, j'utilise le site [www.masswerk.at/cardreader/](http://www.masswerk.at/cardreader/), et j'obtiens rapidement les chaînes de caractères suivantes :

```
card1.png - 365C997610306888C3CB07B26C7ED39325E4AD1BDC87255B8F5E54B66E253759B306A9BAA01B7D4A
card2.png - 5A04DC351E3D7B9CC3CE1DFF5142B08B3AFCA60B9484336B961F54A67319304E8845ABA9B60C734A
```

Comme le laisse penser le titre du challenge, il s'agit de deux chaînes de caractères chiffrées avec du *One Time Pad*. Ce dernier est vulnérable si le masque a été réutilisé, ce qui a été le cas ici. Il nous faut donc trouver un bout d'un des deux messages.

On peut supposer qu'un des deux messages commence par le mot `The`. Testons avec le premier.

```
  365C99
^ 546865 "The"
  ------
  6234FC
^ 5A04DC
  ------
  383020 "80 "
```

Bingo. Nous sommes sur la bonne piste. Le deuxième message commence donc par la chaîne `80 `. La valeur 80 est une valeur que nous connaissons tous puisque c'est une limite emblématique. Mais 80 quoi ? 80 caractères ! Continuons avec `80 characters`.

```
  5A04DC351E3D7B9CC3CE1DFF51
^ 38302063686172616374657273 "80 characters"
  --------------------------
  6234FC56765C09FDA0BA788D22
^ 365C997610306888C3CB07B26C
  --------------------------
  54686520666C617563717F3F4E "The flaucq?N"
```

Bon visiblement ce n'est pas exactement ça, mais le début est correct. `The fla`, hum, `The flag is` ?

```
  365C997610306888C3CB07
^ 54686520666C6167206973 "The flag is"
  ----------------------
  6234FC56765C09EFE3A274
^ 5A04DC351E3D7B9CC3CE1D
  ----------------------
  3830206368617273206C69 "80 chars li"
```

Pas mal. Serait-ce `80 chars limit` ?

```
  5A04DC351E3D7B9CC3CE1DFF5142
^ 3830206368617273206C696D6974 "80 chars limit"
  ----------------------------
  6234FC56765C09EFE3A274923836
^ 365C997610306888C3CB07B26C7E
  ----------------------------
  54686520666C6167206973205448 "The flag is TH"
```

Le format des drapeaux de la THC étant connu, ce doit être `The flag is THC{`.

```
  365C997610306888C3CB07B26C7ED393
^ 54686520666C6167206973205448437B "The flag is THC{"
  --------------------------------
  6234FC56765C09EFE3A27492383690E8
^ 5A04DC351E3D7B9CC3CE1DFF5142B08B
  --------------------------------
  3830206368617273206C696D69742063 "80 chars limit c"
```

Bon, un mot commençant par `c` ce n'est pas simple. Mais au bout de plusieurs essais, on finit par tomber sur `comes`.

```
  5A04DC351E3D7B9CC3CE1DFF5142B08B3AFCA60B
^ 3830206368617273206C696D697420636F6D6573 "80 chars limit comes"
  ----------------------------------------
  6234FC56765C09EFE3A27492383690E85591C378
^ 365C997610306888C3CB07B26C7ED39325E4AD1B
  ----------------------------------------
  54686520666C6167206973205448437B70756E63 "The flag is THC{punc"
```

Vu la première partie du challenge, cela ne peut être que `The flag is THC{punched`.

```
  365C997610306888C3CB07B26C7ED39325E4AD1BDC8725
^ 54686520666C6167206973205448437B70756E63686564 "The flag is THC{punched"
  ----------------------------------------------
  6234FC56765C09EFE3A27492383690E85591C378B4E241
^ 5A04DC351E3D7B9CC3CE1DFF5142B08B3AFCA60B948433
  ----------------------------------------------
  3830206368617273206C696D697420636F6D6573206672 "80 chars limit comes fr"
```

On ne peut pas faire plus facile : `80 chars limit comes from`.

```
  5A04DC351E3D7B9CC3CE1DFF5142B08B3AFCA60B9484336B96
^ 3830206368617273206C696D697420636F6D65732066726F6D "80 chars limit comes from"
  --------------------------------------------------
  6234FC56765C09EFE3A27492383690E85591C378B4E24104FB
^ 365C997610306888C3CB07B26C7ED39325E4AD1BDC87255B8F
  --------------------------------------------------
  54686520666C6167206973205448437B70756E636865645F74 "The flag is THC{punched_t"
```

Une rapide recherche Google (qui plus est si l'on met l'espace ce qui nous donne `a`) nous permet de trouver `punched_tape`.

```
  365C997610306888C3CB07B26C7ED39325E4AD1BDC87255B8F5E54B6
^ 54686520666C6167206973205448437B70756E636865645F74617065 "The flag is THC{punched_tape"
  --------------------------------------------------------
  6234FC56765C09EFE3A27492383690E85591C378B4E24104FB3F24D3
^ 5A04DC351E3D7B9CC3CE1DFF5142B08B3AFCA60B9484336B961F54A6
  --------------------------------------------------------
  3830206368617273206C696D697420636F6D65732066726F6D207075 "80 chars limit comes from pun"
```

Encore une fois, il faut réutiliser le mot `punched`.

```
  5A04DC351E3D7B9CC3CE1DFF5142B08B3AFCA60B9484336B961F54A67319304E88
^ 3830206368617273206C696D697420636F6D65732066726F6D2070756E63686564 "80 chars limit comes from punched"
  -------------------------------------------------------------------
  6234FC56765C09EFE3A27492383690E85591C378B4E24104FB3F24D31D7A582BEC
^ 365C997610306888C3CB07B26C7ED39325E4AD1BDC87255B8F5E54B66E253759B3
  ------------------------------------------------------------------
  54686520666C6167206973205448437B70756E636865645F74617065735F6F725F "The flag is THC{punched_tapes_or_"
```

Enfin, on peut complèter n'importe laquelle des deux phrases avec `cards`, ce qui nous donne le drapeau complet.

```
  365C997610306888C3CB07B26C7ED39325E4AD1BDC87255B8F5E54B66E253759B306A9BAA01B7D4A "The flag is THC{punched_tapes_or_cards}."
^ 6234FC56765C09EFE3A27492383690E85591C378B4E24104FB3F24D31D7A582BEC43021316170E00
  --------------------------------------------------------------------------------
  5A04DC351E3D7B9CC3CE1DFF5142B08B3AFCA60B9484336B961F54A67319304E8845ABA9B60C734A "80 chars limit comes from punched cards."

```

Félicitations, il n'y a plus qu'à valider avec `THC{punched_tapes_or_cards}`.
