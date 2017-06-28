// Programa: Gravacao com modulo cartao SD
// Autor: FILIPEFLOP
 
#include <SdFat.h>
int trig = 6;
int echo = 5;
int s1 = 7;
int s2 = 8;
int a1 = 0;
int a2 = 0;
SdFat sdCard;
SdFile meuArquivo;
 
// Pino ligado ao CS do modulo
const int chipSelect = 4;
int bot = 10;
int valor = 0 ;
 
void setup()
{
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  Serial.begin(9600);
  pinMode(s1 , INPUT);
  pinMode(s2 , INPUT);
  pinMode(bot, INPUT);

  sdCard.begin(chipSelect,SPI_HALF_SPEED);

  meuArquivo.open("leitura_ultrasonico.txt", O_RDWR | O_CREAT | O_AT_END);
}
 
void loop()
{
  a1 = digitalRead (s1);
  a2 = digitalRead (s2);
  valor = digitalRead (bot);

  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);

  digitalWrite(trig, LOW);
  
  unsigned long duracao = pulseIn(echo, HIGH);

  int distancia = duracao / 58;

  Serial.print("Distancia: ");
  Serial.println(distancia);
  delay(1000);
  // Grava dados do potenciometro em LER_POT.TXT
  meuArquivo.print("distancia: ");
  meuArquivo.println(distancia);
  meuArquivo.print("sensor 1");
  meuArquivo.println(a1);
  meuArquivo.print("sensor 2");
  meuArquivo.println(a2); 
  if (valor == HIGH)
  {
    // Interrompe o processo e fecha o arquivo
    Serial.println("Processo de gravacao interrompido. Retire o SD!");
    meuArquivo.close();
    while (1){}
  }
  delay(100);
}

