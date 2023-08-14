#define LED (1 << PD6)
#define BOT (1 << PD2)
int brilho = 0;

ISR(INT0_vect) {
  OCR0A = brilho;
  brilho += 38;
  if (brilho > 254)
    brilho = 0;
}

int main() {
  DDRD = LED;
  PORTD = BOT;

  // Configura modo FAST PWM e modo do comparador A
  TCCR0A |= (1 << WGM01) | (1 << WGM00) | (1 << COM0A1);
  TCCR0B = 1;  // Seleciona a opção para frequência
  OCR0A = 0;

  EICRA = 0b00000011;
  EIMSK = 0b00000001;
  sei();
  while (1) {
  }
}

