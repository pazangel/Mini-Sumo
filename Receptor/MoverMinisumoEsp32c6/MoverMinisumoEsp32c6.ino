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
  rgb.setBrightness(150);//intensidad en la que brilla el led RGB
  rgb.setPixelColor(0, rgb.Color(255, 0, 0));// pixel 0 o led 0 (el unico que tiene el esp32), en rojo (R, G, B)
  rgb.show();// aplica el cambio

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

// =========== Adelante y Giro =====================
    if (resp.startsWith("W")) {           // ADELANTE
      int x = resp.substring(2).toInt();  // en la posicion 0 esta la letra, en la posicion 1 esta la coma "," y en la posicion 2 esta la coordenada, tomamos la posicion 2 y la convertimos a entero y la guardamos

      if (x == 0) {            // joystick quieto: derecho, a tope
      analogWrite(D0, 0); //motor izquierda, se enciende solo un lado para que el motor vaya hacia el frente
      analogWrite(D1, 255);

      analogWrite(D2, 255);// motor derecha, se enciende solo un lado para que el motor vaya hacia el frente
      analogWrite(D3, 0);
      Serial.println("Adelante");

      }
      // ====== Girar Izquierda =============
      if (x > 0) {  // joystick a la izquierda
        analogWrite(D0, 50);//motor izquierda, se enciende solo un lado para que el motor vaya hacia el frente
        analogWrite(D1, 0);

        x = constrain(x, 50, 515);// la funcion constrain no deja que los valores de x salgan del rango de 50 a 515, si llega un 20 lo convierte a 50, si llega un 516 lo convierte a 515
        analogWrite(D2, map(x, 50, 515, 20, 100));//motor derecha, se enciende solo un lado para que el motor vaya hacia atras, reduciendo el tiempo de encemndido del motor con las coordenadas del joystick
        analogWrite(D3, 0);
/*
cuando el joystick manda 50, ese 50 se convierte en 20 (llanta lenta); si fuera 51 o 52 tambien seria 20, y se queda en 20 hasta 55; si fuera 56 seria 21;
si fuera 100 seria 28, si fuera 282 seria 59, y si fuera 515 seria 100 (llanta al maximo de este giro).
*/
        Serial.println("Adelante y Izquierda");
}
// ================ Girar derecha ===============
       else if (x < 0) {  // joystick a la derecha
        analogWrite(D0, 0);//motor izquierda, se enciende solo un lado para que el motor vaya hacia atras, reduciendo el tiempo de encemndido del motor con las coordenadas del joystick
        x = constrain(x, -515, -50);// la funcion constrain no deja que los valores de x salgan del rango de -515 a -50, si llega un -20 lo convierte a -50, si llega un -516 lo convierte a -515.
        analogWrite(D1, map(x, -50, -515, 20, 100));
/*
cuando el joystick manda -50, ese -50 se convierte en 20 (llanta lenta); si fuera -51 o -52 tambien seria 20, y se queda en 20 hasta -55; si fuera -56 seria 21;
si fuera -100 seria 28, si fuera -282 seria 59, y si fuera -515 seria 100 (llanta a tope).
*/
        analogWrite(D2, 0);//motor derecha, se enciende solo un lado para que el motor vaya hacia el frente
        analogWrite(D3, 50);
        Serial.println("Adelante y Derecha");
      }
    }
// ========= solo Girar ========================
else if(resp.startsWith("G")){ // derecha o izquierda
      int x = resp.substring(2).toInt();  // en la posicion 0 esta la letra, en la posicion 1 esta la coma "," y en la posicion 2 esta la coordenada, tomamos la posicion 2 y la convertimos a entero y la guardamos

// ====== Girar Izquierda =============
      if (x > 0) {  // joystick a la izquierda
        analogWrite(D0, 50);//motor izquierda, se enciende solo un lado para que el motor vaya hacia el frente
        analogWrite(D1, 0);

        x = constrain(x, 50, 515);// la funcion constrain no deja que los valores de x salgan del rango de 50 a 515, si llega un 20 lo convierte a 50, si llega un 516 lo convierte a 515
        analogWrite(D2, map(x, 50, 515, 20, 100));//motor derecha, se enciende solo un lado para que el motor vaya hacia atras, reduciendo el tiempo de encemndido del motor con las coordenadas del joystick
        analogWrite(D3, 0);
/*
cuando el joystick manda 50, ese 50 se convierte en 20 (llanta lenta); si fuera 51 o 52 tambien seria 20, y se queda en 20 hasta 55; si fuera 56 seria 21;
si fuera 100 seria 28, si fuera 282 seria 59, y si fuera 515 seria 100 (llanta al maximo de este giro).
*/
        Serial.println("Izquierda");
}
// ================ Girar derecha ===============
       else if (x < 0) {  // joystick a la derecha
        analogWrite(D0, 0);//motor izquierda, se enciende solo un lado para que el motor vaya hacia atras, reduciendo el tiempo de encemndido del motor con las coordenadas del joystick
        x = constrain(x, -515, -50);// la funcion constrain no deja que los valores de x salgan del rango de -515 a -50, si llega un -20 lo convierte a -50, si llega un -516 lo convierte a -515.
        analogWrite(D1, map(x, -50, -515, 20, 100));
/*
cuando el joystick manda -50, ese -50 se convierte en 20 (llanta lenta); si fuera -51 o -52 tambien seria 20, y se queda en 20 hasta -55, si fuera -56 seria 21;
si fuera -100 seria 28, si fuera -282 seria 59, y si fuera -515 seria 100 (llanta a tope).
*/
        analogWrite(D2, 0);//motor derecha, se enciende solo un lado para que el motor vaya hacia el frente
        analogWrite(D3, 50);
        Serial.println("Derecha");
      }
}
// ============ Atras =================
else if (resp == "S") {    // ATRAS
        analogWrite(D0, 255);  // motor izquierda, se enciende solo un lado por completo para que el motor vaya hacia atras
        analogWrite(D1, 0);

        analogWrite(D2, 0);  // motor derecha, se enciende solo un lado para que el motor vaya hacia atras
        analogWrite(D3, 255);
        Serial.println("Atras");
    }
// ========= Giro rapido Izquierda ==================
else if (resp == "L") {  
  analogWrite(D0, 255);
  analogWrite(D1, 0);
  analogWrite(D2, 255);
  analogWrite(D3, 0);
  Serial.println("Giro rapido izquierda");
 }
// ======== Giro rapido derecha ==================
else if (resp == "R") {  
  analogWrite(D0, 0);
  analogWrite(D1, 255);
  analogWrite(D2, 0);
  analogWrite(D3, 255);
  Serial.println("Giro rapido derecha");
 }

//=========== Freno =================
    else if(resp == "F") { 
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

================================ CONSTRAIN ===============================================================
se agrego la funcion constrain para que mantenga los rangos, porque si el joystick por ruido manda un valor mayor o menor del rango esperado puede que map convierta las velocidades fuera del rango establecido, 
por ejemplo si llega un 530 pueda que lo convierta a 102 y si llega un valor menor como un 10 convertiria ese valor a un valor cercano del 20 como 14, o tambien si el rango de salida fuera de 0 a 255, un 530 se convertiria en 263, y analogWrite solo entiende de 0 a 255, 
en si puede aver compotamientos indefinidos con analogWrite, para que no se salga del rango primero metemos el valor recibido en constraint para que no deje que se salga del rango
y al final le entregamos a map un valor ya dentro del rango
*/