// ===============================
// ESP32-C6 VERSION
// ===============================
#include <Adafruit_NeoPixel.h>
#define RX 14
#define TX 15

#define D0 3
#define D1 4

#define D2 6
#define D3 7  

//para apagar el led
#define RGB_PIN 8
Adafruit_NeoPixel rgb(1, RGB_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  Serial.begin(9600);
  rgb.begin();
  rgb.clear();     // Borra color
  rgb.show();      // Aplica cambios

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
  if (Serial1.available()) {
    String resp = Serial1.readStringUntil('\n');
    resp.trim();
    Serial.println(resp);

    if (resp == "W") {    // ADELANTE
      analogWrite(D0, 0); //motor izquierda
      analogWrite(D1, 255);

      analogWrite(D2, 255);// motor derecha
      analogWrite(D3, 0);
      Serial.println("Adelante");
    }

    else if (resp == "S") {     // ATRAS
      analogWrite(D0, 255);
      analogWrite(D1, 0);   

      analogWrite(D2, 0);
      analogWrite(D3, 255);
      Serial.println("Atras");
    }

    else if (resp == "A") {   // IZQUIERDA (gira sobre su eje)
      analogWrite(D0, 240);   // motor izquierda hacia atrás
      analogWrite(D1, 0);

      analogWrite(D2, 240);   // motor derecha hacia adelante
      analogWrite(D3, 0);
      Serial.println("Izquierda");
    }

    else if (resp == "D") {   // DERECHA (gira sobre su eje)
      analogWrite(D0, 0);     // motor izquierda hacia adelante
      analogWrite(D1, 240);

      analogWrite(D2, 0);     // motor derecha hacia atrás
      analogWrite(D3, 240);
      Serial.println("Derecha");
    }

    else if (resp == "F") {    // FRENO
      analogWrite(D0, 0);
      analogWrite(D1, 0);
      analogWrite(D2, 0);
      analogWrite(D3, 0);
      Serial.println("Freno");
    }
  }
}

/*
D0 Y D1 Controlan al motor de la izquierda
D2 Y D3 controlan el motor de la derecha

nota: verlo de frente
*/