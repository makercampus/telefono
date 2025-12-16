/*
  TEST: Teclera 4x4 (Negra)

  CONEXIONES FÍSICAS REALES:
  --------------------------
  COLUMNAS (C1, C2, C3, C4) -> Pines 26, 25, 33, 32
  FILAS    (R1, R2, R3, R4) -> Pines 13, 4, 22, 27
*/



#include <Keypad.h>

const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};


byte rowPins[ROWS] = {13, 4, 22, 27}; 
byte colPins[COLS] = {26, 25, 33, 32}; 

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

void setup() {
  Serial.begin(115200);
  delay(2000); 
  Serial.println("=== TEST TECLERA 4x4 NEGRA ===");
}

void loop() {
  char key = keypad.getKey();
  
  if (key) {
    Serial.print("Tecla: ");
    Serial.println(key);
    delay(100); 
  }
} 


