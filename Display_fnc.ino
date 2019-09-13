
//fonctions de gestion d'affichage (16 char, 2 lignes)

void lcdClear() {
  lcd.clear();
}

void waitMsg() {
  lcd.setCursor(0, 0);
  lcd.print("1: Demarrer");
  lcd.setCursor(0, 1);
  lcd.print("2: Options");
}
void BeepMsg() {
  lcd.setCursor(0, 0);
  lcd.print("Go !");
}
void PhaseMsg() {
  lcd.setCursor(0, 0);
  lcd.print("1: Interrompre");
  lcd.setCursor(0, 1);
  lcd.print(" -> reste: " + String(timer / LoopbySec) + "s ");
}
void OptMainMsg() {
  lcd.setCursor(0, 0);
  lcd.print("1: Audio");
  lcd.setCursor(0, 1);
  lcd.print("2: Temporisation");
}

//-------------------------------

void OptTempoMsg() {
  lcd.setCursor(0, 0);
  lcd.print("1: Vert");
  lcd.setCursor(0, 1);
  lcd.print("2: Orange");
}

void OptMsgTempo1() {
  lcd.setCursor(0, 0);
  lcd.print("tempo. Vert");
  lcd.setCursor(0, 1);
  lcd.print("(en s) :");
  lcd.print(temps_P1);
}

void OptMsgTempo2() {
  lcd.setCursor(0, 0);
  lcd.print("tempo. Orange");
  lcd.setCursor(0, 1);
  lcd.print("(en s) :");
  lcd.print(temps_P2);
}

//-------------------------------

void OptMsgSnd() {
  lcd.setCursor(0, 0);
  lcd.print("1: Activation");
  lcd.setCursor(0, 1);
  lcd.print("2: tonalite");
}

void OptMsgSndActive() {
  lcd.setCursor(0, 0);
  lcd.print("1/2 :  debut|fin");
  lcd.setCursor(0, 1);
  //lcd.print("3:retour");
  lcd.setCursor(9, 1);
  lcd.print(startSnd ? "OUI" : "NON");
  lcd.setCursor(13, 1);
  lcd.print(stopSnd ? "OUI" : "NON");
}

void OptMsgSndPwm() {
  lcd.setCursor(0, 0);
  lcd.print("tonalite(1/2)");
  lcd.setCursor(3, 1);
  lcd.print('<');
  for (int i = 0; i < 8; i++)
    lcd.print( configPwm >> i == 1 ? (char)255 : ' ');
  lcd.print('>');
}
