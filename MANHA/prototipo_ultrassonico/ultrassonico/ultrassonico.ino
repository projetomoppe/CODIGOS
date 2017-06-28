#include <LiquidCrystal.h>
#include <Ultrasonic.h>

//Define os pinos para o trigger e echo
#define pino_trigger 13 //define o o pino do trigger.
#define pino_echo 12 //define o pino do echo.
#define ledvd 10 //define o pino do led verde.
#define ledvm 11 //define o pino do led vermelho.
#define ledam 7 //define o pino do led amarelo.
#define buzz 9 //define o pino do buzzer.

 float referencia = 17.0; //referencia do tamanho total do recipiente ou local.
 float alerta1 = 5.0; //primeiro nivel de alerta.
 float alerta2 = 10.0; //segundo nivel de alerta.
 
//Inicializa o sensor nos pinos definidos acima
Ultrasonic ultrasonic(pino_trigger, pino_echo);
LiquidCrystal lcd(6,5,4,3,2,8);
void setup(){
  pinMode(ledvd, OUTPUT); //define o pino como output.
  pinMode(ledvm, OUTPUT); //define o pino como output.
  pinMode(ledam, OUTPUT); //define o pino como output.
  pinMode(buzz, OUTPUT); //define o pino como output.
 
  Serial.begin(9600); //inicia o serial monitor.
  lcd.begin(16,2);
  Serial.println("Lendo dados do sensor...");
}
 
void loop()
{
  //Le as informacoes do sensor, em cm e pol
  float cmMsec, inMsec;
  long microsec = ultrasonic.timing();
  cmMsec = ultrasonic.convert(microsec, Ultrasonic::CM);
  float nivel = referencia - cmMsec;
  //Exibe informacoes no serial monitor
  Serial.print("Distancia em cm: ");
  Serial.println(cmMsec);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("NIVEL:");
  lcd.setCursor(7,0);
  lcd.print(nivel);
  lcd.print(" cm");

  if (nivel < alerta1 ){
    digitalWrite(ledvd, HIGH);
  }else{
    digitalWrite(ledvd, LOW);
  }
  if (nivel >= alerta1 && nivel < alerta2 ){
    digitalWrite(ledam, HIGH);
  }else {
    digitalWrite(ledam, LOW);
  }

  if (nivel >= alerta2 ){
    digitalWrite(ledvm,HIGH);
    digitalWrite(buzz, HIGH);
    delay(100);
    digitalWrite(buzz, LOW);
    delay(100);
  }else {
    digitalWrite(ledvm,LOW);
    digitalWrite(buzz, LOW);
  }

  delay(1000);
}
