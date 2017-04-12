#include <VirtualWire.h>
const int led = 13;
const int botao = A1;

int valor_botao;
char valor_CharMsg[4];
int estado = 0; 

void setup()
{
Serial.begin(9600);
pinMode(led, OUTPUT);
pinMode (botao, INPUT); 
vw_set_tx_pin;
vw_setup(2000);
Serial.println("transmissao modulo RF – acione o botao … ");
}

void loop()
{
valor_botao = digitalRead (botao);

if (valor_botao == 0)
{
estado = !estado;
itoa (estado,valor_CharMsg,10);
digitalWrite(led, true);
vw_send((uint8_t *)valor_CharMsg, strlen(valor_CharMsg));
vw_wait_tx();
 digitalWrite(led, false);
 Serial.print("Valor enviado: ");
 Serial.println(valor_CharMsg);
 delay(250);
}

}



