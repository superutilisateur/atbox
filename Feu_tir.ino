#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <EEPROM.h>

//Custom IO definition
#define GREEN 15 //A1
#define ORANGE 16
#define RED 17
#define BT1_PIN  10
#define BT2_PIN  9
#define BT3_PIN  8
#define BZ_PIN  3
#define I2C_ADDR  0x27

#define SND_STATU_ADDR  1
#define PWM_RATIO_ADDR  2
#define TIMER2_ADDR  3
#define TIMER1_ADDR  4
//risque de limitation : par defaut on est a 3,5 min soit 180+30s = 210s -1s pour le beep de depart

//etats
#define ST_WAIT 0
#define ST_START 1
#define ST_P1 2
#define ST_P2 3
#define ST_END 4
#define ST_OPT 5
#define ST_OPT_TEMP 6
#define ST_OPT_TEMP_SET 7
#define ST_OPT_SND 8
#define ST_OPT_SND_SET 9
#define ST_OPT_SND_PWM 10
#define ST_OPT_TEMP_SET_P1 11
#define ST_OPT_TEMP_SET_P2 12


//evenements controles
#define NO_EVENT  0
#define BT1_EVENT  1
#define BT2_EVENT  2
#define BT3_EVENT  3

//temp d'attente entre chaque boucle (ms)
#define LoopWait  100
//nombre de boucles par seconde
#define LoopbySec  10

//timers (durées en s)
#define Temps_TEST  4

int temps_P1 = 0;
int temps_P2 = 30;
int timer = 0;

int prev_status = ST_WAIT;
int status = ST_WAIT;
int btEvent = NO_EVENT;
int lastState = NO_EVENT;
int configPwm = 0;
bool startSnd = false;
bool stopSnd = false;

LiquidCrystal_I2C lcd(0x27, 20, 4);

void setup() {
  //initialisation de l'affichage et des I/O
  lcd.init();
  lcd.clear();
  lcd.backlight();
  pinMode(GREEN, OUTPUT);
  pinMode(ORANGE, OUTPUT);
  pinMode(RED, OUTPUT);
  pinMode(BZ_PIN, OUTPUT);
  pinMode(BT1_PIN, INPUT_PULLUP);
  pinMode(BT2_PIN, INPUT_PULLUP);
  pinMode(BT3_PIN, INPUT_PULLUP);

  //on charge la config (byte)
  int activeSnd = EEPROM.read(SND_STATU_ADDR);
  startSnd = activeSnd % 2;
  stopSnd = activeSnd >> 1;
  configPwm = EEPROM.read(PWM_RATIO_ADDR);

  temps_P1 = EEPROM.read(TIMER1_ADDR);
  temps_P2 = EEPROM.read(TIMER2_ADDR);

}

void loop() {
  int buttonState = NO_EVENT;
  //Temporisation de 100 ms pour la boucle principale
  unsigned long endOfLoop = millis() + LoopWait;
  manageState();
  //note : les évenements des touches sont consommé ici, apres chaque boucle de 100ms
  consumeBtEvent();

  //On attend la fin du temps disponible pour la boucle
  //(on ne prend pas en compte les dépassement)
  while (millis() < endOfLoop) {
    if (LOW == digitalRead(BT1_PIN))
      buttonState = BT1_EVENT;
    else if (LOW == digitalRead(BT2_PIN))
      buttonState = BT2_EVENT;
    else if (LOW == digitalRead(BT3_PIN))
      buttonState = BT3_EVENT;
  }
  if (lastState != buttonState && buttonState == NO_EVENT)
  {
    btEvent = lastState;
  }
  lastState = buttonState;
}
