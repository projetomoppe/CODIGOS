#include <LiquidCrystal.h> //Biblioteca utilizada para fazer o controle do LCD
#include <Ultrasonic.h> //Biblioteca utilizada para realizar as funções do sensor Ultrasonico

#define PINO_TRG 30 //Define os pinos do Arduino ligados ao Trigger
#define PINO_ECHO 32 //Define os pinos do Arduino ligados ao Echo

Ultrasonic ultrasonic(PINO_TRG, PINO_ECHO); //Inicializa o sesnsor Ultrasonico nos pinos especificados

LiquidCrystal lcd(7, 6, 5, 4, 3, 2); //Configura os pinos do Arduino para se comunicar com o LCD 
//int trig = 30;
//int echo = 32;

int azul = 24; //Pino 24 sera saida do LED Azul
int amarelo = 23; //Pino 23 sera saida do LED Amarelo
int vermelho = 22; //Pino 22 sera saida do LED Vermelho

int buzz = 12; //Pino 12 sera saida da buzina

void setup() {
// pinMode(trig, OUTPUT);
// pinMode(echo, INPUT);

  pinMode(azul, OUTPUT); //Pino representando LED Azul
  pinMode(amarelo, OUTPUT); //Pino representando LED Amarelo
  pinMode(vermelho, OUTPUT); //Pino representando LED Vermelho

  pinMode(buzz, OUTPUT); //Pino representando a buzina

  Serial.begin(9600); //Iniciamos a porta serial com Baud Rate de 9600B
  lcd.begin(16, 2);//Inicia o LCD com dimensoes 16X2(Colunas X Linhas)
}

void loop() {
//  digitalWrite(trig, LOW);
//  delayMicroseconds(2);
  
//  digitalWrite(trig, HIGH);
//  delayMicroseconds(10);

//  digitalWrite(trig, LOW);
  
//  float duracao = pulseIn(echo, HIGH);

//  float distancia = duracao / 58.00;
//  float capacidade = 100 - distancia * 6.085;

float distancia; //Declarando a variavel distancia
long microsec = ultrasonic.timing(); //Le os valores do sensor Ultrasonico
distancia = ultrasonic.convert(microsec, Ultrasonic::CM); //Atribui os valores em Cm

int nivel = 100 - distancia * 6.2; //Calcula a capacidade em porcentagem

  //Usamos o IF, um estrutara de condiçao, para verificar as distancias
  
  if(distancia > 11){ //Se for maior que 11... 
    digitalWrite(azul, HIGH); //O LED azul acende
    digitalWrite(amarelo, LOW); //O LED amarelo permanece apagado
    digitalWrite(vermelho, LOW); //O LED vermelho permanece apagado
  }

  if((distancia <= 11) && (distancia > 6)){ //Se for menor igual a 11 e maior que 6...
    digitalWrite(azul, HIGH); //O LED azul permanece aceso
    digitalWrite(amarelo, HIGH); //O LED amarelo acende
    digitalWrite(vermelho, LOW); //O LED vermelho permanece apagado
  }
  if(distancia <= 6){ //Se for menoor igual a 6
    digitalWrite(azul, HIGH); //O LED azul permanece aceso
    digitalWrite(amarelo, HIGH); //O LED amarelo permanece aceso
    digitalWrite(vermelho, HIGH); //O LED vermelho acente

    digitalWrite(buzz, HIGH); //A buzina apita
    delay(500); //Aguarda 5 segundos
    digitalWrite(buzz, LOW); //A buzina desliga
    delay(500); //Aguarda 5 segundos
  }
  
  lcd.clear();
  
  lcd.setCursor(0, 0); //Posiciona o cursor na coluna zero(0) e na linha zero(0)
  lcd.print("Dist:"); //Printa a palavra Dist
  lcd.setCursor(6, 0); //Posiciona o cursor na coluna seis(6) e na linha zero(0)
  lcd.print(distancia); //Printa o valor da variavel distancia
  lcd.setCursor(11, 0); //Posiciona o cursor na coluna dez(10) e na linha zero(0)
  lcd.print("cm"); //Printa a palavra cm
    
  lcd.setCursor(0,1); //Posiciona o cursor na coluna zero(0) e na linha um(1)
  lcd.print("Nivel:"); //Printa a palavra Quant
  lcd.setCursor(7,1); //Posiciona o cursor na coluna sete(7) e na linha um(1)
  lcd.print(nivel); //Print o valor da variavel capacidade
  lcd.setCursor(10,1); //Posiciona o cursor na coluna onze(11) e na linha um(1)
  lcd.print("%"); //Printa sinal numerico
  delay(100); //Aguarda 1 segundo
}
