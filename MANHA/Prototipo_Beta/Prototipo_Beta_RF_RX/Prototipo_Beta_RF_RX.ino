#include <VirtualWire.h>

int led1 = 2;
int led2 = 3;
int led3 = 4;
int receptor = 7;
char recebido[4];
int vlrecebido;

void setup()
{
  Serial.begin(9600);
  pinMode(led1,OUTPUT);
  pinMode(led2,OUTPUT);
  pinMode(led3,OUTPUT);
  vw_set_rx_pin(receptor);
  vw_setup(2000);
  vw_rx_start();
  Serial.println("Aguardando dados: ");
}

void loop(){
  
  uint8_t buf[VW_MAX_MESSAGE_LEN];
  uint8_t buflen= VW_MAX_MESSAGE_LEN;
  
  if (vw_get_message(buf,&buflen))
  {
    int i;
    for (i=0; i< buflen; i++)
    {
      recebido[i]= char(buf[i]);
    }
    recebido[buflen]='\0';
    vlrecebido= atoi(recebido);
    //Serial.print("Recebido:  ");
 
    if (vlrecebido == 1){   
      Serial.println("Nivel critico atingido");
      digitalWrite(led1, HIGH);
      digitalWrite(led2, LOW);
      digitalWrite(led3, LOW);
    }
   
    if (vlrecebido == 0){   
      Serial.println("Nivel de monitoramento atingido");
      digitalWrite(led2, HIGH);
      digitalWrite(led1, LOW);
      digitalWrite(led3, LOW);
    }
    if (vlrecebido == 2){
      Serial.println("Nivel normal");
      digitalWrite(led3, HIGH);
      digitalWrite(led1, LOW);
      digitalWrite(led2, LOW);
    }
  }
}
  
