#include <IRremote.h>

IRrecv IR(12);

#define red_pin1 11
#define yellow_pin1 10
#define green_pin1 9
#define red_pin2 4
#define yellow_pin2 3
#define green_pin2 2
#define init_button 5
#define blink_button 6
#define buzzer 8

// Definição das variáveis de tratamento de tempo:

unsigned long time, currentTime, initialTime;
unsigned long time2, currentTime2, initialTime2;
unsigned long previousTime = 0;

// Definição do array pins, que contém todos os pinos referentes aos leds utilizados:

int pins[] = {11, 10, 9, 4, 3, 2};

// Inicialização das variáveis booleanas:

bool ledState = 1;
bool init_button_state = 0;
bool blink_button_state = 0;


void setup()
{
  initialTime = millis();
  initialTime2 = millis();
  
  // Definição dos pinos de saída:
  
  IR.enableIRIn();
  Serial.begin(9600);

  pinMode(init_button, INPUT);
  pinMode(blink_button, INPUT);
  pinMode(red_pin1, OUTPUT);
  pinMode(yellow_pin1, OUTPUT);
  pinMode(green_pin1, OUTPUT);
  pinMode(red_pin2, OUTPUT);
  pinMode(yellow_pin2, OUTPUT);
  pinMode(green_pin2, OUTPUT);
  pinMode(buzzer, OUTPUT);
}

// Função para desligar todos os leds:

void turn_off_leds()
{
  for (int i = 0; i < 6; i++) {
    digitalWrite(pins[i], LOW);
  }
}

// Função para piscar as luzes amarelas de cada semafóro em 1hz:

void blink_yellow()
{
  if (millis() - previousTime >= 500){
    previousTime = millis();
    digitalWrite(yellow_pin1, ledState);
    digitalWrite(yellow_pin2, ledState);
    digitalWrite(buzzer, ledState);
    ledState = !ledState;
  }
}

// Função do primeiro semáforo:

void traffic_lights1()
{

  // Programação dos intervalos de tempo do primeiro semáforo utilizando a função millis()
  // *** VERMELHO - 7 SEG; VERDE - 8 SEG; AMARELO - 2 SEG ***

  currentTime = millis();
  time = currentTime - initialTime;
  
  if (time < 7000) {
    digitalWrite(yellow_pin1, LOW);
    digitalWrite(red_pin1, HIGH);
    
  }
  
  if (time >= 7000 && time < 15000) {
    
    digitalWrite(red_pin1, LOW);
    digitalWrite(green_pin1, HIGH);
    
  }
  
  
  if (time >= 15000) {
    digitalWrite(green_pin1, LOW);
    digitalWrite(yellow_pin1, HIGH);
  }
  
  if (time >= 17000) {
    initialTime = millis();
  }
  
}

// Função do segundo semáforo:

void traffic_lights2() {

  // Programação dos intervalos de tempo do segundo semáforo utilizando a função millis()
  // ***  VERDE - 5 SEG; AMARELO - 2 SEG; VERMELHO - 10 SEG ***

  currentTime2 = millis();
  time2 = currentTime2 - initialTime2;
  
  if (time2 < 5000) {             
    digitalWrite(red_pin2, LOW);
    digitalWrite(green_pin2, HIGH);
    
  }
  
  if (time2 >= 5000 && time < 7000) {
    
    digitalWrite(green_pin2, LOW);
    digitalWrite(yellow_pin2, HIGH);
    
  }
  
  if (time2 >= 7000) {
    digitalWrite(yellow_pin2, LOW);
    digitalWrite(red_pin2, HIGH);
  }
  
  
  if (time2 >= 17000) {
    initialTime2 = millis();
  }
}

void loop()
{
  
   if(IR.decode()) {
     Serial.println(IR.decodedIRData.decodedRawData, HEX);
     delay(30);
     IR.resume();
   }

  if (digitalRead(init_button) || IR.decodedIRData.decodedRawData == 0xBA45FF00) { // Verifica o estado do botão de inicializar o ciclo do semáforo
    turn_off_leds();              // Chama a função para apagar todos os leds
    blink_button_state = 0;       // Define o estado do botão de piscar os leds amarelos como 0, para interromper o processo caso esteja em execução
    init_button_state = 1;        // Define o estado do botão de inicializar o ciclo do semáforo como 1
  }

  if (digitalRead(blink_button) || IR.decodedIRData.decodedRawData == 0xB946FF00) { // Verifica o estado do botão de inicializar a função de piscar os leds amarelos
    turn_off_leds();               // Chama a função para apagar todos os leds antes de iniciar a função do botão
    init_button_state = 0;         // Define o botão de inicializar o semáforo como 0, para interromper o processo caso esteja em execução
    blink_button_state = 1;        // Define o botão de piscar os leds amarelos como 1
  }

  if (blink_button_state) {        // Verifica o estado lógico do botão de piscar, caso 1, executar a função blink_yellow()
    blink_yellow();
  }

  if (init_button_state) {      // Verifica o estado lógico do botão de inicializar o ciclo do semáforo, caso 1, executar as funções:
    traffic_lights1();          // Chamada da função do primeiro semáforo
    traffic_lights2();          // Chamada da função do segundo semáforo
  }

}