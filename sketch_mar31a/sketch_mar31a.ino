#define SMIN (1<<PD2)
#define SMAX (1<<PD3)
#define VALVULA (1<<PB0)
#define CHEIO (1<<PB1)
#define ENCHENDO (1<<PB2)


int main(){
DDRB |= VALVULA | CHEIO | ENCHENDO;
PORTD |= SMIN | SMAX;
EICRA = (0<<ISC01)+(1<<ISC00)+(0<<ISC11)+(1<<ISC10);
EIMSK = (1<<INT0) + (1<<INT1);
  sei();
  for(;;){

  }
}

ISR(INT0_vect){
  PORTB |= ENCHENDO;
  PORTB |= VALVULA;
  PORTB &= ~CHEIO;
}

ISR(INT1_vect){
  PORTB &= ~ENCHENDO;
  PORTB &= ~VALVULA;
  PORTB |= CHEIO;
}
