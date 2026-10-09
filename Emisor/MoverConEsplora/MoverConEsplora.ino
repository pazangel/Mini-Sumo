#include <SoftwareSerial.h>
#include <Esplora.h>

SoftwareSerial Serial2(11, 3);  // rx, tx

void setup() {
  Serial.begin(9600);
  Serial2.begin(9600);
}

void loop() {

  int botonArriba   = Esplora.readButton(SWITCH_UP);
  int botonAbajo    = Esplora.readButton(SWITCH_DOWN);
  int botonIzq      = Esplora.readButton(SWITCH_LEFT);
  int botonDer      = Esplora.readButton(SWITCH_RIGHT);

  if (botonArriba == LOW) {
    Serial2.println("W");   // Adelante
    Serial.println("W");
  }
  else if (botonAbajo == LOW) {
    Serial2.println("S");   // Atrás
    Serial.println("S");
  }
  else if (botonIzq == LOW) {
    Serial2.println("A");   // Girar izquierda
    Serial.println("A");
  }
  else if (botonDer == LOW) {
    Serial2.println("D");   // Girar derecha
    Serial.println("D");
  }
  else {
    Serial2.println("F");   // Freno
    Serial.println("F");
  }

  delay(20);
}