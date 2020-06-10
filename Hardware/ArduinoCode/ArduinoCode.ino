#include <ArduinoJson.h>
#include <SoftwareSerial.h>
#include <TimerOne.h>

double T, xung;
double tocdo, Tocdodat;
float E, E1, E2;
float alpha, beta, gamma, Kp, Kd, Ki;
float Output , LastOutput;
float u,y; //Filter
//Software serial
const byte RX = 8;
const byte TX = 9;
String Tocdodat_String;
SoftwareSerial mySerial = SoftwareSerial(RX, TX);


void setup() {
  //IO
  pinMode(2, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  pinMode(3, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  //PID Parameter
  Tocdodat =150; //Max 245-Min 80
  tocdo = 0;
  E = 0; E1 = 0; E2 = 0;
  T = 0.01;
  Kp = 0.016670420034878; Kd = 0; Ki = 0.0547498772735634;
  //Serial
  Serial.begin(9600);
  //|------------Truyen UART----------|
  //0mySerial.begin(9600);
  //|---------------------------------|

  //Timer
  attachInterrupt(0, Demxung, FALLING);
  Timer1.initialize(10000);
  Timer1.attachInterrupt(PID);
}

void loop() {
  int i;
  for (i = 0; i < 10; i++)
    delay(1);
    Serial.println(tocdo);
    if(Serial.available()){
      Tocdodat_String = Serial.readStringUntil('\n');
      Tocdodat = Tocdodat_String.toInt();
      }
}
void Demxung() {
  if (digitalRead(4) == LOW) xung++;
  else xung--;
}
void PID () {
  tocdo = (xung / 1500) * (1 / T) * 60;
  u = (float)tocdo*5/1024;
  tocdo = 0.945*tocdo + 0.0549*u;
  xung = 0;
  E = Tocdodat - tocdo;
  alpha = 2 * T * Kp + Ki * T * T + 2 * Kd;
  beta = T * T * Ki + 4 * Kd + 2 * T * Kp;
  gamma = 2 * Kd;
  Output = (alpha * E + beta * E1 + gamma * E2 + 2 * T * LastOutput) / (2 * T);
  LastOutput = Output;
  E2 = E1;
  E1 = E;
  if (Output > 255) Output = 255;
  if (Output < 0) Output = 0;
  if (Output > 0)
  {
    analogWrite(3, Output);
    digitalWrite(10, HIGH);
    digitalWrite(11, LOW);
  }
  else {
    analogWrite(3, 0);
    digitalWrite(10, LOW);
    digitalWrite(11, LOW);
  }

}
