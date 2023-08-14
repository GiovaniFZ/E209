#define led 8
 int valor_lido;
 
 void setup() {
  Serial.begin(9600);
  pinMode (led, OUTPUT);
}

void loop() {
  if (Serial.available()>0) {
    valor_lido=Serial.read();
    if (valor_lido=='1'){
      digitalWrite(led, HIGH);
      Serial.print("Ligado\n");
    } else if (valor_lido=='0'){
      digitalWrite(led, LOW);
      Serial.print("Desligado\n");
    }
  }
}
