#include <Ultrasonic.h>

#define TRIGGER_PIN  4
#define ECHO_PIN     5
double velocidade = 0;
Ultrasonic ultrasonic(TRIGGER_PIN, ECHO_PIN);
int s1= 11;
int s2= 10;
int x =0;
int i1 =0;
int i2 =0;
void setup() {
Serial.begin(9600);
pinMode(s1, INPUT);
pinMode(s2, INPUT);
}

void loop() {
  i1 =digitalRead (s1);
  i2 =digitalRead (s2);
  float cmMsec1,cmMsec2, inMsec;
  long microsec = ultrasonic.timing();
  cmMsec1 = ultrasonic.convert(microsec, Ultrasonic::CM);
  Serial.print("- CM1: ");
  Serial.println(cmMsec1);
  Serial.println(i1);
  Serial.println(i2);
  delay(3000);
  microsec = ultrasonic.timing();
  cmMsec2 = ultrasonic.convert(microsec, Ultrasonic::CM);
  Serial.print("- CM2: ");
  Serial.println(cmMsec2);
  Serial.println(i1);
  Serial.println(i2);
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
