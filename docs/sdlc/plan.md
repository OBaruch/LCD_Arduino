# Plan

[← Back to README](../../README.md) · [Intent](intent.md) · [Spec](spec.md) · **Plan**

This plan has two parts:

1. **Original implementation plan (reconstructed)**: how the sketch was most likely built, inferred from its final form. No original plan exists.
2. **Repository modernization plan (executed)**: the steps actually taken in 2026 to reorganize and document the repository without touching the code.

---

## Part 1: Original implementation plan (reconstructed, 2021)

> Inferred from the structure of the final code. The real development order is **Unknown**.

| Step | Task | Result in code |
|---|---|---|
| 1 | Wire a 16×2 LCD with an I2C backpack to the Arduino | — |
| 2 | Find the LCD's I2C address (common candidates `0x27`, `0x3F`, `0x20`) | Address `0x27` chosen. Alternatives kept in a comment (line 5) |
| 3 | Start the LCD and show static text | `lcd.init()`, `lcd.backlight()`, `setCursor` / `print` |
| 4 | Add a global flag for the display state | `bool p=1;` |
| 5 | Write the two display branches in `loop()` | Two `if` blocks with `clear` / `print` / `delay(300)` |
| 6 | Wire an input to pin 2 and attach an ISR on the rising edge | `attachInterrupt(digitalPinToInterrupt(2), cambiarEstado, RISING)` |
| 7 | Put the toggle logic in the ISR | `cambiarEstado(): p = !p;` |
| 8 | Show it to the instructor; state B shows the student ID and name | Strings on lines 27 and 29 |
| 9 | Publish to GitHub | Commits `f101d31`, `125fb59` (2021-02-20) |

---

## Part 2: Repository modernization plan (executed, 2026)

### Guiding principle

> Modernize the repository, not the project.

### Steps

| # | Task | Output | Status |
|---|---|---|---|
| 1 | Inventory every file and the git history | Two files: sketch + MIT license. No docs, media or data | Done |
| 2 | Recover context from code strings, comments, license and commits | [project-context.md](../project-context.md) | Done |
| 3 | Classify the origin with evidence (Confirmed / Inferred / Unknown) | Academic / Coursework (Inferred) | Done |
| 4 | Move the sketch to `src/LCD_ConInterrupciones/` using `git mv`, keeping the IDE folder = sketch-name rule | Pure rename, SHA-256 unchanged | Done |
| 5 | Protect original bytes (CRLF) from line-ending normalization | `.gitattributes` (`*.ino -text`) | Done |
| 6 | Document the code without changing it | [code-overview.md](../code-overview.md) | Done |
| 7 | Record improvements separately and **do not apply them** | [possible-improvements.md](../possible-improvements.md) | Done |
| 8 | Write the reconstructed intent, spec and plan | `docs/sdlc/` | Done |
| 9 | Add contribution guardrails for human and automated contributors | [AGENTS.md](../../AGENTS.md) | Done |
| 10 | Write a professional README with navigation | [README.md](../../README.md) | Done |
| 11 | Add a minimal `.gitignore` for Arduino/IDE artifacts | `.gitignore` | Done |
| 12 | Deliver on a dedicated branch through a pull request | Branch `docs/repository-refactor` | Done |

### Deliberately not done

- No change to the sketch's content, encoding, line endings or file name.
- No CI/CD, Docker, build system (PlatformIO, Makefile), linters or tests. They were not part of the original project.
- No `data/`, `assets/` or `examples/` folders. The project has no such content.
- No `architecture.md`. A single 39-line sketch has no meaningful architecture beyond what [code-overview.md](../code-overview.md) covers.

### Verification

```bash
# 1. Original bytes preserved
sha256sum src/LCD_ConInterrupciones/LCD_ConInterrupciones.ino
# expected: 3678b01cdd5f937708459a360ae461a7e794ff07a0cddbf4473e77393a130d52

# 2. History followed across the move
git log --follow --oneline -- src/LCD_ConInterrupciones/LCD_ConInterrupciones.ino

# 3. Blob identical to the original upload
git diff --stat 125fb59 HEAD -M -- LCD_ConInterrupciones.ino src/LCD_ConInterrupciones/LCD_ConInterrupciones.ino
```
