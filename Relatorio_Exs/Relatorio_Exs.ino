// letra A
#define BUZZER (1<<PB4)
#define BOTAO (1<<PB2)

int main(){
  DDRB = BUZZER;
  PORTB = BOTAO;
  PORTB &= ~BUZZER;
  PCICR = (1<<PCIE0);
  PCMSK0 = BOTAO;
  sei();
  
  for(;;){
    
  }
  
}
ISR(PCINT0_vect){
	PORTB |= BUZZER;
}

// letra B
#define BUZZER (1<<PB4)
#define BOTAO (1<<PC4)

int main(){
  DDRB = BUZZER;
  PORTC = BOTAO;
  PORTB &= ~BUZZER;
  PCICR = (1<<PCIE1);
  PCMSK1 = BOTAO;
  sei();
  
  for(;;){
    
  }
  
}
ISR(PCINT1_vect){
	PORTB |= BUZZER;
}

// letra C
#define BUZZER (1<<PB4)
#define BOTAO (1<<PD6)

int main(){
  DDRB = BUZZER;
  PORTD = BOTAO;
  PORTB &= ~BUZZER;
  PCICR = (1<<PCIE2);
  PCMSK2 = BOTAO;
  sei();
  
  for(;;){
    
  }
  
}
ISR(PCINT2_vect){
	PORTB |= BUZZER;
}