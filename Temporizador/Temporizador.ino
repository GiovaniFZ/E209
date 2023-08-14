// Gerar um cronometro H:M:S como print na serial

unsigned int cont = 0;
unsigned char hora = 0, minuto = 0, segundo = 0;

int main(){  
  Serial.begin(115200);
  // Configuração do temporizador
  // Modo comparador
  TCCR0A = (1 << WGM01);
  TCCR0B = (1<<CS01); // prescaler de 8
  OCR0A = 199 // Ele vai fazer 200 contagens de 500ns, o que gera interrupção a cada 100us
  TIMSK0 = (1<<OCIE0A); // Gerar uma interrupção no estouro do comparador A
  sei();
}

// o que acontece a cada 100 us
ISR(TIMER0_COMA_vect){
  cont++;
  if(cont == 10000){
    cont = 0;
    segundo++;
    if(segundo == 60){
      segundo = 0;
      minuto++;
      if(minuto == 60{
        minuto = 0;
        hora++;
        if(hora == 24){
          hora = 0;
        }
      }
    }
  }
  Serial.print(hora);
  Serial.print(":");
  Serial.print(minuto);
  Serial.print(":");
  Serial.print(segundo);
}