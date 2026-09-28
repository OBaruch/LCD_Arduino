# Possible Improvements (Not Applied)

[← Back to README](../README.md)

> **Important:** None of these improvements were applied. The sketch in `src/` is kept exactly as it was first written, to preserve its historical context. This list only records what a modern review would point out.

## Correctness

| # | Observation | Why it matters | Possible change |
|---|---|---|---|
| 1 | `bool p` is changed inside an ISR but is not declared `volatile` | The compiler may cache `p` in a register inside `loop()`, so changes made by the ISR might not be seen reliably | `volatile bool p = 1;` |
| 2 | No debouncing on pin 2 | Mechanical bounce causes several rising edges per press, so `p` may flip an even number of times and the message looks like it did not change | Ignore edges within about 50 ms of the last one, using `millis()` in the ISR, or add hardware RC debouncing |
| 3 | `pinMode(2, …)` is never set, and no internal pull-up is used | A floating input causes false interrupts unless an external pull-down resistor is fitted | `pinMode(2, INPUT_PULLUP)` with the button to GND and `FALLING`, or document the external resistor |
| 4 | `"Seminario de embebidos"` is 22 characters on a 16-column display | Only `Seminario de emb` is visible | Shorten the text, or scroll it |

## Design / style

| # | Observation | Possible change |
|---|---|---|
| 5 | The screen is cleared and redrawn every 300 ms even when nothing changed, which can cause visible flicker | Redraw only when `p` changes (keep the last drawn state) |
| 6 | Two separate `if` blocks instead of `if / else` | `if (p) { … } else { … }` |
| 7 | One-letter global name `p` | A descriptive name, for example `showCourseMessage` |
| 8 | `delay(300)` blocks the loop | A `millis()`-based non-blocking loop, or no delay once item 5 is done |
| 9 | Hard-coded I2C address with alternatives only in a comment | A named constant, or an I2C scanner at start-up |

## Content

| # | Observation | Possible change |
|---|---|---|
| 10 | Message A has informal language with profanity, and message B shows a personal student ID | For a public or demo version, use neutral text and no personal identifiers |

## Repository-level (not code)

| # | Observation | Possible change |
|---|---|---|
| 11 | No wiring diagram or photo of the original circuit | Add a Fritzing or hand-drawn schematic under `docs/` if the hardware can be rebuilt |
| 12 | The library version is not pinned | Record the tested `LiquidCrystal_I2C` version if the sketch is rebuilt |

---

If any of these are ever applied, they should go in a **separate, clearly labelled file or folder** (for example `src/LCD_ConInterrupciones_v2/`), so the original sketch stays untouched.
