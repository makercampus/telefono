# Módulo Sim A7670G - CAT1_A767X

![alt text](../../A7670.png)


# MUY IMPORTANTE ACTIVAR SIM ANTES, PONERLA EN EL CELULAR Y MARCAR *103#

![alt text](<../../chip claro prepago.png>)

## Detalles
La rejilla se desbloquea primero y luego se levanta para poner la sim.
La sim va con el chip hacia abajo (cara/marca hacia arriba) y en una esquina está marcado donde va la parte doblada/hundida

## Chequeo básico del módem y SIM
> Todo esto en el monitor serial con 115200 baud y Both NL & CR.

- **`AT`**  
  - Bueno: `OK` → módem vivo.  
  - Malo: nada/basura → baud, pines o alimentación mal.

- **`AT+CPIN?`**  
  - Bueno: `+CPIN: READY` → SIM presente y sin PIN.  
  - Malo: `SIM PIN` → falta `AT+CPIN="1234"`.  
  - Malo: `SIM not inserted` / `SIM failure` → SIM mal puesta o dañada.

## Red y señal

- **`AT+CREG?`** (voz 2G/3G)  
  - Bueno: `+CREG: 0,1` o `0,5` → registrado (local/roaming).  
  - Malo: `+CREG: 0,0` → no registrado.  
  - Causas malas: sin cobertura, SIM solo datos (sin voz), bandas/modo mal, antena mala.

- **`AT+CEREG?`** (LTE)  
  - Bueno: `+CEREG: 0,1` o `0,5` → LTE OK.  
  - Excepción: `0,11` → solo servicio limitado/emergencia, no normal.

- **`AT+CSQ`** (señal)  
  - Bueno: `+CSQ: 10–31, y` → señal aceptable.  
  - Malo: `+CSQ: 99,99` → sin señal / sin registro.

## Llamada saliente

- **Llamar:**  
  - Comando: `ATD+569XXXXXXXX;`  
  - Bueno: el otro teléfono suena, luego `NO CARRIER` al colgar.  
  - Malo típico:  
    - `+CME ERROR: no network service` → sin servicio de voz (no registrado, SIM solo datos, bandas/modo mal).  
    - `operation not allowed` → operador/SIM bloquea voz.

- **Colgar:**  
  - Comando: `AT+CHUP`  
  - Bueno: corta la llamada (o `OK` si no hay llamada).  

## Recibir llamada

- Requisito: `AT+CREG?` debe dar `0,1` o `0,5` y la SIM debe tener voz.  
- Al entrar llamada: aparece `RING` (y opcional `+CLIP` si está activado).  
- Para contestar: `ATA`.  
- Si nunca hay `RING`: no está registrado en voz o la SIM no tiene servicio de voz.

