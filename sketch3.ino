#include <ESP32Servo.h>

const int PIN_TRIG = 33;
const int PIN_ECHO = 32;
const int PIN_LED = 16;
const int PIN_BOTAO = 27;
const int PIN_SERVO = 26;

Servo motorPortao;

bool estadoPortao = false; 
bool botaoAnterior = HIGH;
unsigned long tempoAnterior = 0;

int posicaoServo = 0;
int alvoServo = 0;

unsigned long tempoPiscar = 0;
int contadorPisca = 0;
bool piscando = false;
bool ledEstado = LOW;

// Função para medir distância
long lerDistancia() {
  digitalWrite(PIN_TRIG, LOW);
  delayMicroseconds(3);
  digitalWrite(PIN_TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(PIN_TRIG, LOW);
  long duracao = pulseIn(PIN_ECHO, HIGH, 30000);
  return duracao * 0.034 / 2;
}

void setup() {
  Serial.begin(9600);
  pinMode(PIN_TRIG, OUTPUT);
  pinMode(PIN_ECHO, INPUT);
  pinMode(PIN_LED, OUTPUT);
  pinMode(PIN_BOTAO, INPUT_PULLUP);

  motorPortao.attach(PIN_SERVO);
  motorPortao.write(0);
  Serial.println("Sistema iniciado — portão fechado.");
}

void loop() {
  bool botaoAtual = digitalRead(PIN_BOTAO);
  unsigned long agora = millis();

  if (botaoAnterior == HIGH && botaoAtual == LOW) {
    long distancia = lerDistancia();
    Serial.print("Distância: ");
    Serial.print(distancia);
    Serial.println(" cm");

    if (!estadoPortao) {
      if (distancia > 20) {
        Serial.println("Abrindo portão...");
        alvoServo = 90;
        digitalWrite(PIN_LED, HIGH);
        estadoPortao = true;
      } else {
        Serial.println("Obstáculo detectado! Portão não abrirá.");
        piscando = true;
        contadorPisca = 0;
        tempoPiscar = agora;
      }
    } else {
      Serial.println("Fechando portão...");
      alvoServo = 0;
      digitalWrite(PIN_LED, LOW);
      estadoPortao = false;
    }
  }
  botaoAnterior = botaoAtual;

  if (posicaoServo < alvoServo && agora - tempoAnterior > 30) {
    posicaoServo++;
    motorPortao.write(posicaoServo);
    tempoAnterior = agora;
  } else if (posicaoServo > alvoServo && agora - tempoAnterior > 30) {
    posicaoServo--;
    motorPortao.write(posicaoServo);
    tempoAnterior = agora;
  }

  if (piscando && agora - tempoPiscar > 150) {
    ledEstado = !ledEstado;
    digitalWrite(PIN_LED, ledEstado);
    tempoPiscar = agora;
    contadorPisca++;

    if (contadorPisca >= 6) {
      piscando = false;
      digitalWrite(PIN_LED, LOW);
    }
  }
}
