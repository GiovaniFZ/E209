int main (void){
  DDRD = 0x03;
  while(1){
    PORTD = 0x01;
    _delay_ms(1000);
    PORTD = 0x02;
    _delay_ms(1000);
    PORTD = 0x03;
    _delay_ms(1000);
    PORTD = 0x00;
    _delay_ms(1000);    
  }
}
