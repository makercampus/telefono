
### Ejemplo con módulo KY-037 / KY-038

La salida `DO` entrega un **umbral digital**  
La salida `AO` entrega la **amplitud real del sonido**.

| Módulo | ESP32 | Descripción |
|:-------|:------|:-------------|
| AO | GPIO34 / GPIO35 / GPIO36 / GPIO39 | Entrada analógica |
| G | GND | Tierra |
| + | 3.3V | Alimentación |
| DO | (Opcional) cualquier pin digital | Umbral digital |

---

## Pantalla SPI (TFT 1.8” ST7735)

**Conexión recomendada utilizando SPI por hardware:**

| Pantalla | ESP32 | Descripción |
|:----------|:------|:-------------|
| GND | GND | Tierra |
| VCC | 3.3V | Alimentación (no usar 5V) |
| SCK | GPIO18 | Reloj SPI |
| SDA (MOSI) | GPIO23 | Datos hacia la pantalla |
| RES | GPIO4 | Reset |
| DC | GPIO2 | Data/Command |
| CS | GPIO5 | Chip Select |
| BL | 3.3V o GPIO15 | Luz de fondo (Backlight) |

---

## Teclera 4x4 ZRX-543

La **teclera** se conecta directamente a GPIOs (no requiere VCC ni GND).

COLUMNAS (C1, C2, C3, C4) -> Pines 26, 25, 33, 32

FILAS    (R1, R2, R3, R4) -> Pines 13, 4, 22, 27

| Teclera   | ESP32  | Número Conector |
|:--------- |:-------|:----------------|
| R1        | GPIO13 | 8               |
| R2        | GPIO4  | 7               |
| R3        | GPIO22 | 6               |
| R4        | GPIO27 | 5               |
| C1        | GPIO26 | 4               |
| C2        | GPIO25 | 3               |
| C3        | GPIO33 | 2               |
| C4        | GPIO32 | 1               |

---

## Módulo SIM A7670G — CAT1_A767X

| A7670G Pin | ESP32 | Nota |
|:-------------|:------|:------|
| UTX | GPIO16 | RX2 del ESP32 |
| URX | GPIO17 | TX2 del ESP32 |
| PWR-K | GPIO27 | Encendido del módulo |
| SLEEP# | (opcional) GPIO26 | Modo de suspensión |
| 5–12V | Fuente 5–12V / USB-C | No usar 3.3V |
| GND | GND ESP32 + GND fuente | Tierra común |

**Importante:**  
El módulo requiere **corriente alta (picos de 2A)**.  
Se recomienda alimentarlo por **USB-C** o por una **fuente 5V 2A externa** y **unir las tierras**.

---
