/*
  -----Gestion du deroulemment des operation (machine a état)-----

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
*/

void manageState() {
  //gestion de l'effacemet
  if (prev_status != status)
  {
    prev_status = status;
    lcdClear();
  }

  switch (status) {
    case ST_WAIT : //--------------------------W8
      ledRed();
      waitMsg();
      if (btEvent == BT1_EVENT) {
        status = ST_START;
      }
      else if (btEvent == BT2_EVENT) {
        status = ST_OPT;
      }
      break;
    case ST_START : //----------------------------
      ledRed();
      BeepMsg();
      timer = temps_P1 * LoopbySec;
      beep(true); //start beep
      status = ST_P1;
      break;
    case ST_P1 :   //--------------------------P1
      ledGreen();
      resetOnBt3();
      if  (timer > 0 && btEvent != BT1_EVENT) {
        if (timer % LoopbySec == 0)
          PhaseMsg();
        timer--;
      }
      else {
        status = ST_P2;
        timer = temps_P2 * LoopbySec;
      }
      break;
    case ST_P2 : //--------------------------P2
      ledOrange();
      resetOnBt3();
      if (timer > 0 && btEvent != BT1_EVENT) {
        if (timer % LoopbySec == 0)
          PhaseMsg();
        timer--;
      }
      else {
        status = ST_END;
      }
      break;
    case ST_END  : //------------------------END
      ledRed();
      beep(false);
      status = ST_WAIT;
      break;
    case ST_OPT : //--------------------------OPTIONS
      OptMainMsg();
      navigate(ST_OPT_SND, ST_OPT_TEMP);
      break;
    case ST_OPT_TEMP    : //----------------Menu tempo
      OptTempoMsg();
      navigate(ST_OPT_TEMP_SET_P1, ST_OPT_TEMP_SET_P2);
      break;
    case ST_OPT_TEMP_SET_P1: //----------------config P1
      OptMsgTempo1();
      if (btEvent == BT1_EVENT ) {
        temps_P1 --;
        if (temps_P1 < 1)
          temps_P1 = 1;
      }
      if (btEvent == BT2_EVENT) {
        temps_P1 ++;
        if (temps_P1 > 250)
          temps_P1 = 250;
      }
      if (btEvent == BT3_EVENT) {
        updateTempoConfig();
        status = ST_OPT_TEMP;
      }
      break;
    case ST_OPT_TEMP_SET_P2: //----------------config P1
      OptMsgTempo2();
      if (btEvent == BT1_EVENT ) {
        temps_P2 --;
        if (temps_P2 < 1)
          temps_P2 = 1;
      }
      if (btEvent == BT2_EVENT) {
        temps_P2 ++;
        if (temps_P2 > 250)
          temps_P2 = 250;
      }
      if (btEvent == BT3_EVENT) {
        updateTempoConfig();
        status = ST_OPT_TEMP;
      }
      break;
    case ST_OPT_SND     : //----------------Menu son
      //menu son
      OptMsgSnd();
      navigate(ST_OPT_SND_SET, ST_OPT_SND_PWM);
      break;
    case ST_OPT_SND_SET ://----------------config beep
      OptMsgSndActive();
      if (btEvent == BT1_EVENT) {
        startSnd = !startSnd;
      }
      if (btEvent == BT2_EVENT) {
        stopSnd = !stopSnd;
      }
      if (btEvent == BT3_EVENT) {
        updateSndConfig();
        status = ST_OPT_SND;
      }
      break;
    case ST_OPT_SND_PWM ://----------------config pwm
      OptMsgSndPwm();
      if (btEvent == BT1_EVENT ) {
        configPwm = configPwm >> 1;
        if (configPwm < 1)
          configPwm = 1;
        beepTest();
      }
      if (btEvent == BT2_EVENT) {
        configPwm = configPwm << 1;
        if (configPwm > 64)
          configPwm = 64;
        beepTest();
      }
      if (btEvent == BT3_EVENT) {
        updateSndConfig();
        status = ST_OPT_SND;
      }
      break;
  }
}

//gestion des menus

boolean resetOnBt3() {
  if (btEvent == BT3_EVENT) {
    //BT3 detecté, on fait un "Reset" (retour mode attente)
    status = ST_WAIT;
    return true;
  }
  return false;
}

//permet de naviguer entre 2 etats ou de revenir au depart
void navigate(int state1, int state2) {
  if (btEvent == BT1_EVENT)
    status = state1;
  if (btEvent == BT2_EVENT)
    status = state2;
  if (btEvent == BT3_EVENT) {
    lcdClear();
    status = ST_WAIT;
  }
}
