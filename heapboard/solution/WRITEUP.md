# Write-up

Nous sommes en présence d'un binaire `heapboard` qui présente quelques fonctionnalités de sécurité classiques.

```bash$ file heapboardheapboard: ELF 32-bit LSB executable, Intel 80386, version 1 (SYSV), dynamically linked, interpreter /lib/ld-linux.so.2, for GNU/Linux 2.6.32, BuildID[sha1]=063a809e986aff1eb61fafcbcce7d7890add19fd, stripped

$ checksec.sh --file heapboardRELRO           STACK CANARY      NX            PIE             RPATH      RUNPATH      FILEFull RELRO      Canary found      NX enabled    No PIE          No RPATH   No RUNPATH   heapboard```

En lançant le programme et en jouant avec, nous nous retrouvons avec un petit forum simpliste qui nous permet de créer des sujets avec un auteur, un titre et un contenu. Il permet aussi d'afficher les sujets, de les modifier, d'y répondre et de les supprimer.

```
 _    _                  ____                      _ | |  | |                |  _ \                    | || |__| | ___  __ _ _ __ | |_) | ___   __ _ _ __ __| ||  __  |/ _ \/ _` | '_ \|  _ < / _ \ / _` | '__/ _` || |  | |  __/ (_| | |_) | |_) | (_) | (_| | | | (_| ||_|  |_|\___|\__,_| .__/|____/ \___/ \__,_|_|  \__,_|                  | |                                                  |_|                                What do you want to do?  1. Create a new thread  2. Display all threads  3. Exit the board> 1Author: NeatMonsterTitle: My Cool TitleContent: This is some content.What do you want to do?  1. Create a new thread  2. Display all threads  3. Exit the board> 2-------------------------------------------------------| index | author               | title                |-------------------------------------------------------|     1 | NeatMonster          | My Cool Title        |-------------------------------------------------------Which thread would you like to see?> 1-------------------------------------------------------|     1 | NeatMonster          | My Cool Title        |-------------------------------------------------------| This is some content.                               |-------------------------------------------------------| NO COMMENTS IN THIS THREAD                          |-------------------------------------------------------What do you want to do?  1. Comment in the thread  2. Modify the thread  3. Delete the thread  4. Go back to main menu> 1Comment: Nice thread.What do you want to do?  1. Create a new thread  2. Display all threads  3. Exit the board> 2-------------------------------------------------------| index | author               | title                |-------------------------------------------------------|     1 | NeatMonster          | My Cool Title        |-------------------------------------------------------Which thread would you like to see?> 1-------------------------------------------------------|     1 | NeatMonster          | My Cool Title        |-------------------------------------------------------| This is some content.                               |-------------------------------------------------------| Nice thread.                                        |-------------------------------------------------------What do you want to do?  1. Comment in the thread  2. Modify the thread  3. Delete the thread  4. Go back to main menu> 4What do you want to do?  1. Create a new thread  2. Display all threads  3. Exit the board> 3Exiting...```

Pour aller plus loin, il va être nécessaire de faire un peu d'analyse statique sur le programme. En creusant un peu, on comprend que le programme comporte deux structures principales, celle des sujets, et celle des commentaires, qui sont stockées sur le tas.

```00000000 thread          struc ; (sizeof=0x28)00000000 prev            dd ?                    ; offset00000004 next            dd ?                    ; offset00000008 index           dd ?0000000C author          dd ?                    ; offset00000010 title           dd ?                    ; offset00000014 content         dd ?                    ; offset00000018 size            dd ?0000001C comments        dd ?                    ; offset00000020 unknown         dd ?                    ; offset00000024 delete_func     dd ?                    ; offset00000028 thread          ends
```

La structure `thread` comporte une liste doublement chaînée, quelques pointeurs vers des chaînes de caractères, un pointeur vers une liste de commentaires et un compteur, et enfin un pointeur de fonction utilisé pour la suppression.

```
00000000 comment         struc ; (sizeof=0x14)00000000 next            dd ?                    ; offset00000004 index           dd ?00000008 text            dd ?                    ; offset0000000C unknown         dd ?                    ; offset00000010 delete_func     dd ?                    ; offset00000014 comment         ends
```

La structure `comment` comporte une liste chaînée simple, un pointeur vers une chaîne de caractères et un pointeur de fonction utilisé lui aussi lors de la suppression du sujet parent.

En jettant un coup d'oeil approfondi à l'application, on peut dénicher plusieurs bugs.

Le champ `size` contenant le nombre de commentaires laissés sur un article est utilisé comme un octet seul au lieu d'un entier. Il est utilisé notamment pour initialiser les fonctions de suppression des commentaires.

```c
if ( SLOBYTE(thread->size) > 0 ){  for ( comment = thread->comments; comment; comment = comment->next )    comment->delete_func = free;}
```

On remarque donc que si le nombre de commentaires vaut 256, le champ `size` vaudra 0 et l'intialisation ne sera pas faite.

Un peu plus loin, ce pointeur de fonction est utilisé pour la suppression du commentaire.

```c
comment = thread->comments;if ( comment ){  do  {    next_comment = comment->next;    comment->delete_func(comment->text);    comment->delete_func(comment);    comment = next_comment;  }  while ( next_comment );}
```

On a donc un pointeur de fonction dont on peut empêcher l'initalisation, et influencer le contenu en fonction d'un ancien contenu dans le tas. Mais comment faire ? On remarque que parmi les appels à la fonction `malloc`, celui du contenu d'un sujet est fait avec un tampon de taille 8000 octets. C'est celui que nous allons utiliser pour l'exploitation.

Pour exploiter la faille, nous allons devoir...

1. créer trois sujets (#1, #2, #3) ;
2. remplir le sujet #2 avec un grand contenu, de préférence un motif cyclique pour faciler la recherche des divers décalages ;
3. supprimer le sujet #2 pour libérer la mémoire ;
4. créer deux nouveaux sujets (#4, #5) ;
5. ajouter suffisament de commentaires au sujet #4 pour éviter l'intialisation ;
6. supprimer le sujet #4 pour déclencher l'appel.

En manipulant le contenu du sujet #2, nous sommes en mesure de manipuler les données non-initialisés du sujet #4. Nous allons chercher à placer l'adresse de la fonction `system` dans le champ `delete_func` du permier commentaire.

Le script Python donné en annexe nous permet de recupérer un *shell* sur la machine distance. Il n'y a plus qu'à faire un `cat flag.txt` pour récupérer le drapeau tant recherché.

```bash
$ ls
flag.txt
heapboard
$ cat flag.txt
THC{my_board_is_the_best_board}
```


