# Code Overview

[← Back to README](../README.md)

This document explains the original sketch [`src/LCD_ConInterrupciones/LCD_ConInterrupciones.ino`](../src/LCD_ConInterrupciones/LCD_ConInterrupciones.ino) **without changing it**. Line numbers refer to the original file.

## File summary

| Property | Value |
|---|---|
| Language | Arduino C/C++ (`.ino`) |
| Lines | 39 |
| Line endings | CRLF (Windows) |
| External dependency | `LiquidCrystal_I2C.h` |
| Global state | `LiquidCrystal_I2C lcd`, `bool p` |
| Functions | `setup()`, `loop()`, `cambiarEstado()` (ISR) |

## Structure

### Includes and globals (lines 2–6)

```cpp
#include <LiquidCrystal_I2C.h> // Libreria LCD_I2C
LiquidCrystal_I2C lcd(0x27,16,2); // ... (0x3f,16,2) || (0x27,16,2) ||(0x20,16,2)
bool p=1;
```

- `lcd`: a 16-column × 2-row LCD at I2C address `0x27`. The Spanish comment says: "if it doesn't work with this address you can use `0x3F`, `0x27` or `0x20`". These are the usual addresses of PCF8574/PCF8574A I2C backpacks.
- `p`: the display-state flag. `1` selects message A and `0` selects message B. It starts at `1`.

### `setup()` (lines 8–13)

| Call | Purpose |
|---|---|
| `lcd.init()` | Starts I2C and the LCD controller |
| `lcd.backlight()` | Turns the backlight on |
| `attachInterrupt(digitalPinToInterrupt(2), cambiarEstado, RISING)` | Runs `cambiarEstado` on every LOW→HIGH transition on digital pin 2 |

`pinMode(2, …)` is never called, so pin 2 stays at its default `INPUT` mode (no internal pull-up).

### `loop()` (lines 15–34)

Each pass checks `p` twice, once for each state:

| Condition | Row 0 (col 0) | Row 1 (col 0) | Then |
|---|---|---|---|
| `p == 1` | Informal, profane message addressed to the instructor (13 chars, source line 19) | `"Seminario de embebidos"` | `delay(300)` |
| `p == 0` | `"213605572"` (student ID) | `"OMAR BARUCH M L"` | `delay(300)` |

Each branch calls `lcd.clear()` before it writes, so the screen is fully redrawn about every 300 ms.

### `cambiarEstado()` (lines 37–39)

```cpp
void cambiarEstado (){
  p = !p;
}
```

This is the interrupt service routine. The name is Spanish for "change state". It flips the flag. The next time `loop()` reads `p`, the other message is drawn.

## Execution flow

```
power-on
   │
   ▼
setup ── lcd.init ── lcd.backlight ── attachInterrupt(pin 2, RISING → cambiarEstado)
   │
   ▼
┌───────────────── loop ─────────────────┐
│  p==1 ? draw message A, wait 300 ms    │◄──────┐
│  p==0 ? draw message B, wait 300 ms    │       │
└────────────────────────────────────────┘       │
                                                 │
   rising edge on pin 2 ──► cambiarEstado: p = !p ┘  (asynchronous)
```

## Display output

The LCD shows 16 columns per row. HD44780-compatible controllers keep up to 40 characters per row in memory, so text past column 16 is stored but not shown when the display is not scrolled. *(Inferred from how the hardware normally behaves; not verified on the original hardware.)*

| State | Row 0 (visible) | Row 1 (visible) |
|---|---|---|
| `p == 1` | Instructor message (13 chars incl. 3 leading spaces, fits) | `Seminario de emb` (first 16 of 22 chars) |
| `p == 0` | `213605572` | `OMAR BARUCH M L` |

## Inferred hardware setup

The repository has no schematic. Based on the code alone:

| Component | Connection | Status |
|---|---|---|
| Arduino board with an interrupt on pin 2 (e.g. Uno / Nano / Mega) | — | Inferred |
| 16×2 LCD + I2C backpack | VCC, GND, SDA, SCL → board I2C pins | Inferred |
| Push button (or another digital source) | Pin 2, with an external pull-down resistor to GND and the button to VCC (needed for clean `RISING` edges without `INPUT_PULLUP`) | Inferred |

## Dependencies observed

- **`LiquidCrystal_I2C`**. The `init()` method (instead of `begin()`) matches the widely used Arduino `LiquidCrystal_I2C` library family. The exact fork and version are **Unknown**.
- **Arduino core**: `attachInterrupt`, `digitalPinToInterrupt`, `delay`.

No other files, headers or configuration take part in the build.
