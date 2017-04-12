#include <VirtualWire.h>

int ledpin = 13;
char Valor_CharMsg[4];
int emissor = 4;
int botao = A0;
int valor_botao;
int estado = 0;
void setup()
{
  Serial.begin(9600);
  pinMode(ledpin,OUTPUT);
  pinMode(botao,INPUT);
  vw_set_tx_pin(emissor);
  vw_setup(2000);
  Serial.println("Transmissor modulo rf");
}
void loop()
{
  valor_botao = digitalRead(botao);
  
  if(valor_botao == 0)
  {
    estado = !estado;
    itoa(estado,Valor_CharMsg,10);
    digitalWrite(ledpin, HIGH);
    vw_send((uint8_t*)Valor_CharMsg, strlen(Valor_CharMsg));
    vw_wait_tx();
    digitalWrite(ledpin, LOW);
    Serial.println(Valor_CharMsg);
    delay(200);
  }
}
