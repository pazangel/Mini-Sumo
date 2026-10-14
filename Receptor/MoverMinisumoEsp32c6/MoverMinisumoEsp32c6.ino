// ===============================
// ESP32-C6 VERSION
// ===============================
#include <Adafruit_NeoPixel.h>
#define RX 14
#define TX 15

#define D0 3
#define D1 4

#define D2 1  // se cambio el pin 6 por el pin 1
#define D3 7

//para apagar el led
#define RGB_PIN 8
Adafruit_NeoPixel rgb(1, RGB_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  Serial.begin(9600);
  rgb.begin();
  rgb.clear();  // Borra color
  rgb.show();   // Aplica cambios

  pinMode(D0, OUTPUT);
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);

  analogWrite(D0, 0);
  analogWrite(D1, 0);
  analogWrite(D2, 0);
  analogWrite(D3, 0);

  // UART hardware (NO SoftwareSerial)
  Serial1.begin(9600, SERIAL_8N1, RX, TX);

  delay(900);
}

void loop() {
  rgb.setBrightness(150);//intensidad en la que brilla el led RGB
  rgb.setPixelColor(0, rgb.Color(255, 0, 0));// pixel 0 o led 0 (el unico que tiene el esp32), en rojo (R, G, B)
  rgb.show();// aplica el cambio
  if (Serial1.available()) {
    String resp = Serial1.readStringUntil('\n');
    resp.trim();
    Serial.println(resp);

    if (resp.startsWith("W")) {           // ADELANTE
      int x = resp.substring(2).toInt();  // en la posicion 0 esta la letra, en la posicion 1 esta la coma "," y en la posicion 2 esta la coordenada, tomamos la posicion 2 y la convertimos a entero y la guardamos

      if (x == 0) {            // joystick quieto: derecho, a tope
        analogWrite(D0, 255);  // motor izquierda hacia adelante
        analogWrite(D1, 0);

        analogWrite(D2, 0);  // motor derecha hacia adelante
        analogWrite(D3, 255);
        Serial.println("Adelante");

      } 
      else if (x > 0) {  // joystick a la izquierda: baja la llanta izquierda del robot (D3)
        analogWrite(D0, 255);//motor izquierda
        analogWrite(D1, 0);

        analogWrite(D2, 0);//motor derecha
        analogWrite(D3, map(x, 50, 515, 255, 100));
        Serial.println("Adelante e izquierda");

      } else if (x < 0) {  // joystick a la derecha: baja la llanta derecha del robot (D0)
        analogWrite(D0, map(x, -50, -515, 255, 100));//motor izquierda
        analogWrite(D1, 0);

        analogWrite(D2, 0);//motor derecha
        analogWrite(D3, 255);
        Serial.println("Adelante y derecha");
      }
    }

else if(resp.startsWith("G")){ // derecha o izquierda
      int x = resp.substring(2).toInt();  // en la posicion 0 esta la letra, en la posicion 1 esta la coma "," y en la posicion 2 esta la coordenada, tomamos la posicion 2 y la convertimos a entero y la guardamos

      if (x > 0) {  // joystick a la izquierda: baja la llanta izquierda del robot (D3)
        analogWrite(D0, 255);//motor izquierda
        analogWrite(D1, 0);

        analogWrite(D2, 0);//motor derecha
        analogWrite(D3, map(x, 50, 515, 255, 100));
        /*
cuando el joystick manda 50, ese 50 se convierte en 255 (llanta a tope); si fuera 51 tambien seria 255, y si fuera 52 serian 254;
si fuera 100 seria 228, si fuera 282 seria 128, y si fuera 515 seria 0 (llanta parada).
        */
        Serial.println("Adelante e izquierda");

      } else if (x < 0) {  // joystick a la derecha: baja la llanta derecha del robot (D0)
        analogWrite(D0, map(x, -50, -515, 255, 100));//motor izquierda
        /*
cuando el joystick manda -50, ese -50 se convierte en 255 (llanta a tope); si fuera -51 tambien seria 255, y si fuera -52 serian 254;
si fuera -100 seria 228, si fuera -282 seria 128, y si fuera -515 seria 0 (llanta parada).
        */
        analogWrite(D1, 0);


        analogWrite(D2, 0);//motor derecha
        analogWrite(D3, 255);
        Serial.println("Adelante y derecha");
      }
}

if (resp == "S") {    // ATRAS
      analogWrite(D0, 0); //motor izquierda
      analogWrite(D1, 255);

      analogWrite(D2, 255);// motor derecha
      analogWrite(D3, 0);
      Serial.println("Adelante");
    }

    else if (resp == "F") {  // FRENO
      analogWrite(D0, 0);//motor izquierda
      analogWrite(D1, 0);

      analogWrite(D2, 0);//motor derecha
      analogWrite(D3, 0);
      Serial.println("Freno");
    }
  }
}

/*
D0 Y D1 Controlan al motor de la izquierda
D2 Y D3 controlan el motor de la derecha

nota: verlo de frente

D2 estaba en el pin 6, al encender o resetear la placa mandaba una
señal al driver y el motor derecho daba un tiron. Se cambio al pin 1 y ya no pasa.
*/