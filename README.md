# atbox
code arduino pour boitier de control tir

Fonctionnement:
```
3 bouton de commande sont disponible (bt1, bt2 et bt3)
  3 feux de couleur sont pilotés
  1 ecran de controle affiche l'etat, et la temporisation au besoin
  1 generateur se son
  Liste des etats
  [etat Attente] de commandes (rouge allumé, on attend une touche, 3 touches possibles)
  -bt1 declanche la séquence phase 1
  -bt2 passe en mode reglages
  (-bt3 declanche l'auto test)
  [etat phase 1] (vert allumé, temporisation par defaut : 3min 30s)
  - bt1 ou fin de temporisation declanche la sequence phase 2
  (- bt3 passe en mode attente)
  [etat phase 2] (vert allumé, temporisation par defaut : 3min 30s)
  - bt1 ou fin de temporisation, passe en mode attente
  (- bt3 passe en mode attente)
  [etat fin] la fin de séquence peut etre annoncé par un son (temporisation 1s)
  -attente tempo
  -raz du buffer commande avant de quitter
  -retour etat attente
  [etat reglages]
  -liste les options de reglage
    temporisation
      phase 1
        temps s
      phase 2
        temps s
    signal sonore
      debut tir
        oui/non
      arret tir
        oui/non
```
