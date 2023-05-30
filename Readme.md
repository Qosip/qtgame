# Readme du projet qt - FR

Ce Readme va expliquer la nature du projet, ses détails, comment jouer, ainsi que des informations complémentaire.  
Nombre de Participants : 1  
Heures : ~150h  
Langage : C++ accompagné de Qt 5.15.2  
Durée : 1 mois  
Année : Isen CIR2 Mars/Avril 2023  
Vidéo : https://www.youtube.com/watch?v=fmkm5IIBKJY

# Le Projet
Ce projet à été effectué dans le cadre de la fin d'un module C++ en CIR2.  
Le Cahier des charges minimal était :    
	•  Le joueur contrôle le personnage au clavier    
	•  Un meilleur score est mémorisé (temps d'arrivée ou score basé sur le temps écoulé)    
	•  Une vue est centrée sur le personnage principal qui évolue dans une scène    
	•  Le choix de l'esthétique et des règles du jeu est libre    
	•  On doit pouvoir recommencer une partie lorsque le joueur a perdu sans devoir relancer le programme  

## Lancer le projet  
Dans l'archive se trouvent le dossier du projet ainsi que son build. Tous les fichiers nécessaires se trouvent à l'interieur du dossier "qtprojetbase".   
11 fichiers .cpp  
10 fichiers .h  
5131 lignes  
Dans le dossier "/qtprojetbase/src/" : 697 fichiers / 55 dossiers  
Le projet à été développé à l'aide de la version 5.15.2 de Qt.  
Si tout se passe bien, aucun préréglages ou action de l'utilisateur n'est à prévoir avant de lancer le projet.  
:warning:```Si vous lancez le projet sur un ordinateur portable : Il est fortement recommandé de brancher votre pc pour des soucis de performances (surtout pour le niveau 3)```  

## Description du jeu en lui-même
En lancant le code vous arriverez sur un Menu, d'ici vous pourrez soit regarder le ScoreBoard, quitter l'application ou bien lancer une partie.  
Si vous voulez que votre pseudo soit sauvegardé lors de l'enregistrement du score pensez bien à le mettre dans la case prévue à cet effet avant d'appuyer sur "Jouer".  
Le jeu comporte un Tuto qui explique quelles touches doivent être utilisées pour jouer.  
Après se tuto il y aura 3 niveaux. L'objectif étant de ramasser des pièces, tuer des ennemis, perdre le moins de coeurs et le tout en le moins de temps possible.  
Vous pourrez quitter/mettre en pause la partie à tout moment et revenir au menu en appuyant sur "t".  

## Touches
q = Aller à gauche  
d = Aller à droite  
q+shift = Slide à gauche  
d+shift = Slide à droite  
espace = Sauter  
t = Mettre en pause le jeu  
r = Respawn au dernier Checkpoint  
e = bouton d'action (Passer le niveau au contact des diamants blanc/noir, ouvrir les coffres) (Bien rester appuyé le temps de l'animation)  
clic droit de la souris = tirer une flèche (maintenir le clic)  

## Spécificités
L'arc peut soit tirer à droite ou à gauche du personnage, pour déterminer le sens il faut placer le curseur de la souris du côté du personnage où vous voulez tirer la flèche.  
Pour faire des dégâts aux ennemis vous pouvez soit tirer à l'arc, soit leurs donner un coup de "slide".  
Vous pouvez regagner de la vie en tuant un ennemis mais seulement en le tuant grâce au "slide".  
Vous pouvez subir des dégâts de chute si vous tomber de trop haut.  

## Fonctions incluses dans le jeu  
Lorsque vous tomber de haut la caméra tremble.  
Lors du saut du personnage des particules apparaissent sous ses pieds.  
Au niveau tuto et niveau 1 au fur et à mesure que vous avancez la scène s'assombrit.  
A ces mêmes niveaux les arbres bougent lorsque le personnage avance.  
Un compagnon oiseau va vous suivre tout à long de votre partie. Il ne donne aucun avantage ni aide. Il se dirige tout seul et peut picorer lorsqu'il est posé.  
Des plateformes sont mouvantes et d'autres peuvent se casser.  
Il y a trois ennemis différents.  
Des coffres contenant des pièces sont obtenables (restez appuyé sur "E" au contact de l'un d'entre eux.  
Des checkpoint sont inclus (diamants rouges), lorsque vous validez le checkpoint celui-ci devient vers et vous pouvez y respawn en appuyant sur "r".  
Pour des soucis de fluidité du mouvement et ne pas avoir de frustration de la part du joueur (ne pas pouvoir sauter si vous êtes 1px en dehors du bloc, ne pas accomplir un saut si vous êtes à 2px de le réussir), vous pouvez sauter sans toucher de plateformes. Cependant le saut reste unique et vous ne pourrez pas sauter plusieurs fois à la suite. Pour les blocs "haut droit" et "haut gauche" le joueur se déplace directement au dessus du bloc.  

## Bug connu
Si vous appuyez sur une touche de déplacement (droite ou gauche) lors du lancement du jeu, vous allez vous déplacer/glisser sans rien faire. Il faudra donc fermer la fenêtre et relancer.  
Le prochain n'est pas un bug mais une chose à laquelle prêter attention. Si vous ne pouvez pas aller à droite ou à gauche alors que vous pensez pourtant le pouvoir, c'est que vous avez collisionné un bloc qui vous empêche de vous déplacer dans le sens voulu. Pour cela donnez juste un coup dans le sens opposé et vous serez libre de ré avancer.

## Crédits

Personnage : https://legnops.itch.io/red-hood-character  
Tileset principal : https://www.gamedevmarket.net/asset/free-simple-pixel-tileset-16x16/  
Assets lvl 3 : https://www.kenney.nl/assets/1-bit-platformer-pack  
Sorcerer : https://lionheart963.itch.io/wizard  
NightBorne : https://creativekind.itch.io/nightborne-warrior  
Wolves : https://admurin.itch.io/enemy-winter-canines  
Transition entre les levels : https://pimen.itch.io/holy-spell-effect  
Hearts : https://fliflifly.itch.io/hearts-and-health-bar  
Background et arbres : https://szadiart.itch.io/platformer-fantasy-set1  
  
(dans les fichiers github manquent les assets du personnage et des ennemis)

Pour toute question ou problème : fddavid.francois@gmail.com  
François DAVID
