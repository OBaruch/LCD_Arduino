# Intent

[← Back to README](../../README.md) · **Intent** · [Spec](spec.md) · [Plan](plan.md)

> **Retroactive artifact.** This intent was reconstructed in 2026 from the existing repository. It records *why* the project existed, as far as the evidence shows. It was **not** written when the project was built. Statements are tagged **Confirmed**, **Inferred** or **Unknown**.

## 1. Original project intent (2021)

### Problem

An embedded systems course ("Seminario de embebidos", **Confirmed** as text in the code) needed a way to show that a microcontroller program can respond to external events **asynchronously**, through hardware interrupts, instead of polling. *(Inferred.)*

### Desired outcome

A working Arduino circuit where pressing an input (on pin 2) instantly changes what a 16×2 I2C LCD shows, switching between:

- a message about the course, and
- the student's identification (student ID and name).

This proves both the interrupt handling and the LCD integration to the instructor. *(Inferred.)*

### Stakeholders

| Stakeholder | Interest | Status |
|---|---|---|
| Student / author (Omar Baruch M. L.) | Complete and demonstrate the practice | Confirmed author, inferred role |
| Course instructor | Check that the practice works and who did it | Inferred |

### Success criteria (inferred)

1. The LCD starts up and shows text when powered on.
2. A rising edge on pin 2 switches the displayed message.
3. The student's ID and name can be shown on the display as proof of authorship.

### Non-goals

- Robust input handling (debouncing, pull-ups)
- Reusable library code
- Configurability or persistence

*(Inferred from what the code does and does not do.)*

## 2. Repository modernization intent (2026)

### Problem

The repository had one sketch file at the root, no README and no context. Anyone visiting it, including the author years later, could not tell what it was, why it existed or how to run it.

### Desired outcome

A clear, navigable, portfolio-ready repository that:

- keeps the original sketch **byte-for-byte**;
- explains the project's context, behaviour and inferred hardware;
- separates confirmed facts, inferences and unknowns;
- records possible improvements without applying them.

### Hard constraint

> **Modernize the repository, not the project.** The source code must not be edited, reformatted, re-encoded or renamed.

### Success criteria

1. `sha256sum` of the sketch matches the original: `3678b01cdd5f937708459a360ae461a7e794ff07a0cddbf4473e77393a130d52`.
2. `git log --follow` shows the sketch as a rename of the original upload.
3. A reader can understand the project from `README.md` alone.
4. No invented facts. Every claim is tagged or traceable to a file.
5. No unnecessary tooling (no CI, Docker, build systems or linters).
