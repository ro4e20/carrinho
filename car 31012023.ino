#include <Servo.h>
Servo servo;

int SERVO = 11; // servomotor ligado em uma porta digital PWM
int MET = 10;      // motor da esquerda para trás 
int MEF = 9;        // motor da esquerda para frente
int MDF = 6;        // motor da direita para frente
int MDT = 5;        // motor da direita para trás
int POT = 255;     // potência do motor de 0 a 255
int TRIG = 8;        // essa porta envia um sinal para o sensor ultrassônico
int ECO = 7;         // essa porta recebe um sinal do sensor ultrassônico
int tempo;             // duração do sinal enviado do sensor ultrassônico
int F, E, D;            // distâncias medidas da frente (90°), da direita (30°) e esquerda (150°)

void setup( ) {
  pinMode(MEF, OUTPUT);
  pinMode(MET, OUTPUT);
  pinMode(MDF, OUTPUT);
  pinMode(MDT, OUTPUT);
  pinMode(ECO, INPUT);
  pinMode(TRIG, OUTPUT);
  digitalWrite(TRIG, LOW);
  servo.attach(SERVO);   // associa o objeto ao pino digital 11
  servo.write(90);             // inicia olhando para frente (ângulo de 90°)
  delay(2000);
}
  
void loop( ) {
  analogWrite(MDF, 0);    // inicia com os motores parados
  analogWrite(MEF, 0);   
  analogWrite(MDT, 0);
  analogWrite(MET, 0); 

  servo.write(30);          // gira para direita (ângulo de 30°)
  delay(1500);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);
  tempo = pulseIn(ECO, HIGH);
  D = tempo/58;          // calcula a distância a partir do tempo de ida e volta do ultrassom com v = 345 m/s

  servo.write(150);       // gira para esquerda (ângulo de 150°)
  delay(1500);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);
  tempo = pulseIn(ECO, HIGH);
  E = tempo/58;  

  servo.write(90);       // gira para frente (ângulo de 90°)
  delay(1500);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);
  tempo = pulseIn(ECO, HIGH);
  F = tempo/58;  

  if (F > 30) {                                  
    if ((D > 20) && (E > 20)) {         // o carrinho vai para frente desde que a distância ao obstáculo for maior que 30 cm
      analogWrite(MDF, POT);
      analogWrite(MEF, POT);   
      analogWrite(MDT, 0);
      analogWrite(MET, 0); 
      delay (1500);
    }
    
    else {
      if (D > E) {                              // o carrinho gira para a direita
        analogWrite(MDF, 0);
        analogWrite(MEF, POT);   
        analogWrite(MDT, POT);
        analogWrite(MET, 0); 
        delay (500);
      }

      else {                                       // o carrinho gira para a esquerda
        analogWrite(MDF, POT);
        analogWrite(MEF, 0);   
        analogWrite(MDT, 0);
        analogWrite(MET, POT); 
        delay (500);
      }
    }
  }
    
  else {                               // se a distância for menor do que 30 cm, então ele dá ré e gira 
    analogWrite(MDF, 0);
    analogWrite(MEF, 0);   
    analogWrite(MDT, POT);
    analogWrite(MET, POT);
    delay (500);
    analogWrite(MDF, POT);
    analogWrite(MEF, 0);   
    analogWrite(MDT, 0);
    analogWrite(MET, POT);
    delay (750);
  } 
}
