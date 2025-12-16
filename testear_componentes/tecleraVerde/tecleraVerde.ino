/*
  TEST: Teclera 5x4 HX-543 la verdecita

  Abre el Monitor Serie a 115200 y presiona teclas.
  Debería mostrar qué tecla se presionó.
*/

#include <Keypad.h>

const byte ROWS = 5;
const byte COLS = 4;

char keys[ROWS][COLS] = {
  { 'A',  'B',  '#',  '*'  },  // F1, F2, #, *
  { '1',  '2',  '3',  'U'  },  // 1, 2, 3, UP
  { '4',  '5',  '6',  'D'  },  // 4, 5, 6, DOWN
  { '7',  '8',  '9',  'E'  },  // 7, 8, 9, ESC
  { 'L',  '0',  'R',  'O'  }   // LEFT, 0, RIGHT, ENTER
};

/*
  Conexiones actualizadas:
  Filas (R1-R5):
    R1 -> GPIO 32
    R2 -> GPIO 33
    R3 -> GPIO 25
    R4 -> GPIO 26
    R5 -> GPIO 22 
  Columnas (C1-C4):
    C1 -> GPIO 27
    C2 -> GPIO 13
    C3 -> GPIO 4
    C4 -> GPIO 2 
*/
byte rowPins[ROWS] = {32, 33, 25, 26, 22};
byte colPins[COLS] = {27, 13, 4, 2};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

void setup() {
  Serial.begin(115200);
  Serial.println("=== TEST TECLERA HX-543 ===");
  Serial.println("Presiona cualquier tecla...");
}

void loop() {
  char key = keypad.getKey();
  
  if (key) {
    Serial.print("Tecla presionada: ");
    
    // Traducir caracteres especiales
    switch (key) {
      case 'A': Serial.println("F1"); break;
      case 'B': Serial.println("F2"); break;
      case 'U': Serial.println("UP"); break;
      case 'D': Serial.println("DOWN"); break;
      case 'L': Serial.println("LEFT"); break;
      case 'R': Serial.println("RIGHT"); break;
      case 'E': Serial.println("ESC"); break;
      case 'O': Serial.println("ENTER"); break;
      default:  Serial.println(key); break;
    }
  }
}