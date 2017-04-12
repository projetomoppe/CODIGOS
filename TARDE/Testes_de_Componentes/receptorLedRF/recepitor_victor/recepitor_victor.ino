#include <VirtualWire.h>
int led =5;
int valor_recebido_RF;
char recebido_RF_char[4];
void setup() {
  Serial.begin(9600);
  pinMode(led, OUTPUT);
  vw_set_rx_pin(7);
  vw_setup(1000); 
  vw_rx_start();
  Serial.println("Recepcao modulo RF - Aguardando...");
}

void loop() {
    uint8_t buf[VW_MAX_MESSAGE_LEN];
    uint8_t buflen = VW_MAX_MESSAGE_LEN;
    
    if (vw_get_message(buf, &buflen)) 
    {
    int i;
        for (i = 0; i < buflen; i++)
       {              
          recebido_RF_char[i] = char(buf[i]);
       }
       recebido_RF_char[buflen] = '\0';
       valor_recebido_RF = atoi(recebido_RF_char);
       Serial.print("Recebido: ");
       Serial.print(valor_recebido_RF);
       
       if (valor_recebido_RF == 1)
       {
         digitalWrite(led, HIGH);
         Serial.println(" - Led aceso !");
       }
       if (valor_recebido_RF == 0)
       {
         digitalWrite(led, LOW);
         Serial.println(" - Led apagado !");
       }
    }
  }
