#include <Ultrasonic.h>

// Programa: Gravacao com modulo cartao SD
// Autor: FILIPEFLOP
 
#include <SdFat.h>
 
SdFat sdCard;
SdFile meuArquivo;

// Pino ligado ao CS do modulo
const int echoPin = 4;
const int trigPin = 5;
const int chipSelect = 6;
const int potPin = A5;
const int botaoPin = 7;
const int s1Pin = 3;
const int s2Pin = 2;

int estadoS1 = 0;
int estadoS2 = 0;
int valorBot = 0;
float distancia = 0.0;
long microsec = 0;

Ultrasonic ultrasonic(trigPin, echoPin);

void setup()
{
  Serial.begin(9600);
  // Define o pino do potenciometro como entrada
  pinMode(potPin, INPUT);
  pinMode(botaoPin, INPUT);  
  pinMode(s1Pin, INPUT);
  pinMode(s2Pin, INPUT);

  // Inicializa o modulo SD
  if(!sdCard.begin(chipSelect,SPI_HALF_SPEED))sdCard.initErrorHalt();
  // Abre o arquivo LER_POT.TXT
  if (!meuArquivo.open("dados.txt", O_RDWR | O_CREAT | O_AT_END))
  {
    sdCard.errorHalt("Erro na abertura do arquivo LER_POT.TXT!");
  }
}
 
void loop()
{
  microsec = ultrasonic.timing();
  distancia = ultrasonic.convert(microsec, Ultrasonic::CM);

  estadoS1 = digitalRead(s1Pin);
  estadoS2 = digitalRead(s2Pin);  

  Serial.print("Leitura ultra: ");
  Serial.println(distancia);
  Serial.print("Leitura s1: ");
  Serial.println(estadoS1);
  Serial.print("Leitura s2: ");
  Serial.println(estadoS2);
 
  // Grava dados do potenciometro em LER_POT.TXT
  meuArquivo.print("Leitura ultra: ");
  meuArquivo.println(distancia);
  meuArquivo.print("Leitura s1: ");
  meuArquivo.println(estadoS1);
  meuArquivo.print("Leitura s2: ");
  meuArquivo.println(estadoS2);

  valorBot = digitalRead(botaoPin); 
  if (valorBot == 1)
  {
    // Interrompe o processo e fecha o arquivo
    Serial.println("Processo de gravacao interrompido. Retire o SD!");
    meuArquivo.close();
    while (1) {}
  }
  delay(1000);
}

