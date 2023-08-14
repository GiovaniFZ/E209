#include <stdio.h>
#include <stdlib.h>
#define SENSOR_GOTAS (1<<PD7)
#define MOTOR (1<<PB3)
#define ALARME (1<<PB0)
#define NUM_GOTAS 2
#define FLUXO_MAX 450 
#define FOSC 16000000U // Clock Speed
#define BAUD 9600
#define MYUBRR FOSC / 16 / BAUD - 1

char msg_tx[20];
char msg_rx[32];
int pos_msg_rx = 0;
int tamanho_msg_rx = 3;
unsigned int volume = 0, tempo_inf = 0, contador = 0, interv_tempo = 0, cont_aux = 0, erro = 0, data_aux = 0, entrar = 0;
float pot = 0,fluxo_re = 0, fluxo_def = 0, interv_tempo_aux = 0, erro_aux = 0, tensao = 0;
u16 adc_result0;

//Prototipos das funcoes UART
void UART_Init(unsigned int ubrr);
void UART_Transmit(char *dados);

int main(void)
{
  // UART
  UART_Init(MYUBRR);
  
  // Pull-up
  PORTD = SENSOR_GOTAS;
  // SAIDAS
  DDRB |= MOTOR + ALARME;

  // TIMER
  TCCR0A = 0;  // modo normal
  TCCR0B = 0; // Inicia timer desligado
  TIMSK0 |= (1 << TOIE0); // habilita interrupção no fim da contagem

  //PWM
  TCCR2A |= (1 << WGM21) | (1 << WGM20) | (1 << COM2A1);
  TCCR2B = 1; // Seleciona opção para frequência
  OCR2A = 0;
  
  // INTERRUPÇÃO SENSOR GOTAS
  PCICR = 0b00000100;
  PCMSK2 = 0b10000000;

  // INTERRUPÇÃO GLOBAL
  sei();

  // ADC
  ADC_init(); // Inicializa ADC

  UART_Transmit("Entre com o volume\n");
  while (1) {
    
    data_aux = (msg_rx[0] - 48) * 100 + (msg_rx[1] - 48) * 10 + (msg_rx[2] - 48) * 1; 
    if (data_aux > 100 && data_aux < 999 && entrar == 0) {
   
      volume = data_aux;
      data_aux = 0;
        
      msg_rx[0] = ' ';
      msg_rx[1] = ' ';
      msg_rx[2] = ' ';
      
      itoa(volume, msg_tx, 10); //
      UART_Transmit("Volume = ");
      UART_Transmit(msg_tx);
      UART_Transmit("\n");
      
      UART_Transmit("Entre com o tempo de infusao: \n");
      entrar = 1;
    }
    _delay_ms(10);
   
    if (data_aux > 100 && data_aux < 999 && entrar == 1) {
      
      tempo_inf = data_aux;
      tempo_inf = tempo_inf/60;         // Conversão para horas
      fluxo_def = volume/tempo_inf;     // Calculo do fluxo definido (real feito na interrupção)
      pot = (fluxo_def/FLUXO_MAX)*100;  // Calculo da potencia
      
      msg_rx[0] = ' ';
      msg_rx[1] = ' ';
      msg_rx[2] = ' ';
      
      itoa(tempo_inf, msg_tx, 10); //
      UART_Transmit("tempo de infusao:");
      UART_Transmit(msg_tx);
      UART_Transmit("\n");
      _delay_ms(1000);
      
      itoa(fluxo_def, msg_tx, 10); //
      UART_Transmit("fluxo definido:");
      UART_Transmit(msg_tx);
      UART_Transmit("\n");
      _delay_ms(1000);
      
      itoa(pot, msg_tx, 10); //
      UART_Transmit("potencia:");
      UART_Transmit(msg_tx);
      UART_Transmit("\n");
      _delay_ms(1000);
     
      UART_Transmit("Digite sim para ");
      UART_Transmit(" alterar parametros.\n");
      OCR2A = (int)pot;
      UART_Transmit("Calculando Erro...\n");
     
      data_aux = 0;
      entrar = 2;
    }
    
    
    if(msg_rx[0] == 's' && msg_rx[1] == 'i' && msg_rx[2] == 'm'){
       cont_aux = 0;
       entrar = 0;
       interv_tempo = 0;
       UART_Transmit("\n");
       UART_Transmit("Entre com o volume\n");
       msg_rx[0] = ' ';
     }
     
    tensao = (ADC_read(ADC0D) * 5.0) / 1023.0;
    if(tensao == 5.0){
      UART_Transmit("Bolhas detectadas!\n");
      PORTB |= ALARME;
      OCR2A = 0;
    }else{
      PORTB &=~ALARME;
    }
  }
}

// SENSOR GOTAS
ISR (PCINT2_vect) {
  TCCR0B = (1 << CS02) | (1 << CS00);  // Liga timer
  cont_aux++; // Conta quantas vezes o botão foi pressionado
  if (cont_aux >= 4) {
    TCCR0B = 0; // Desliga timer
    interv_tempo_aux = interv_tempo/3600.0;
    fluxo_re = (NUM_GOTAS/interv_tempo_aux)*0.05; // Calculo  do fluxo real
    erro_aux = ((fluxo_re - fluxo_def)/fluxo_def)*100;
    erro = (int) erro_aux;
    
    itoa(erro, msg_tx, 10); //
    UART_Transmit("Erro:");
    UART_Transmit(msg_tx);
    UART_Transmit("%");
    UART_Transmit("\n");
        
    itoa(interv_tempo, msg_tx, 10); //
    UART_Transmit("Interv_tempo:");
    UART_Transmit(msg_tx);
    UART_Transmit("\n");

    itoa(volume, msg_tx, 10); //
    UART_Transmit("Volume:");
    UART_Transmit(msg_tx);
    UART_Transmit("\n");

    itoa(tempo_inf, msg_tx, 10); //
    UART_Transmit("Tempo inf:");
    UART_Transmit(msg_tx);
    UART_Transmit("\n");
  }
}

// TIMER
ISR (TIMER0_OVF_vect) {
  if (contador > 61) {    // 1 segundo
    interv_tempo++;  // intervalo de tempo aumentado em 1 seg
    contador = 0;
  }
  contador ++;
}

// ADC
void ADC_init(void)
{
  // Configurando Vref para VCC = 5V
  ADMUX = (1 << REFS0);
  /*
    ADC ativado e preescaler de 128
    16MHz / 128 = 125kHz
    ADEN = ADC Enable, ativa o ADC
    ADPSx = ADC Prescaler Select Bits
    1 1 1 = clock / 128
  */
  ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
}
int ADC_read(u8 ch)
{
  char i;
  int ADC_temp = 0; // ADC temporário, para manipular leitura
  int ADC_read = 0; // ADC_read
  ch &= 0x07;
  // Zerar os 3 primeiros bits e manter o resto
  ADMUX = (ADMUX & 0xF8) | ch;
  // ADSC (ADC Start Conversion)
  ADCSRA |= (1 << ADSC); // Faça uma conversão
  // ADIF (ADC Interrupt Flag) é setada quando o ADC pede interrupção
  // e resetada quando o vetor de interrupção
  // é tratado.
  while (!(ADCSRA & (1 << ADIF))); // Aguarde a conversão do sinal
  for (i = 0; i < 8; i++) // Fazendo a conversão 8 vezes para maior precisão
  {
    ADCSRA |= (1 << ADSC); // Faça uma conversão
    while (!(ADCSRA & (1 << ADIF))); // Aguarde a conversão do sinal
    ADC_temp = ADCL; // lê o registro ADCL
    ADC_temp += (ADCH << 8); // lê o registro ADCH
    ADC_read += ADC_temp; // Acumula o resultado (8 amostras) para média
  }
  ADC_read = ADC_read >> 3; // média das 8 amostras ( >> 3 é o mesmo que /8)
  return ADC_read;
}

// USART
ISR(USART_RX_vect)
{
  // Escreve o valor recebido pela UART na posição pos_msg_rx do buffer msg_rx
  msg_rx[pos_msg_rx++] = UDR0;
  if (pos_msg_rx == tamanho_msg_rx)
    pos_msg_rx = 0;
}

void UART_Transmit(char *dados)
{
  // Envia todos os caracteres do buffer dados ate chegar um final de linha
  while (*dados != 0)
  {
    while (!(UCSR0A & (1 << UDRE0))); // Aguarda a transmissão acabar
    // Escreve o caractere no registro de tranmissão
    UDR0 = *dados;
    // Passa para o próximo caractere do buffer dados
    dados++;
  }
}

void UART_Init(unsigned int ubrr)
{
  // Configura a baud rate */
  UBRR0H = (unsigned char)(ubrr >> 8);
  UBRR0L = (unsigned char)ubrr;
  // Habilita a recepcao, tranmissao e interrupcao na recepcao */
  UCSR0B = (1 << RXEN0) | (1 << TXEN0) | (1 << RXCIE0);
  // Configura o formato da mensagem: 8 bits de dados e 1 bits de stop */
  UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}
