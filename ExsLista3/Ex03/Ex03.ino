#define MOTOR (1<< PD1)
#define BOTAOLIGA (1<<PB1)
#define BOTAODESLIGA (1<<PB2)
unsigned int cont = 0;
unsigned int contaux = 0;

// a cada 100us
ISR(TIMER0_COMPA_vect){
  cont++;
  if(cont == 10000) // A cada 1 segundo
     contaux++;
  if(contaux == 10){
    PORTD |= MOTOR;
  }
}


ISR(PCINT0_vect){
  if(PINB & BOTAOLIGA){
    TCCR0B = (1<<CS01); // prescaler de 8, ativa temporizador
  }
  if(PINB & BOTAODESLIGA){
    TCCR0B = 0;
    cont = 0;
    contaux = 0;
    PORTD &= ~MOTOR;
  }
}


int main(){
  DDRD = MOTOR; // define motor como saida
  PORTD &= ~MOTOR; // inicia com o motor desligado
  // Configuração da interrupção
  PCICR = (1<<PCIE0); // Habilita no portal B
  PCMSK0 = (1<<PCINT1) + (1<<PCINT2); // Botões 1 e 2 do portal B
  // Configuração do timer
  TCCR0A = (1<<WGM01); // Modo de comparador
  TCCR0B = 0; // Desativa o timer (será ativado ao pressionar o botão)
  OCR0A = 199; // 200 contagens de 500ns
  TIMSK0 = (1<<OCIE0A); //Gerar uma interrupção no estouro do comparador A
  sei();

  for(;;){
    
  }
  
}
