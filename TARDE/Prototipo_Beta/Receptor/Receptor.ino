#include <VirtualWire.h>

//Programa : Comunicacao com Modulo RF 433 - Receptor
//Autor : Arduino e Cia

//Define pino led
int led1 = 5;
int led2 = 4;
int led3 = 3;
int led4 = 2;
int led_aviso=8;
int valor_recebido_RF;
char recebido_RF_char[4]; 

void setup() 
{ 
  Serial.begin(9600);
  pinMode(led1, OUTPUT);
  pinMode(led2,  OUTPUT);
  pinMode(led3, OUTPUT);
  //Pino ligado ao pino DATA do receptor RF
  vw_set_rx_pin(7);
  //Velocidade de comunicacao (bits por segundo)
  vw_setup(2000); 
  //Inicia a recepcao  
  vw_rx_start();
  Serial.println("Recepcao modulo RF - Aguardando...");
}

void loop()
{
    uint8_t buf[VW_MAX_MESSAGE_LEN];
    uint8_t buflen = VW_MAX_MESSAGE_LEN;
    
    if (vw_get_message(buf, &buflen)) 
    {
       int i;
       for (i = 0; i < buflen; i++)
       {            
          //Armazena os caracteres recebidos  
          recebido_RF_char[i] = char(buf[i]);
       }
       recebido_RF_char[buflen] = '\0';
       
       //Converte o valor recebido para integer
       valor_recebido_RF = atoi(recebido_RF_char);
         
       //Mostra no serial monitor o valor recebido
       Serial.print("Recebido: ");
       Serial.println(valor_recebido_RF);

       
       digitalWrite(led_aviso, HIGH);
       delay(100);
       digitalWrite(led_aviso, LOW);
       //Altera o estado do led conforme o numero recebido
    }
    
    if (valor_recebido_RF == 0)
    {
       digitalWrite(led1, LOW);
       digitalWrite(led2, LOW);
       digitalWrite(led3, LOW);
       digitalWrite(led4, HIGH);
    }
    if (valor_recebido_RF == 1)
    {
       digitalWrite(led1, HIGH);
       digitalWrite(led2, LOW);
       digitalWrite(led3, LOW);
       digitalWrite(led4, LOW);
    }
    if (valor_recebido_RF == 2)
    {
       digitalWrite(led1, LOW);
       digitalWrite(led2, HIGH);
       digitalWrite(led3, LOW);
       digitalWrite(led4, LOW);
    }
    if (valor_recebido_RF == 3)
    {
       digitalWrite(led1, LOW);
       digitalWrite(led2, LOW);
       digitalWrite(led3, HIGH);
       digitalWrite(led4, LOW);
    }
}
