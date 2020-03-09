# AOAOAOAOA
Projet d'AOA (Architecture des ordinateurs avancée)

Phase I
=======
1) Mesurez la performance du noyau avec gcc -O2, gcc -O3, gcc -O3
-march=native, icc -O2, icc -O3 et
icc -O3 -xHost.
2) Recommencez avec d'autres options d'optimisation qui vous
sembleraient pertinentes (vous devrez les chercher dans la
documentation de gcc et d'icc), que vous pourrez combiner entre elles...
3) Expliquez les différences de performances entre versions avec MAQAO
(*) et likwid-perfctr (**)
4) Question indépendante des 6 premières : justifiez les points
d'implémentation du driver susceptibles d'impacter les mesures. Vous en
ferez notamment une analyse de sensibilité (montrez par exemple
qu'augmenter un paramètre au-delà d'une certaine limite a un impact
négligeable...)

Phase II
========
0) Configurez la compilation selon le sujet (à défaut, gcc -O2)
1) Mesurez la performance du noyau
2) Analysez le noyau avec MAQAO (*) et likwid-perfctr (**)
3) Identifiez le goulet d'étranglement (ce qui limite les performances)
4) Proposez une optimisation (au niveau source)
5) Recommencez (rebouclez à l'étape 1) tant que vous arrivez à
améliorer les performances. Vous pouvez soit repartir du noyau non
optimisé, soit d'un noyau précédemment optimisé
6) Une fois (mais pas avant) que vous n'arrivez plus à obtenir de gain,
notez bien les performances correspondantes ainsi que toutes les étapes
qui vous ont permis d'y arriver puis relâchez la contrainte sur la
compilation : vous pouvez alors utiliser des options plus agressives
ou/et un autre compilateur => rebouclez à l'étape 1 jusqu'à ne plus
obtenir de gain supplémentaire
7) Utilisez des directives OpenMP pour paralléliser votre noyau. S'il
ne vous semble pas parallélisable, expliquez pourquoi, et comment on
pourrait malgré tout le paralléliser (avec degré de concurrence
moindre, autre algorithme etc.)
8) Question facultative (1 à 2 points bonus) : Utilisez des intrinsics
pour écrire/optimiser le code (niveau avancé), voire modifiez
directement l'assembleur (niveau expert). Vous pouvez également
utiliser le compilateur ISPC (https://ispc.github.io/)

La nature itérative de cette phase doit transparaître dans vos rapports
autant que possible.

Notamment, dites en quoi MAQAO et likwid-perfctr vous ont aidé pour les
étapes 3 et 4. Dans le cas contraire, nous apprécierions que vous
critiquiez (de façon justifiée et si possible constructive) ces outils
avec preuves à l'appui.

Pour l'étape 4, vous trouverez une liste assez exhaustive de
transformations de boucles :
http://en.wikipedia.org/wiki/Loop_optimization#Optimization_via_a_sequence_of_loop_transformations

(*) MAQAO permet l'analyse statique de codes x86. Il est disponible
sous forme d'un binaire exécutable uniquement sous Linux x86_64. Page
web officielle : http://www.maqao.org

(**) likwid-perfctr permet de mesurer, pendant l'exécution d'un
programme, des compteurs matériels indiquant le comportement dynamique
de ce dernier vis à vis de la mémoire, des unités de calcul... Page web
officielle : https://github.com/RRZE-HPC/likwid
