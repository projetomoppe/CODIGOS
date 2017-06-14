#include <TinyGPS++.h>
#include <Time.h>
#include <TimeLib.h>

static const int GPSBaud = 9600;


TinyGPSPlus gps;


void setup()
{
  Serial.begin(115200);
  Serial3.begin(GPSBaud); 
 

  Serial.println("Moppe");
  Serial.println("Obtendo Dados de Localizacao");
  Serial.println();
  
}

void loop() // isUpdated();
{
 while(Serial3.available() > 0){
   if (gps.encode(Serial3.read())) 
   {     
    
    if ((gps.location.isValid() && gps.location.isUpdated()) && (gps.date.isValid() && gps.date.isUpdated()) && (gps.time.isValid() && gps.time.isUpdated()))
    {
      Serial.print("Localizacao: "); 
      Serial.print(gps.location.lat(), 6);
      Serial.print(",");
      Serial.print(gps.location.lng(), 6);
      
      Serial.print("  Data/Hora: ");
      
      Serial.print(gps.date.day());
      Serial.print("/");
      Serial.print(gps.date.month());
      Serial.print("/");
      Serial.print(gps.date.year());
      Serial.print(" ");
      setTime(gps.time.hour(),gps.time.minute(),gps.time.second(),gps.date.day(),gps.date.month(),gps.date.year());
      adjustTime(-3 * SECS_PER_HOUR);
        
      if (hour() < 10) Serial.print("0");
      Serial.print(hour());
      Serial.print(":");
      if (minute() < 10) Serial.print
      ("0");
      Serial.print(minute());
      Serial.print(":");
      if (second() < 10) Serial.print("0");
      Serial.print(second());
      
      Serial.println();
    }   
  
    if (millis() > 5000 && gps.charsProcessed() < 10)
    {
      Serial.println("GPS nao identificado.");
      while(true);
    }
   }
 }
}




