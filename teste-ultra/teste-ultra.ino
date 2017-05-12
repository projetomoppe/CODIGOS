#include <NewPing.h>

//Define os pinos para o trigger e echo
#define TRIG 6 //define o o pino do trigger.
#define ECHO 7 //define o pino do echo.

double dist_cm;
long tempo;
 
//Inicializa o sensor nos pinos definidos acima
NewPing sonar(TRIG, ECHO);

void setup(){
  Serial.begin(9600); //inicia o serial monitor.
  Serial.println("Lendo dados do sensor...");
}
 
void loop()
{
  //Le as informacoes do sensor
  tempo = sonar.ping();
  dist_cm = sonar.convert_cm(tempo);

  //Exibe informacoes no serial monitor
  Serial.print("DISTANCIA: ");
  Serial.println(dist_cm);

  delay(200);
}
