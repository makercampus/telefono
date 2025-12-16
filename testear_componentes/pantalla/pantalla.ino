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

  tft.setCursor(10, 20);
  tft.println("ESP32 OK");

  tft.setCursor(10, 50);
  tft.println("ST7735");

  tft.setCursor(10, 80);
  tft.println("SPI GPIO14");

  delay(2000);

  // Test colores
  tft.fillScreen(ST77XX_RED);   delay(500);
  tft.fillScreen(ST77XX_GREEN); delay(500);
  tft.fillScreen(ST77XX_BLUE);  delay(500);
  tft.fillScreen(ST77XX_BLACK);

  tft.setCursor(10, 70);
  tft.println("Maker Campus");
}

void loop() {
}
