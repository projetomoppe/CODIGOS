#include <LiquidCrystal.h>
#include <Ultrasonic.h>

//Define os pinos para o trigger e echo
#define pino_trigger 7   //define o o pino do trigger.
#define pino_echo 6 //define o pino do echo.

//Inicializa o sensor nos pinos definidos acima
Ultrasonic ultrasonic(pino_trigger, pino_echo);
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
void setup(){
 
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
  //Exibe informacoes no serial monitor
  Serial.print("Distancia em cm: ");
  Serial.println(cmMsec);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.setCursor(0,0);

}
