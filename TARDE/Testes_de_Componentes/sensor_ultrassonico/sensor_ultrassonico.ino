int trig = 7;
int echo = 6;

int azul = 10;
int amarelo = 9;
int vermelho = 8;

void setup() {
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);

  pinMode(azul, OUTPUT);
  pinMode(amarelo, OUTPUT);
  pinMode(vermelho, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);

  digitalWrite(trig, LOW);
  
  unsigned long duracao = pulseIn(echo, HIGH);

  int distancia = duracao / 58;

  Serial.print("Distancia: ");
  Serial.println(distancia);
  delay(1000);
}
