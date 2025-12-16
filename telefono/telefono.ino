#include <Arduino.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <Keypad.h>

// -------------------- PINES --------------------

// Pantalla ST7735 (SPI VSPI) - Configuración de pantalla.ino
#define TFT_CS   5
#define TFT_DC   16
#define TFT_RST  17
#define TFT_SCLK 14
#define TFT_MOSI 23

// Crear SPI personalizado para la pantalla
SPIClass spi = SPIClass(VSPI);
Adafruit_ST7735 tft = Adafruit_ST7735(&spi, TFT_CS, TFT_DC, TFT_RST);

// Teclera 4x4 - Configuración de tecleraNegra.ino
const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

// Pines de la teclera
byte rowPins[ROWS] = {13, 4, 22, 27}; 
byte colPins[COLS] = {26, 25, 33, 32}; 

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// Módulo SIM A7670G - Configuración de sim.ino
HardwareSerial A7670G(2);
const int PIN_SIM_RX    = 18;   // RX2 ESP32 (Conectar a TX del SIM)
const int PIN_SIM_TX    = 19;   // TX2 ESP32 (Conectar a RX del SIM)

// Variables Globales
String phoneNumber = "+569";
bool isCalling = false;

// -------------------- FUNCIONES --------------------

void updateScreen() {
  tft.fillScreen(ST7735_BLACK);
  
  // Título
  tft.setTextColor(ST7735_WHITE);
  tft.setTextSize(1);
  tft.setCursor(10, 10);
  tft.println("MAKER PHONE");
  
  // Número
  tft.setTextColor(ST7735_GREEN);
  tft.setTextSize(2);
  tft.setCursor(10, 40);
  tft.println(phoneNumber);
  
  // Estado
  tft.setTextSize(1);
  tft.setTextColor(ST7735_YELLOW);
  tft.setCursor(10, 80);
  if (isCalling) {
    tft.println("LLAMANDO...");
  } else {
    tft.println("LISTO");
  }
  
  // Instrucciones
  tft.setTextColor(ST7735_WHITE);
  tft.setCursor(0, 100);
  tft.println("A:Llamar B:Borrar");
  tft.println("C:Limpiar D:Cortar");
}


void simSendAT(const String& cmd) {
  Serial.println("CMD: " + cmd);
  A7670G.println(cmd);
}

// -------------------- SETUP --------------------
void setup() {
  Serial.begin(115200);
  
  // Configurar Pantalla
  spi.begin(TFT_SCLK, -1, TFT_MOSI, TFT_CS);
  tft.initR(INITR_BLACKTAB);
  tft.setRotation(1);
  updateScreen();
  
  // Configurar SIM
  A7670G.begin(115200, SERIAL_8N1, PIN_SIM_RX, PIN_SIM_TX);
  // simPowerOn();
  
  // Sincronizar SIM
  simSendAT("AT");
  delay(1000);
  simSendAT("AT+CSQ");
}

// -------------------- LOOP --------------------
void loop() {
  char key = keypad.getKey();
  
  if (key) {
    Serial.println(key); // Debug
    
    if (key == 'A') {
      // LLAMAR
      if (phoneNumber.length() > 4) {
        isCalling = true;
        updateScreen();
        simSendAT("ATD" + phoneNumber + ";");
      }
    } else if (key == 'B') {
      // BORRAR
      if (phoneNumber.length() > 4) {
        phoneNumber.remove(phoneNumber.length() - 1);
        updateScreen();
      }
    } else if (key == 'C') {
      // LIMPIAR
      phoneNumber = "+569";
      isCalling = false;
      updateScreen();
    } else if (key == 'D') {
      // CORTAR
      isCalling = false;
      updateScreen();
      simSendAT("ATH");
    } else {
      // NUMEROS
      if (phoneNumber.length() < 15) { // Limite de caracteres
        phoneNumber += key;
        updateScreen();
      }
    }
  }
  
  // Leer respuestas del SIM
  while (A7670G.available()) {
    Serial.write(A7670G.read());
  }
}
