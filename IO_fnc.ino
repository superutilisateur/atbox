
//fonction d'accesibilité pour les IO

void ledOff() {
  digitalWrite(GREEN, HIGH);
  digitalWrite(ORANGE, HIGH);
  digitalWrite(RED, HIGH);
}
void ledGreen() {
  digitalWrite(GREEN, LOW);
  digitalWrite(ORANGE, HIGH);
  digitalWrite(RED, HIGH);
}
void ledOrange() {
  digitalWrite(GREEN, HIGH);
  digitalWrite(ORANGE, LOW);
  digitalWrite(RED, HIGH);
}
void ledRed() {
  digitalWrite(GREEN, HIGH);
  digitalWrite(ORANGE, HIGH);
  digitalWrite(RED, LOW);
}

//on declanche la sortie <!> ca fait du bruit a 490Hz
void beep(boolean start) {
  //on ne beep que la la config est activé (bit 1 pour le start, 2 pour le end)
  if ((start && startSnd) || (!start && stopSnd)) {
    analogWrite(BZ_PIN, configPwm);
    delay(1000);
    analogWrite(BZ_PIN, 0);
  }
  else
    delay(1000);
}

void beepTest() {
  analogWrite(BZ_PIN, configPwm);
  delay(100);
  analogWrite(BZ_PIN, 0);
}

void consumeBtEvent() {
  btEvent = NO_EVENT;
}

void updateSndConfig() {
  int snd = startSnd;
  if (stopSnd)
    snd += 2;
  EEPROM.update(SND_STATU_ADDR, snd);
  EEPROM.update(PWM_RATIO_ADDR, configPwm);
}


void updateTempoConfig() {
  EEPROM.update(TIMER1_ADDR, temps_P1);
  EEPROM.update(TIMER2_ADDR, temps_P2);
}
