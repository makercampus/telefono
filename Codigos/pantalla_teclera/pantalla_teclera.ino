#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <Keypad.h>

// --- CONFIGURACIÓN PANTALLA ---
// Pines TFT
#define TFT_CS   5
#define TFT_DC   16
#define TFT_RST  17
#define TFT_SCK  14
#define TFT_MOSI 23

// Crear SPI personalizado
SPIClass spi = SPIClass(VSPI);

// Crear pantalla usando ese SPI
Adafruit_ST7735 tft = Adafruit_ST7735(&spi, TFT_CS, TFT_DC, TFT_RST);

// --- CONFIGURACIÓN TECLADO ---
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

// Buffer para el texto
String inputString = "";

void setup() {
  Serial.begin(115200);

  // Iniciar SPI con pines personalizados
  spi.begin(TFT_SCK, -1, TFT_MOSI, TFT_CS);

  // Iniciar pantalla
  tft.initR(INITR_BLACKTAB);
  tft.setRotation(1);
  tft.fillScreen(ST77XX_BLACK);

  tft.setTextColor(ST77XX_GREEN);
  tft.setTextSize(2);

  // Mostrar Maker Campus por 1 segundo
  tft.setCursor(10, 70);
  tft.println("Maker Campus");
  delay(1000);

  // Limpiar pantalla
  tft.fillScreen(ST77XX_BLACK);
  tft.setCursor(0, 0);
}

void loop() {
  char key = keypad.getKey();
  
  if (key) {
    Serial.print("Tecla: ");
    Serial.println(key);

    // Si presionamos 'D', borramos la pantalla (opcional)
    if (key == 'D') {
      inputString = "";
      tft.fillScreen(ST77XX_BLACK);
      tft.setCursor(0, 0);
    } else {
      // Agregamos la tecla al buffer
      inputString += key;
      
      // Actualizamos pantalla
      tft.fillScreen(ST77XX_BLACK);
      tft.setCursor(0, 0);
      tft.println(inputString);
    }
  }
}
