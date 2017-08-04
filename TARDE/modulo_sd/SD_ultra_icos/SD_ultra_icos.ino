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
const int botaoPin = 7;
int valorPot = 0;
int valorBot = 0;
float distancia = 0.0;
long microsec = 0;

Ultrasonic ultrasonic(trigPin, echoPin);

void setup()
{
  Serial.begin(9600);
  // Define o pino do potenciometro como entrada
  pinMode(A5, INPUT);
  pinMode(7, INPUT);  


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
  
  // Leitura da porta A5/Potenciometro
  //valorPot = analogRead(A5);
  valorBot = digitalRead(botaoPin);
  Serial.print("Leitura ultra: ");
  Serial.println(distancia);
 
  // Grava dados do potenciometro em LER_POT.TXT
  meuArquivo.print("Leitura ultra: ");
  meuArquivo.println(distancia);
 
  if (valorBot == 1)
  {
    // Interrompe o processo e fecha o arquivo
    Serial.println("Processo de gravacao interrompido. Retire o SD!");
    meuArquivo.close();
    while (1) {}
  }
  delay(2000);
}

