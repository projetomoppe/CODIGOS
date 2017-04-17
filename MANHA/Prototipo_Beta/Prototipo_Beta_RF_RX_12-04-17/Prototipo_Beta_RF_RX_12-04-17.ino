// biblioteca para comunicacao RF
#include <VirtualWire.h>

// define pinos
#define N0    5
#define N1    4
#define N2    3
#define LEDRX 8
#define RX    7

// variaveis de manipulacao
char msg[4];
int estado;

void setup()
{
  // debug
  Serial.begin(9600);
  
  pinMode(N0, OUTPUT);
  pinMode(N1, OUTPUT);
  pinMode(N2, OUTPUT);
  pinMode(LEDRX, OUTPUT);

  // inicia comunicacao wireless
  vw_set_rx_pin(RX);
  vw_setup(2000);
  vw_rx_start();

  // debug
  Serial.println("Aguardando dados: ");
}

void loop(){

  // armazena mensagem recebida
  if(vw_have_message()){
    uint8_t buf[VW_MAX_MESSAGE_LEN];
    uint8_t buflen= VW_MAX_MESSAGE_LEN;

    // se tem mensagem, pega mensagem
    if (vw_get_message(buf, &buflen))
    {
      // acende notificacao de mensagem recebida
      digitalWrite(LEDRX, HIGH);
      
      // atribui mensagem para variavel de manipulacao
      int i;
      for (i = 0; i < buflen; i++)
      {
        msg[i] = char(buf[i]);
      }
      msg[buflen] = '\0';
      estado = atoi(msg);
   
      if (estado == 0){   
        // debug
        Serial.println("Nivel normalizado!");
        
        digitalWrite(N0, HIGH);
        digitalWrite(N1, LOW);
        digitalWrite(N2, LOW);
      }
      else if (estado == 1){   
        Serial.println("Nivel de alerta atingido!");
        digitalWrite(N0, LOW);
        digitalWrite(N1, HIGH);
        digitalWrite(N2, LOW);
      }
      if (estado == 2){
        Serial.println("Nivel critico atingido!");
        digitalWrite(N0, LOW);
        digitalWrite(N1, LOW);
        digitalWrite(N2, HIGH);
      }
  
      // apaga notificacao de mensagem recebida
      digitalWrite(LEDRX, LOW);
    }
  } // end vw_have_message()
}
