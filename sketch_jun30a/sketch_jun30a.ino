#define LED (1<< PB3)
int main(){
  DDRB = LED;
  for(;;){
    _delay_ms(1000);
    PORTB |= LED;
    _delay_ms(1000);
    PORTB &= ~LED;
    _delay_ms(1000);
    }
}
