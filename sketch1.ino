#define ledOk 14
#define ledAlerta 27
#define botaoAcionador 18
#define pinTrig 15
#define pinEcho 2

bool ativo = false;
bool alarme = false;

void setup() {
  Serial.begin(115200);
  pinMode(pinTrig, OUTPUT);
  pinMode(pinEcho, INPUT);
  pinMode(ledOk, OUTPUT);
  pinMode(ledAlerta, OUTPUT);
  pinMode(botaoAcionador, INPUT_PULLUP);
}

void loop() {
  if (digitalRead(botaoAcionador) == LOW) {
    ativo = !ativo;
    if (!ativo) {
      alarme = false;
    }
    delay(300);
  }

  if (ativo) {
    digitalWrite(ledOk, HIGH);

    // mede distância
    digitalWrite(pinTrig, LOW);
    delayMicroseconds(2);
    digitalWrite(pinTrig, HIGH);
    delayMicroseconds(10);
    digitalWrite(pinTrig, LOW);

    long tempo = pulseIn(pinEcho, HIGH);
    int distancia = tempo * 0.034 / 2;

    Serial.print("Distancia: ");
    Serial.print(distancia);
    Serial.println(" cm");

    if (distancia < 50) {
      alarme = true; 
    }

    if (alarme) {
      digitalWrite(ledOk, LOW);
      digitalWrite(ledAlerta, HIGH);
      delay(300);
      digitalWrite(ledAlerta, LOW);
      delay(300);
    } else {
      digitalWrite(ledAlerta, LOW);
    }

  } else {
    digitalWrite(ledOk, LOW);
    digitalWrite(ledAlerta, LOW);
  }
}
