#define pwm_out (1 << PB3)
int brilho = 0;
int main(void)
{
 DDRD |= pwm_out; // configura saída para o PWM
 PORTD &= ~pwm_out; // PWM inicia desligado
 // Configura modo FAST PWM e modo do comparador A
 TCCR2A = (1<<COM2B1) | (1<<WGM21) | (1<<WGM20);
 TCCR2B = (1<<CS22) | (1<<CS20); // Seleciona opção para frequência
 OCR2B = 60;
  
 for (;;)
 {
 OCR2B = brilho;
 brilho += 10;
 if (brilho > 254)
 brilho = 0;
 _delay_ms(100);
 }
}