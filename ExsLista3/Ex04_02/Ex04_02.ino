#define MOTOR (1 << PD6)
#define LIGA (1 << PB1)
#define DESLIGA (1 << PB2)
unsigned int cont = 0;
float DC = 0;

ISR(TIMER2_COMPA_vect) {
  cont++;
  if(cont%10000 == 0){ // A cada 1 seg
    DC += 31.87; // adiciona 12,5%
    if(DC < 255)
      OCR0A = int(DC); // PWM
    else
      OCR0A = 255; // Mantém ligado
    Serial.println(OCR0A);
    Serial.println(DC);
  }
}

ISR(PCINT0_vect) {
  // Se liga for pressionado
  if (!(PINB & LIGA)){
    TCCR2B = (1<<CS01); // Ativa o temporizador
    
  }
  if (!(PINB & DESLIGA)){
    cont = 0;
    TCCR2B = 0;
    DC = 0;
    OCR0A = 0;
    Serial.println(OCR0A);
    Serial.println(DC);
  }
}

int main() {
  Serial.begin(115200);
  // Entradas e saidas
  DDRD = MOTOR;
  PORTB = (LIGA + DESLIGA);

  // Configuração do timer
  TCCR2A = (1<<WGM21); //Comparador
  TCCR2B = 0; //Pre-scaler de 8
  OCR2A = 199; //200 contagens de 500 ns
  TIMSK2 = (1<<OCIE2A); //Gerar uma interrupção no estouro do comparador A

  // Interrupção do portal B
  PCICR = (1 << PCIE0);
  PCMSK0 = (LIGA + DESLIGA);

  // Configuração do motor
  TCCR0A = (1<<COM0A1) + (0<<COM0A0) + (1<<WGM01) + (1<<WGM00);
  TCCR0B = (1<<CS02) + (1<<CS00);
  OCR0A = 0;
  sei();

  for (;;) {
  }
}
