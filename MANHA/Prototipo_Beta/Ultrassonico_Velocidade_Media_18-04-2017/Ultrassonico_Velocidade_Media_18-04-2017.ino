#include <NewPing.h>

//Define os pinos para o trigger e echo
#define TRIG 5 //define o o pino do trigger.
#define ECHO 6 //define o pino do echo.
#define TEMP_SIZE 50
#define ARRAY_SIZE 100

int intervalo = 10000, delay_time = 1, count = 0, index = 0;
double dist_cm = 0.0, referencia = 21.0, total = 0.0, nivel[ARRAY_SIZE], nivel_temp[TEMP_SIZE], velocidade = 0.0;
long tempo;
unsigned long tempo_varredura, millisAtual = 0, millisAnterior = 0;
 
//Inicializa o sensor nos pinos definidos acima
NewPing sonar(TRIG, ECHO);

void setup(){
  Serial.begin(9600); //inicia o serial monitor.
  Serial.println("Lendo dados do sensor...");

  for (int i = 0; i < TEMP_SIZE; i++){
    nivel_temp[i] = 0.0;
  }

  for (int i = 0; i < ARRAY_SIZE; i++){
    nivel[i] = 0.0;
  }
  
  //pinMode(13, OUTPUT);
}
 
void loop()
{
  millisAtual = millis();
  
  //Le as informacoes do sensor
  tempo = sonar.ping();
  dist_cm = sonar.convert_cm(tempo);

  // exclui dados de leitura fora da referencia
  if(dist_cm >= 0.0 && dist_cm <= 21.0)
  {
    total -= nivel_temp[index];
    nivel_temp[index] = referencia - dist_cm;
    total += nivel_temp[index];
    index++;

    if (index >= TEMP_SIZE)
    {
      index = 0;
      nivel[count] = total/TEMP_SIZE;

      Serial.print("nivel[");
      Serial.print(count);
      Serial.print("]: ");
      Serial.println(nivel[count]);
      
      count++;
    
      // calcula a velocidade na variacao do nivel
      if (count >= ARRAY_SIZE)
      {       
        tempo_varredura = (millisAtual - millisAnterior);
        millisAnterior = millisAtual;
        count = 0;
    
        velocidade = (nivel[ARRAY_SIZE] - nivel[0])/(tempo_varredura/1000.0);
    
        Serial.print("============ VELICIDADE: ");
        Serial.println(velocidade);
      }
    }
  }
  
  delay(delay_time);
}
