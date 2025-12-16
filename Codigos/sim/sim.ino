static const int PIN_RX_4G = 18;   // RX del módulo 4G
static const int PIN_TX_4G = 19;   // TX del módulo 4G
static const uint32_t BAUD_4G = 115200;  // Baud típico de A7670/SIM7600

void setup() {
  Serial.begin(115200);
  while (!Serial) { }
  Serial2.begin(BAUD_4G, SERIAL_8N1, PIN_RX_4G, PIN_TX_4G);
}

void loop() {
  while (Serial.available() > 0) {
    Serial2.write(Serial.read());
    yield();
  }
  while (Serial2.available() > 0) {
    Serial.write(Serial2.read());
    yield();
  } 
}