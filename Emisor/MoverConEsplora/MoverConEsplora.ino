#include <SoftwareSerial.h>
#include <Esplora.h>

SoftwareSerial Serial2(11, 3);  // rx, tx

//variables globales

//variable para
int xCenter;

void setup() {
  Serial.begin(9600);
  Serial2.begin(9600);  // inicializa la comunicacion con la antena HC-12

  //Joystick
  //leemos un valor inicial para hacer la calibracion
  Esplora.writeRGB(255, 0, 0);//enciende el led RGB en rojo para indicar que no se mueva el joystick
  delay(1000);
  xCenter = Esplora.readJoystickX();// lee un valor inicial en x y lo guarda en la variable global 

  Esplora.writeRGB(0, 255, 0);// enciende el led RGB en verde para indicar que ya se puede mover el joystick
  delay(1000);
  Esplora.writeRGB(0, 0, 0);
}

void loop() {
  //botón
  int botonArriba = Esplora.readButton(SWITCH_UP);

  //Joystick
  int x = Esplora.readJoystickX() - xCenter;  // leer posicion en x menos el valor leido del inicio

  // Zona muerta
  if (abs(x) < 50) {  // se le saca valor absoluto a x en caso de ser negativo y si es menor de 50, x valdra 0, esto para eliminar el ruido mecanico del centro
    x = 0;
  }

  if (botonArriba == LOW) {
    Serial2.println("W,"+ String(x));  // Adelante y mover derecha o izquierda si se desea
    Serial.println("W,"+ String(x));
  }

  else if (x != 0) {
    Serial2.println("G," + String(x));  // Giro sin avanzar
    Serial.println("G," + String(x));
  }

  else {
    Serial2.println("F");  // Freno
    Serial.println("F");
  }

  delay(20);
}
