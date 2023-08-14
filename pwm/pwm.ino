#define pwm_out (1 << PB3)
int brilho = 0;
int main(void)
{
 DDRB |= pwm_out; // configura saída para o PWM
 PORTB &= ~pwm_out; // PWM inicia desligado
 // Configura modo FAST PWM e modo do comparador A
 TCCR2A |= (1 << WGM21) | (1 << WGM20) | (1 << COM2A1);
 TCCR2B = 1; // Seleciona opção para frequência
 OCR2A = 0;

 for (;;)
 {
 OCR2A = brilho;
 brilho += 10;
 if (brilho > 254)
 brilho = 0;
 _delay_ms(100);
 }
}
