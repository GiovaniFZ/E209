#define BOTAOA (1 << PD1)
#define BOTAOB (1 << PD2)
#define BOTAOC (1 << PD3)
#define MOTOR1 (1 << PB1)
#define MOTOR2 (1 << PB2)
#define MOTOR3 (1 << PB3)
// B: Saida
// D: Entradas

int main(){
  DDRB |= MOTOR1 | MOTOR2 | MOTOR3; // Direção de saida
  PORTD |= BOTAOA | BOTAOB | BOTAOC; // Pull down
  int nhp = 90;

  for(;;){
    // desligando entradas
    PORTB &= ~(MOTOR1);
  	PORTB &= ~(MOTOR2);
  	PORTB &= ~(MOTOR3);
    short int botaoa = PIND & BOTAOA;
    short int botaob = PIND & BOTAOB;
    short int botaoc = PIND & BOTAOC;
    
    if(nhp > 90){
    // desliga entradas
    PORTB &= ~(MOTOR1);
    PORTB &= ~(MOTOR2);
    PORTB &= ~(MOTOR3);
    nhp = 0;
    }else{
      if(botaoa == BOTAOA){
          PORTB |= MOTOR1;
          nhp += 30;
      }
      if(botaob == BOTAOB){
        PORTB |= MOTOR2;
        nhp += 50;
      }
        if(botaoc == BOTAOC){
          PORTB |= MOTOR3;
          nhp += 70;
      }
      
    }
  }
}
