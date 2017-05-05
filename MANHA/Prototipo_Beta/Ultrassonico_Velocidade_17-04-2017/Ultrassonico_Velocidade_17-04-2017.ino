#include <NewPing.h>

//Define os pinos para o trigger e echo
#define pino_trigger 6 //define o o pino do trigger.
#define pino_echo 5 //define o pino do echo.
#define ARRAY_SIZE 100

int intervalo = 3000, delay_time = 100, i = 0, i_temp;
double referencia = 21.0; //referencia do tamanho total do recipiente ou local.
double dist_cm, vet_nivel[ARRAY_SIZE];
long tempo;
double velocidade = 0.0;
unsigned long millisAnterior = 0;
 
//Inicializa o sensor nos pinos definidos acima
NewPing sonar(pino_trigger, pino_echo);

void setup(){
  Serial.begin(9600); //inicia o serial monitor.
  Serial.println("Lendo dados do sensor...");
  pinMode(13, OUTPUT);
}
 
void loop()
{
  //Le as informacoes do sensor
  tempo = sonar.ping();
  dist_cm = sonar.convert_cm(tempo);
  vet_nivel[i] = referencia - dist_cm;

  //Exibe informacoes no serial monitor
  Serial.print("Nivel: ");
  Serial.println(vet_nivel[i]);

  // calculo velocidade
  unsigned long millisAtual = millis();
  
  if ((unsigned long)(millisAtual - millisAnterior) >= intervalo)
  {
    digitalWrite(13, !digitalRead(13));
    i_temp = i;
    i = -1;
    millisAnterior = millisAtual;

    Serial.print("D2: ");
    Serial.println(vet_nivel[i_temp]);
  
    Serial.print("D1: ");
    Serial.println(vet_nivel[i+1]);

    velocidade = ((vet_nivel[i_temp] - vet_nivel[i+1])/(intervalo/1000.0)); // cm/s
    
    Serial.print("VELICIDADE: ");
    Serial.println(velocidade);
  }
  
  i++;

  delay(delay_time);
}
