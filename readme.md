# Murmuration 

Un nombre défini d'instances de lecteur sonore errent dans un espace.
De gauche à droite, c'est la panoramisation 
De haut en bas, c'est la vitesse de lecture.

Toutes les boules de couleurs sont des lecteurs d'un son qui réagissent de manière autonome aux règles de l'environnement.
Présentement il y a quatre modes soit 
* Attraction (vers la souris) 
* Répulsion (de la souris)
* Attracteurs (4 points aléatoires )
* Snowfall


les touches d'actions sont :
* les chiffres 1 2 3 4  définies le mode de comportement des particules, 
* la touche espace réinitialise le système 


il y a quelques paramètres accessibles, 
* le nombre de particules (présentement le maximum est 100, mais ça pourrait être plus)
* la friction (force de rétention) (pas encore effective dans tous les modes)
* le drag (aussi une force de rétention pas encore effective dans tous les modes )
* playbackspeedmin est la vitesse minimale de lecture de l'échantillon (si à 0.5, la lecture ne sera pas inférieure à 0.5)
* plackbackspeedRange est l'étendue de la vitesse de lecture (si à 2, la vitesse de lecture sera de la vitesse minimum à la vitesse minimum + 2)
* loadSound : permets de charger un son

Fonctionne bien avec des écouteurs, mais pourraient éventuellement être adaptés pour supporter plusieurs canaux.


# Installation : 
* nécessite [openframeworks](http://openframeworks.cc/download/)
* placer le dossier de projet de murmuration dans {ofFolder}/apps/myApps/
* exécuter le project manager de openframeworks pour lier les addons (ofxGui et ofxOsc) 
* testé sous OSX 10.11 et OF 0.98