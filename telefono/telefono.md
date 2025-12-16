# Guía de Montaje: Teléfono Maker

Esta guía detalla paso a paso cómo conectar y programar el Teléfono Maker utilizando un ESP32, una pantalla TFT, una teclera matricial y un módulo SIM A7670G.

---

## 1. Configuración del Entorno de Desarrollo (Arduino IDE)

Antes de conectar nada, asegúrate de tener el software listo.

### A. Instalar Soporte para ESP32
1.  Abre Arduino IDE y ve a **Archivo > Preferencias**.
2.  En "Gestor de URLs Adicionales de Tarjetas", pega lo siguiente:
    `https://dl.espressif.com/dl/package_esp32_index.json`
3.  Ve a **Herramientas > Placa > Gestor de Tarjetas**.
4.  Busca **"esp32"** (por Espressif Systems) e instálalo (versión 2.0.14 o superior recomendada).
5.  Selecciona tu placa en **Herramientas > Placa > ESP32 Arduino**.
    *   En el cuadro de búsqueda que aparece, escribe **"DEV"**.
    *   Selecciona la opción **"DOIT ESP32 DEVKIT V1"**.
    *   Esta es la placa estándar más compatible para este proyecto.

### B. Instalar Librerías Necesarias
Ve a **Herramientas > Administrar Bibliotecas** e instala las siguientes:

1.  **Adafruit GFX Library** (por Adafruit) - Gráficos base.
2.  **Adafruit ST7735 and ST7789 Library** (por Adafruit) - Controlador de pantalla.
3.  **Keypad** (por Mark Stanley, Alexander Brevig) - Manejo de la teclera matricial.

---

## 2. Lista de Componentes

*   **Microcontrolador:** ESP32 (30 pines o 38 pines)
*   **Pantalla:** TFT ST7735 1.8" (SPI)
*   **Teclado:** Matricial 4x4 (Membrana negra)
*   **Comunicación:** Módulo SIM A7670G (LTE/4G)
*   **Audio:** Speaker y Micrófono (Conectados directamente al módulo SIM)

---

## 3. Preparación Crítica: SIM y Energía

Antes de conectar los cables, es vital preparar el chip y la fuente de energía.

### A. Activación y Preparación de la SIM
1.  **Desbloqueo del PIN:** Inserta la tarjeta SIM en un teléfono móvil normal. Ve a configuración de seguridad y **desactiva la solicitud de PIN**. El módulo A7670G no podrá conectarse si la SIM pide PIN al inicio.
2.  **Activación de Línea:** Realiza una llamada de prueba desde el celular para asegurar que el chip está activo y tiene saldo/minutos.
3.  **Red 4G/LTE:** Verifica que tengas cobertura 4G en tu zona, ya que este módulo opera en redes LTE.

### B. Requerimientos de Energía (¡Muy Importante!)
*   **Picos de Corriente:** El módulo SIM puede tener picos de consumo de hasta **2 Amperios** al registrarse en la red o hacer una llamada.
*   **Fuente Externa:** El puerto USB del computador **NO** es suficiente para alimentar el módulo SIM.
*   **Conexión:** Debes usar una fuente de 5V externa (batería LiPo o fuente de banco) conectada a los pines VCC/GND del módulo.
*   **Tierra Común (Common Ground):** Debes conectar el GND de la fuente externa al GND del ESP32. Si no unes las tierras, la comunicación fallará.

---

## 4. Diagrama de Conexiones

### A. Pantalla TFT ST7735 (SPI)
La pantalla utiliza el bus VSPI del ESP32.

| Pin Pantalla | Pin ESP32 | Función |
| :--- | :--- | :--- |
| **VCC** | 3.3V | Alimentación |
| **GND** | GND | Tierra |
| **CS** | GPIO 5 | Chip Select |
| **RESET** | GPIO 17 | Reset |
| **A0 / DC** | GPIO 16 | Data/Command |
| **SDA / MOSI** | GPIO 23 | Datos (Master Out Slave In) |
| **SCK** | GPIO 14 | Reloj SPI |
| **LED** | 3.3V | Backlight (Luz de fondo) |

### B. Teclera Matricial 4x4
Conexión directa a los pines digitales. No requiere resistencias adicionales si se usa `INPUT_PULLUP` interno (la librería Keypad lo hace).

| Pin Teclera (Conector) | Pin ESP32 | Función |
| :--- | :--- | :--- |
| **1** (Izquierda) | GPIO 32 | Columna 4 |
| **2** | GPIO 33 | Columna 3 |
| **3** | GPIO 25 | Columna 2 |
| **4** | GPIO 26 | Columna 1 |
| **5** | GPIO 27 | Fila 4 |
| **6** | GPIO 22 | Fila 3 |
| **7** | GPIO 4 | Fila 2 |
| **8** (Derecha) | GPIO 13 | Fila 1 |

### C. Módulo SIM A7670G
El módulo se comunica por puerto serie (UART2).

| Pin Módulo SIM | Pin ESP32 | Función |
| :--- | :--- | :--- |
| **UTX** | GPIO 18 | Recepción ESP32 (RX2) |
| **URX** | GPIO 19 | Transmisión ESP32 (TX2) |
| **GND** | GND | Tierra Común |
| **VCC** | 5V (Ext) | Fuente externa recomendada (2A) |

### D. Audio (Speaker y Micrófono)
**IMPORTANTE:** El audio se conecta directamente al módulo SIM mediante los conectores blancos JST ZH 1.5mm. **NO** se conectan al ESP32.

*   **Speaker:** Conector JST de 2 pines en el módulo SIM.
    *   Amarillo: SPK+
    *   Blanco: SPK-
*   **Micrófono:** Conector JST de 2 pines en el módulo SIM.
    *   Rojo: MIC+
    *   Negro: MIC- (GND)

---

## 5. Funcionamiento del Código

El programa `telefono.ino` integra todos los componentes para realizar llamadas telefónicas básicas.

### Interfaz de Usuario
*   **Pantalla de Inicio:** Muestra "MAKER PHONE" y el número actual (inicia con `+569`).
*   **Estado:** Indica si está "LISTO" o "LLAMANDO...".

### Controles del Teclado
*   **Teclas 0-9, *, #:** Escriben el número telefónico.
*   **Tecla A (Llamar):** Inicia la llamada al número en pantalla. Envía el comando AT `ATD+569...;`.
*   **Tecla B (Borrar):** Borra el último dígito ingresado. No permite borrar el prefijo `+569`.
*   **Tecla C (Limpiar):** Reinicia el número a `+569` y cancela cualquier estado de llamada.
*   **Tecla D (Cortar):** Finaliza la llamada en curso. Envía el comando AT `ATH`.

### Flujo de Encendido
1.  Inicia comunicación Serial con PC (115200 baudios).
2.  Inicia Pantalla TFT (Fondo negro).
3.  Sincroniza comunicación con el SIM (Envía `AT`).
4.  Verifica señal (`AT+CSQ`).
5.  Queda listo para recibir teclas.

---

## 6. Pruebas y Verificación con Monitor Serial

Para asegurar que todo funciona antes de cerrar la caja, usaremos el Monitor Serial de Arduino.

### A. Configuración del Monitor
1.  Conecta el ESP32 al PC por USB.
2.  En Arduino IDE, abre el monitor: **Herramientas > Monitor Serie** (o Ctrl+Shift+M).
3.  **Velocidad (Baud Rate):** Selecciona **115200 baud** en la esquina inferior derecha.
4.  **Ajuste de Línea:** Selecciona **"Ambos NL & CR"** (New Line & Carriage Return). Esto es crucial para que el módulo SIM entienda los comandos.

### B. Mensajes de Inicio Esperados
Al presionar el botón **EN** (Reset) del ESP32, deberías ver algo similar a esto:

```text
... (mensajes de boot del ESP32) ...
Iniciando Telefono Maker...
Iniciando Pantalla... OK
Probando modulo SIM...
Modulo SIM OK
Conectado a la red!
Nivel de senal: 25 (Excelente)
Listo para llamar.
```

### C. Comandos de Prueba Manual (Depuración)
Si el código lo permite (o si cargas un código de "Serial Relay"), puedes enviar comandos AT directamente. Aquí los más útiles:

| Comando | Función | Respuesta Esperada |
| :--- | :--- | :--- |
| `AT` | Test de comunicación | `OK` |
| `AT+CSQ` | Calidad de señal | `+CSQ: 20,99` (El primer número debe ser mayor a 10) |
| `AT+CREG?` | Estado de registro en red | `+CREG: 0,1` (Registrado local) o `0,5` (Roaming) |
| `AT+COPS?` | Operador actual | `+COPS: 0,0,"Entel PCS"` (o tu operador) |
| `ATD+56912345678;` | Realizar llamada | `OK` ... (Audio de llamada) |
| `ATH` | Cortar llamada | `OK` |

> **Nota:** Si recibes `ERROR` o no hay respuesta, revisa que los cables TX y RX no estén invertidos y que la fuente externa esté encendida.

---

## 7. Solución de Problemas Comunes

*   **Pantalla Blanca:** Revisa conexiones SPI (SCK, MOSI, RES, DC). Asegúrate de usar 3.3V.
*   **Teclas no funcionan o marcan incorrecto:** Verifica el orden de los 8 pines de la teclera. El pin 1 es el de la derecha mirando el conector de frente.
*   **SIM no responde:**
    *   Asegúrate de haber activado la SIM antes en el teléfono.
    *   Asegúrate de que el módulo tenga alimentación externa de 5V (el USB del PC a veces no es suficiente).
    *   Verifica que TX del SIM vaya a RX del ESP32 y viceversa.
    *   Mantén presionado el botón PWR del módulo si el encendido por software falla.
*   **No hay audio:** Revisa la polaridad de los conectores JST del speaker y micrófono.

