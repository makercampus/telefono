#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>

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

void setup() {
  Serial.begin(115200);

  // Iniciar SPI con pines personalizados
  spi.begin(TFT_SCK, -1, TFT_MOSI, TFT_CS);

  // Iniciar pantalla (ajusta si no se ve)
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
  if (Serial.available()) {
    String data = Serial.readString();
    data.trim(); // Limpiar espacios/saltos de linea
    
    if (data.length() > 0) {
      tft.fillScreen(ST77XX_BLACK);
      tft.setCursor(0, 0);
      tft.println(data);
    }
  }
}
