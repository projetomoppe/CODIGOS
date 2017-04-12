#include <VirtualWire.h>

#define ESTADO_1       13
#define ESTADO_2       12
#define SENSOR_1       11
#define SENSOR_2       10
#define NOTIFICACAO_TX 7
#define EMISSOR        8

int estado1;
int estado2;
char valor_msg[4];
int dado = 2;
int dado_temp;

void setup() {
  
Serial.begin(9600);
vw_set_tx_pin(EMISSOR);
vw_setup(2000);

pinMode (ESTADO_1, OUTPUT);
pinMode (ESTADO_2, OUTPUT);
pinMode (NOTIFICACAO_TX, OUTPUT);
pinMode (SENSOR_1, INPUT);
pinMode (SENSOR_2, INPUT);

digitalWrite(ESTADO_1, LOW);
digitalWrite(ESTADO_2, LOW);
}


void loop() {
  
  dado_temp = dado;
  
  estado1 = digitalRead(SENSOR_1);
  estado2 = digitalRead(SENSOR_2);
  
  if(estado1 == LOW && estado2==LOW)
  {
    digitalWrite(ESTADO_1, HIGH);
    digitalWrite(ESTADO_2, LOW);
    dado = 0;
    
  }
   else if(estado1 == LOW && estado2== HIGH)
  {
    digitalWrite(ESTADO_1, LOW);
    digitalWrite(ESTADO_2,HIGH);
    dado = 1;
  }
  else 
  {
    digitalWrite(ESTADO_1, LOW);
    digitalWrite(ESTADO_2, LOW);
    dado = 2;
  }
  
  if(dado != dado_temp)
  {
    itoa(dado,valor_msg,10);
    digitalWrite(NOTIFICACAO_TX,HIGH);
    vw_send((uint8_t*)valor_msg, strlen(valor_msg));
    vw_wait_tx();
    
    digitalWrite(NOTIFICACAO_TX, LOW);
    Serial.println(valor_msg);
  }
  
  delay(250);
}
