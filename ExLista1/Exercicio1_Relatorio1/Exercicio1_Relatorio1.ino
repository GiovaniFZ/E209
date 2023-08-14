// Constantes
#define BOMBA (1<<PB0) // Bomba está em PB0
#define LIGA (1<<PC0)
#define DESLIGA (1<<PC1)
#define CHAVE (1<<PD3)
#define BAIXO (1<<PD4)
#define ALTO (1<<PB5)

int main(){
// Configurar a direção dos pinos
DDRB = BOMBA; // Bomba declarada como saída (por padrão, todos os pinos são de entrada)
// Configurar os resistores de pull-up - Habilita apenas para entrada, nem toda a entrada precisa de pull-up - botões precisam
// Botão NA = ele apertado vai pra vcc
// Botão NF = vai para GND 
PORTC = DESLIGA; // PC1 com resistor de pull-up habilitado (PC1)
PORTB &= ~BOMBA; // Desligar as saidas que precisam começar desligadas

for(;;){
  // Leitura da porta
  short int chave;
  chave = PIND & CHAVE; // A chave serve para zerar as posições que não interessam para a leitura da chave.
  // PD5 e PD4 variam de 0 e 1 por conta dos sensores.
  if(chave == CHAVE){ // Verificar se a chave está no modo manual 
  short int desliga; // Botão desliga
  desliga = PINC & DESLIGA;
    if(!(desliga == DESLIGA)) // Quando aperta o botão desliga, ele vai pra 0, por isso usou-se exclamação.
      PORTB &= ~BOMBA; // Desliga bomba
      // Leitura botão liga
    short int liga;
    liga = PINC & LIGA;
    if(liga == LIGA)
      PORTB |= BOMBA; // Liga a bomba         
  }
  else{ // Chave no modo automatico
    short int baixo, alto; // Sensores
    baixo = PIND & BAIXO;
    alto = PIND & ALTO;
    if((baixo == BAIXO) && (alto == ALTO)) // Ambos ativados
      PORTB = 0b00000000;
    else if((!baixo == 0) && ((!(alto == 0)))
      PORTB |= BOMBA; // Liga a bomba
}

}
}
