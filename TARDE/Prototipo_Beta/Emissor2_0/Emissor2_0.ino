#include <VirtualWire.h>

#define tx   8 // define que a pirta é constante 
#define led  7
#define s1  10
#define s2  11

int i1 =0; //define a que a variavel é igual a 0
int i2 =0;
char Valor_CharMsg[4]; // define o tamanho da mensagem 
int x =-1; //define a que a variavel é igual a -1
int a; //define a que a variavel é igual a 0
void setup() 
{
  Serial.begin(9600);   // faz com que o monitoramento se inicie 
  pinMode(led,OUTPUT); // define o pino como saida  
  pinMode(s1,INPUT); // define o pino como entrada 
  pinMode(s2,INPUT);
  vw_set_tx_pin(tx); // define a porta que nos iremos usar 
  vw_setup(2000); // define a frequencia de comunicação 
  Serial.println("Trasmissao modulo RF..."); // printa mensagem na tela 
}

void loop() 
{
  a=x; //armazena o dade e evita a repetição 
  i1 = digitalRead(s1); // dados dos sensores 
  i2 = digitalRead(s2);

  // define o valor da variavel x
  if (i1 == LOW && i2 == HIGH){
    x=1;
    }
  else if (i1 == LOW && i2 == LOW){
    x=2;
    }
  else if(i1 == HIGH && i2 == LOW) {
    x=3;
  }else if(i1 == HIGH && i2 == HIGH){
    x=0;
  }
    
  // transmite o dado do emisor 
  if(x != a) {
        itoa(x,Valor_CharMsg,10); // compacta a mensagem 
        digitalWrite(led, HIGH);
        delay(100);
        digitalWrite(led, LOW);  
        vw_send((uint8_t*)Valor_CharMsg, strlen(Valor_CharMsg));
        vw_wait_tx();
        digitalWrite(led, LOW); 
        Serial.println(Valor_CharMsg); // escreve o valor da mensagem na tela 
    }
  }
