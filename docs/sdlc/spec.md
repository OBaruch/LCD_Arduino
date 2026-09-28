# Specification

[← Back to README](../../README.md) · [Intent](intent.md) · **Spec** · [Plan](plan.md)

> **Reverse-engineered specification.** This spec describes the behaviour of the **existing** sketch `src/LCD_ConInterrupciones/LCD_ConInterrupciones.ino` as it is. It is not a design for new work. Where the code and a sensible reading of "intended" behaviour differ, the spec records the **actual** behaviour and flags the difference.

## 1. System overview

| Item | Value |
|---|---|
| Platform | Arduino (board model Unknown; needs an interrupt-capable pin 2) |
| Language | Arduino C/C++ |
| Dependency | `LiquidCrystal_I2C` (version Unknown) |
| Peripherals | 16×2 character LCD on an I2C backpack; one digital input on pin 2 |

## 2. Hardware interface

| ID | Interface | Specification | Source |
|---|---|---|---|
| HW-1 | LCD | I2C address `0x27`, 16 columns × 2 rows | Code, line 5 |
| HW-2 | LCD alt. addresses | `0x3F` or `0x20` if `0x27` fails (manual code change) | Comment, line 5 |
| HW-3 | Input | Digital pin 2, external interrupt, `RISING` edge | Code, line 11 |
| HW-4 | Input electrical mode | Default `INPUT` (floating). An external pull-down is needed for correct operation | Inferred (no `pinMode`) |

## 3. State model

| State | Flag `p` | Row 0 text | Row 1 text |
|---|---|---|---|
| **A** (initial) | `1` | Instructor message (13 chars) | `Seminario de embebidos` |
| **B** | `0` | `213605572` | `OMAR BARUCH M L` |

```
          rising edge on pin 2
   ┌────────────────────────────────┐
   ▼                                │
 [ A ] ──── rising edge on pin 2 ──► [ B ]
 (initial)
```

## 4. Functional requirements (as implemented)

| ID | Requirement | Implementation |
|---|---|---|
| FR-1 | At start-up the system shall start the LCD and turn on its backlight | `lcd.init(); lcd.backlight();` |
| FR-2 | At start-up the system shall register an ISR for rising edges on pin 2 | `attachInterrupt(digitalPinToInterrupt(2), cambiarEstado, RISING)` |
| FR-3 | The system shall start in state A | `bool p=1;` |
| FR-4 | While in state A, the system shall clear the LCD and write the state A texts at column 0 of rows 0 and 1 | `loop()`, lines 16–23 |
| FR-5 | While in state B, the system shall clear the LCD and write the state B texts at column 0 of rows 0 and 1 | `loop()`, lines 24–31 |
| FR-6 | After each redraw the system shall wait 300 ms | `delay(300)` |
| FR-7 | On every rising edge on pin 2 the system shall toggle between A and B | `cambiarEstado(): p = !p;` |

## 5. Observed behaviour and deviations

| ID | Observation | Status |
|---|---|---|
| OB-1 | The row 1 text of state A is 22 characters. Only the first 16 (`Seminario de emb`) are visible | Actual behaviour (inferred from display geometry) |
| OB-2 | The display is cleared and redrawn about every 300 ms even without a state change, which may cause flicker | Actual behaviour |
| OB-3 | Without debouncing, one button press may produce several edges and toggles | Likely in practice (inferred) |
| OB-4 | `p` is not `volatile`. With the observed code shape it usually works on AVR, but this is not guaranteed | Code observation |
| OB-5 | In one `loop()` pass, if the ISR fires between the two `if` checks, both branches may run in the same pass | Code observation |

## 6. Non-functional characteristics

| Aspect | Characteristic |
|---|---|
| Latency of state change → display | Up to about 300 ms (one `delay`) plus redraw time |
| Memory / footprint | Small. One global object and one flag |
| Configurability | None at run time. The I2C address is set at compile time |
| Persistence | None. The state resets to A on every reset |

## 7. Out of scope

Serial output, EEPROM, networking, multiple inputs, menus, scrolling text, power management.

## 8. Acceptance checks (for the original sketch)

1. The sketch compiles in the Arduino IDE with a `LiquidCrystal_I2C` library that provides `init()`.
2. After power-on, state A text appears on the LCD.
3. One clean rising edge on pin 2 shows state B. Another one returns to state A.
