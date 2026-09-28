# LCD_Arduino — Interrupt-Driven I2C LCD Message Toggle

An Arduino sketch that shows one of two two-line messages on a 16×2 I2C LCD and switches between them each time an external interrupt fires on digital pin 2.

> **Original implementation notice.** This repository keeps the original implementation of the project. The source code has deliberately not been refactored or modernized, so it still shows the historical context and the original development approach. The source code is the original implementation, developed during my university studies.

---

## Project Overview

The whole project is one Arduino sketch, [`LCD_ConInterrupciones.ino`](src/LCD_ConInterrupciones/LCD_ConInterrupciones.ino). The file name is Spanish for "LCD with interrupts". The sketch:

1. starts a 16×2 character LCD through an I2C backpack (address `0x27`);
2. attaches an interrupt service routine (ISR) to digital pin 2 on the rising edge;
3. in the main loop, redraws the screen about every 300 ms with one of two messages, chosen by a boolean flag;
4. flips that flag inside the ISR, so each rising edge on pin 2 changes the message.

## Project Context

| Item | Value | Status |
|---|---|---|
| Project type | Academic / Coursework (embedded systems practice) | **Inferred**. The sketch prints `Seminario de embebidos` ("Embedded systems seminar"), a student ID and the author's name |
| Course | "Seminario de embebidos" (embedded systems seminar) | **Confirmed** as text in the code. The official course name is **Unknown** |
| University | Not stated anywhere in the repository | **Unknown** |
| Author | Omar Baruch M. L. (Baruch Lopez) | **Confirmed** (source strings, `LICENSE`, git history) |
| Date | Uploaded to GitHub on 2021-02-20 | **Confirmed** (git history). The exact writing date is **Unknown** |
| Language of the original | Spanish (identifiers, comments, displayed text) | **Confirmed** |

See [docs/project-context.md](docs/project-context.md) for the full evidence.

## Problem Statement

Show how to use **external hardware interrupts** on an Arduino to change what a program does asynchronously. Here, the interrupt switches the content of an I2C LCD. The main loop never polls the input pin. *(Inferred from the code. No assignment statement is in the repository.)*

## Objective

Show two different messages on the LCD and switch between them with a hardware interrupt. One message has the course name, the other has the student ID and name. This looks like evidence of a completed lab practice. *(Inferred.)*

## Repository Structure

```
LCD_Arduino/
├── README.md                      ← this file
├── LICENSE                        ← MIT License (original)
├── AGENTS.md                      ← contribution guardrails (preserve original code)
├── .gitattributes                 ← keeps the original sketch byte-for-byte (CRLF)
├── .gitignore
├── src/
│   └── LCD_ConInterrupciones/
│       └── LCD_ConInterrupciones.ino   ← original sketch (unchanged)
└── docs/
    ├── project-context.md         ← origin, evidence, confirmed / inferred / unknown
    ├── code-overview.md           ← line-by-line behaviour and inferred hardware
    ├── possible-improvements.md   ← observations only; NOT applied
    └── sdlc/
        ├── intent.md              ← why the project exists (reconstructed)
        ├── spec.md                ← what it does (reverse-engineered spec)
        └── plan.md                ← how it was built + how the repo was reorganized
```

The sketch sits inside a folder with the same name (`src/LCD_ConInterrupciones/`) because the Arduino IDE requires a sketch to live in a directory that matches its file name.

## Original Implementation

The sketch file has the **exact bytes** of the 2021 upload: the same logic, Spanish identifiers, comments, CRLF line endings, displayed text, and any bugs or informal wording. Git records the file as a pure rename, and its SHA-256 did not change:

```
3678b01cdd5f937708459a360ae461a7e794ff07a0cddbf4473e77393a130d52  LCD_ConInterrupciones.ino
```

Code observations and possible improvements are in [docs/possible-improvements.md](docs/possible-improvements.md). They were **not** applied.

## Technologies

| Technology | Evidence |
|---|---|
| Arduino (C/C++ `.ino` sketch) | File extension, `setup()` / `loop()`, `attachInterrupt`, `digitalPinToInterrupt`, `delay` |
| `LiquidCrystal_I2C` library | `#include <LiquidCrystal_I2C.h>` and the calls `lcd.init()` / `lcd.backlight()` |
| 16×2 character LCD with I2C (PCF8574-style) backpack | Constructor `LiquidCrystal_I2C lcd(0x27,16,2)` and the comment listing the common addresses `0x3F`, `0x27`, `0x20` |
| External hardware interrupt on pin 2 | `attachInterrupt(digitalPinToInterrupt(2), cambiarEstado, RISING)` |

The exact board model and the library version are **Unknown**. Pin 2 can trigger interrupts on common boards such as the Uno, Nano and Mega. *(Inferred.)*

## How It Works

```
setup():  lcd.init() → lcd.backlight() → attach ISR "cambiarEstado" to pin 2 (RISING)

loop():   if p == 1 → clear, row 0: instructor message, row 1: "Seminario de embebidos", wait 300 ms
          if p == 0 → clear, row 0: student ID,         row 1: "OMAR BARUCH M L",        wait 300 ms

ISR cambiarEstado():  p = !p        (runs on every rising edge on pin 2)
```

The details, including the text as it appears on the 16-column display, are in [docs/code-overview.md](docs/code-overview.md).

## Inputs and Outputs

| Direction | Signal | Notes |
|---|---|---|
| Input | Digital pin 2, rising edge | Probably a push button. The pin has no `pinMode`, so the wiring must include an external pull-down resistor *(Inferred)* |
| Output | 16×2 LCD over I2C (SDA/SCL, address `0x27`) | Two messages that alternate |

## Running the Project

The repository has no build configuration, wiring diagram or board definition. The steps below are the standard Arduino workflow implied by the file type. They are not instructions taken from the original project.

1. Open `src/LCD_ConInterrupciones/LCD_ConInterrupciones.ino` in the Arduino IDE.
2. Install a `LiquidCrystal_I2C` library that provides `init()` and `backlight()`. The original library version is **Unknown**.
3. Wire the LCD backpack to the board's I2C pins and a trigger source to digital pin 2.
4. If nothing appears on the display, try the alternative I2C addresses listed in the sketch's comment (`0x3F`, `0x20`).
5. Select the board and port, then upload.

## Documentation

- [Project context](docs/project-context.md)
- [Code overview](docs/code-overview.md)
- [Possible improvements (not applied)](docs/possible-improvements.md)
- SDLC artifacts: [Intent](docs/sdlc/intent.md) · [Spec](docs/sdlc/spec.md) · [Plan](docs/sdlc/plan.md)

## Historical Note

The repository was later reorganized and documented to make it easier to read and to keep the historical context of the original project. The original source code is unchanged. The only change to it is its location in the repository.

## License

[MIT](LICENSE) © 2021 Baruch Lopez
