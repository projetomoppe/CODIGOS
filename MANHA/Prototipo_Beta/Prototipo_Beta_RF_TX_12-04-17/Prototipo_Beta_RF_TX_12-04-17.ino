// inclui biblioteca para RF
#include <VirtualWire.h>

// define pinos dos sensores e do emissor
#define S1    11
#define S2    10
#define LEDTX 7
#define TX    8

// define variaveis de trabalho
int s0;
int s1;
char msg[4];
int dado = -1;
int dado_temp;

void setup() {
                                    
  // debug
  Serial.begin(9600);

  // inicia emissor
  vw_set_tx_pin(TX);
  vw_setup(2000);
  
  pinMode(LEDTX, OUTPUT);
  pinMode(S1, INPUT);
  pinMode(S2, INPUT);
}

void loop() {

  // armazena o dado anterior
  // evita o emissor mandar dados repetitivamente a cada loop
  dado_temp = dado;

  // obtem dados do sensor
  s0 = digitalRead(S1);
  s1 = digitalRead(S2);

  // condicoes de acordo com a instalacao dos sensores
  if(s0 == LOW && s1 == LOW)
    dado = 1;
  else if(s0 == LOW && s1 == HIGH)
    dado = 2;
  else
    dado = 0;

  // envia dado ao receptor quando há alteração de estado
  if(dado != dado_temp)
  {
    itoa(dado, msg, 10);
    digitalWrite(LEDTX, HIGH);
    vw_send((uint8_t*)msg, strlen(msg));
    vw_wait_tx();
    digitalWrite(LEDTX, LOW);
    
    // debug
    Serial.println(msg);
  }
}
