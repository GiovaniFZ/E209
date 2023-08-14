#define LED (1<<PB0)
#define BOTAO (1<<PD7)

int main(){
  DDRB = LED;
  PORTB |= LED;
}
