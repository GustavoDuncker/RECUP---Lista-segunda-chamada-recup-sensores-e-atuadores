#define sensorLuz 5
#define botaoModo 35
#define luzVerde 14
#define luzBranca 16

bool automatico = true;
bool estadoBranco = false;

void setup() {
  Serial.begin(9600);
  pinMode(sensorLuz, INPUT);
  pinMode(botaoModo, INPUT_PULLUP);
  pinMode(luzVerde, OUTPUT);
  pinMode(luzBranca, OUTPUT);

  digitalWrite(luzVerde, HIGH);
  digitalWrite(luzBranca, LOW);
  Serial.println("Sistema iniciado - Modo AUTOMÁTICO");
}

void loop() {
  if (digitalRead(botaoModo) == LOW) {
    automatico = !automatico;
    delay(300);
  }

  int leituraLuz = analogRead(sensorLuz);
  Serial.print("Valor do LDR: ");
  Serial.println(leituraLuz);

  if (automatico) {
    digitalWrite(luzVerde, HIGH);
    if (leituraLuz < 2000) {
      digitalWrite(luzBranca, HIGH);
    } else {
      digitalWrite(luzBranca, LOW);
    }
  } else {
    digitalWrite(luzVerde, LOW);
    if (digitalRead(botaoModo) == LOW) {
      estadoBranco = !estadoBranco;
      digitalWrite(luzBranca, estadoBranco);
      delay(300);
    }
  }

  delay(100);
}
