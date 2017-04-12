//Programa : Comunicacao com Modulo RF 433 - Receptor
//Autor : Arduino e Cia

#include <VirtualWire.h>

//Define pino led
int ledPin = 5;

int valor_recebido_RF;
char recebido_RF_char[4]; 

void setup() 
{
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  //Pino ligado ao pino DATA do receptor RF
  vw_set_rx_pin(7);
  //Velocidade de comunicacao (bits por segundo)
  vw_setup(500); 
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
        //Armazena os caracteres recebidos  
          recebido_RF_char[i] = char(buf[i]);
      
       recebido_RF_char[buflen] = '\0';
       
       //Converte o valor recebido para integer
       valor_recebido_RF = (atoi(recebido_RF_char));
         
       //Mostra no serial monitor o valor recebido
       Serial.print("Recebido: ");
       Serial.println(valor_recebido_RF);
       valor_recebido_RF = valor_recebido_RF * 28.33;
       Serial.print("Valor jogado ao Led: ");
       Serial.println(valor_recebido_RF);
       //Altera o estado do led conforme o numero recebido
       analogWrite(ledPin, valor_recebido_RF);
    }
}
