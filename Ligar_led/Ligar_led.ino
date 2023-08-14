int main(void)
{
  DDRD = DDRD | 0b00000100; // Pino PD2 definido como saída
  DDRD = DDRD | 0b10000000; // Pino PD7 definido como saida
  PORTD = PORTD | 0b00010000; // Habilitar resistor de PULL-UP no PD4

  PORTD = PORTD & ~(0b00000100); // Desliga a saída PD2
  PORTD = PORTD & ~(0b10000000); // Desliga a saída PD7
  for (;;){
    if ((PIND & 0b00010000) == 0) // Botão pressionado?
    {
      PORTD = PORTD | 0b00000100; // Aciona a saída PD2
      _delay_ms(2000); // Espera 2 segundos
      PORTD = PORTD & ~(0b00000100); // Desliga a saída PD2
      PORTD = PORTD | 0b10000000; // Aciona a saida PD7
      _delay_ms(2000); // Espera 2 segundos
      PORTD = PORTD & ~(0b10000000); // Desliga a saída PD7
    }else{
      PORTD = PORTD & ~(0b00000100); // Desliga a saída PD2
      PORTD = PORTD & ~(0b10000000); // Desliga a saída PD7
    }
  }
}