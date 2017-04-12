//Programa : Comunicacao com Modulo RF 433 - Emissor
//Autor : Arduino e Cia

#include <VirtualWire.h>

//Define pinos Led e Botao
const int led = 7;
const int s1 = 10;
const int s2 = 11;
int i1 =0;
int i2 =0;
char Valor_CharMsg[4]; 
int x;

void setup() 
{
  Serial.begin(9600);   
  pinMode(led,OUTPUT);
  pinMode(s1,INPUT);
  pinMode(s2,INPUT);
  vw_set_tx_pin(8);
  vw_setup(2000);
  Serial.println("Trasmissao modulo RF...");
}

void loop() 
{
  i1 = digitalRead(s1);
  i2 = digitalRead(s2);

  if (!(i1 == 0 && i2 == 1) && !(i1 == 0 && i2 == 0) && !(i1 == 1 && i2 == 0))
  {
    x=0;
    itoa(x,Valor_CharMsg,10);
    vw_send((uint8_t *)Valor_CharMsg, strlen(Valor_CharMsg));
    vw_wait_tx();
    
    digitalWrite(led, HIGH);
    delay(100);
    digitalWrite(led, LOW);
        
    Serial.print("s1 - ");
    Serial.println(i1);
    Serial.print("s2 - ");
    Serial.println(i2);
    Serial.println("Valor enviado: 0");
  }
  
  if (i1 == 0 && i2 == 1)
  {
    x=1;
    itoa(x,Valor_CharMsg,10);
    vw_send((uint8_t *)Valor_CharMsg, strlen(Valor_CharMsg));
    vw_wait_tx();
    
    digitalWrite(led, HIGH);
    delay(100);
    digitalWrite(led, LOW);
        
    Serial.print("s1 - ");
    Serial.println(i1);
    Serial.print("s2 - ");
    Serial.println(i2);
    Serial.println("Valor enviado: 1");
  }
  
  if (i1 == 0 && i2 == 0)
  {
    x=2;
    itoa(x,Valor_CharMsg,10);
    vw_send((uint8_t *)Valor_CharMsg, strlen(Valor_CharMsg));
    vw_wait_tx();
    
    digitalWrite(led, HIGH);
    delay(100);
    digitalWrite(led, LOW);

    Serial.print("s1 - ");
    Serial.println(i1);
    Serial.print("s2 - ");
    Serial.println(i2);
    Serial.println("Valor enviado: 2");
  }

  if (i1 == 1 && i2 == 0)
  {
    x=3;
    itoa(x,Valor_CharMsg,10);
    vw_send((uint8_t *)Valor_CharMsg, strlen(Valor_CharMsg));
    vw_wait_tx();
    
    digitalWrite(led, HIGH);
    delay(100);
    digitalWrite(led, LOW);
        
    Serial.print("s1 - ");
    Serial.println(i1);
    Serial.print("s2 - ");
    Serial.println(i2);
    Serial.println("Valor enviado: 3");
  }
  delay(100);
}
