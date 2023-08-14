// Constantes
#define MOTOR (1<<PD2)
#define SENSOR (1<<PB3)
#define LIGA (1<<PB0)
#define DESLIGA (1<<PB1)
#define ALARME (1<<PD6)

int main(){
  DDRD |= ALARME | MOTOR; // saidas
  PORTB |= DESLIGA | LIGA; // Pull-up definido no botão desliga
  DDRD &= ~ALARME; // desliga entradas
  short int sensor;
  short int liga;
  short int desliga;

  for(;;){
      liga = PINB & LIGA;
      desliga = PINB & DESLIGA;
      sensor = PINB & SENSOR;

      if(!(sensor == SENSOR)){
        if(liga == LIGA)
          PORTB |= MOTOR; // liga motor
      else if(desliga == DESLIGA)
          PORTD &= MOTOR; // desliga motor
      }else{       
          PORTD &= MOTOR; // Desliga motor
          PORTD |= ALARME; // Aciona alarme    
      }

  }
}