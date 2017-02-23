# Compétition de reversing

# Créer le tarball

Lancez make pour créer le tarball qui va contenir les challenges, la documentation de `doc/` et le decompilateur java dans `tools`

```
make
```


# À installer sur la machine

## Utilitaires
- ce qui est dans tools/ 
- gdb
- radare2
- binutils
- un hex editor
- Les environnements de devs que vous voulez, Java, Python au minimum j'imagine

## Documentation
Toute la documentation qui se trouve dans `doc/`
- La documentation utilisateur de gdb
- La documentation officielle de radare2
- Un .html qui est la spec de x86 32bits et 64bits
- Un ptit tableau pris sur wikipedia en html

# À ne pas installer
- un interpréteur brainfuck
 
# À déterminer
- la pondération de chaque challenge

# Challenges

## ASM

C'est un challenge de reversing statique. Ce que je veux, c'est que les participants trouvent ce que cete fonction fait le plus en détail possible. Dans l'énoncé, il faudrait leur demander de mettre le plus de détail possible, notamment en disant combien de paramètres, l'ordre des paramètres, peut-être chercher à deviner le type. Ensuite, il faut qu'ils disent c'est quoi les grandes étapes de la fonction avec le plus de détail possible. 

Je m'attendrais qu'une réponse idéale dise que c'est une implémentation de strcpy. 
Les éléments de réponses :
* param 1: char * qui est la destination
* param 2: char * qui est la source
* la procédure calcule d'abord la taille de la source comptant jusqu'au null byte
* elle copie la première partie à coup de 4 bytes
* elle copie le nombre de bytes restants à coup d'un byte

## bin1
C'est un petit crackme. Je m'attendrais à ce qu'ils patchent un jump pour printer le flag.

FLAG : UQAM{T0_Jump_0r_N0t_T0_Jump_Th4t_1s_Th3_Qu3st10n}

## bin2
Un autre crackme avec un cipher du mot de passe xoré. Un ltrace afficherait le mot de passe.

FLAG : UQAM{strcmp_funct10n_kn0ws_n0th1ng_4b0ut_pr1v4cy}

## bin3
Un autre crackme mais avec un anti-debug utilisant ptrace.

FLAG : UQAM{4nt1_D3bugg3rs_4r3nt_So_B4d_Aft3r_All_R1ght?}

## bin4
C'est le binaire le plus difficile. Il y a deux anti-debugger : un ptrace et un qui regarde un delta temporel pour voir s'il y a un debugger d'attaché. Le delta est vérifié à chaque tour de la boucle de vérification de mot de passe pour rendre ça plus fastidieux.

FLAG : UQAM{I_W1sh_I_H4d_IDA_inst4lled_But_Wh0_C4n_4ff0rd_Th4t}

## brainfuck
C'est un petit programme brainfuck qui print le flag

FLAG : UQAM{I_Lov3_S1Mpl3_Sp3Cificat1ons}

## Encoding
Je donne le source C d'un programme qui a servi à encoder un .bmp. C'est un rle custom. Ils doivent coder l'algo inverse pour décoder le bmp et obtenir le flag.

FLAG : UQAM{rUn_LenGth_Encoding_1S_the_Futur3}

## Java1
Pour l'instant c'est un .jar, mais le fait de le décompiler enlève un peu de ma logique surperflue qui se voulait justement un casse-tête additionnel pour les participants. À voir si je ne vais pas donner le source directement. Sinon, il y a un programme dans `tools/` pour décompiler un .jar. C'est ce qui devra être installé sur les machines. L'algo fait simplement échanger des bits pour chacun des caractères, il suffit de faire l'opération inverse pour récupérer le mot de passe.

FLAG : UQAM{R3v3rs1ng_J4v4_1s_S0_Much_Fun}

## Java2
Un .jar comme l'autre et il faut trouver l'algo inverse. L'algo fait un calcul sur chaque caractère et il y a un algo qui permet de trouver le mot de passe en s'assurant qu'en soustrayant la valeur du dernier caractère, le nombre % 97 == 0.

FLAG : UQAM{D0ing_m4th_on_j4va_ch4r_is_s0_3v1l}



