#include <Ultrasonic.h>

#define TRIGGER_PIN  4
#define ECHO_PIN     5
double velocidade = 0;
Ultrasonic ultrasonic(TRIGGER_PIN, ECHO_PIN);

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  //inMsec = ultrasonic.convert(microsec, Ultrasonic::IN);
  //Serial.print("MS: ");
  //Serial.print(microsec);
  //Serial.print(", IN: ");
  //Serial.println(inMsec);
  
  float cmMsec1,cmMsec2, inMsec;
  long microsec = ultrasonic.timing();
  cmMsec1 = ultrasonic.convert(microsec, Ultrasonic::CM);
  Serial.print("- CM1: ");
  Serial.println(cmMsec1);
  delay(3000);
  microsec = ultrasonic.timing();
  cmMsec2 = ultrasonic.convert(microsec, Ultrasonic::CM);
  Serial.print("- CM2: ");
  Serial.println(cmMsec2);
  velocidade = ((cmMsec2-cmMsec1)/3);
  //Serial.println(velocidade);
  if (velocidade <0){
    Serial.print("Enchendo ");
    Serial.println((velocidade)*-1);  
    }else if( velocidade > 0) {
    Serial.print("esvaziando");
    Serial.println(velocidade);     
    } 
}
