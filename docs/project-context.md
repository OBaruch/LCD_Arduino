# Project Context

[← Back to README](../README.md)

This document puts together everything the repository says about where the project came from. Each statement is tagged:

- **Confirmed**: directly supported by a file or by git history.
- **Inferred**: a reasonable deduction from the available evidence.
- **Unknown**: the repository does not give enough information.

## Available sources

The original repository has **only two files**:

| File | Type | Content |
|---|---|---|
| `LCD_ConInterrupciones.ino` | Source code | Arduino sketch, 39 lines, CRLF line endings |
| `LICENSE` | License | MIT License, "Copyright (c) 2021 Baruch Lopez" |

The repository has **no** PDFs, Word documents, presentations, images, diagrams, datasets, outputs or earlier README. All context below comes from the source code, the license and the git history.

## Git history (original)

| Commit | Date | Author | Message |
|---|---|---|---|
| `f101d31` | 2021-02-20 20:09:04 −06:00 | Baruch Lopez | Initial commit (LICENSE) |
| `125fb59` | 2021-02-20 20:09:26 −06:00 | Baruch Lopez | Add files via upload (the sketch) |

The sketch was uploaded through the GitHub web interface, 22 seconds after the repository was created. It was probably written earlier and published later as an archive. *(Inferred.)*

## Origin classification

**Classification: Academic / Coursework (embedded systems practice). Inferred, high confidence.**

Evidence:

| Evidence | Where | Supports |
|---|---|---|
| String `"Seminario de embebidos"` ("Embedded systems seminar") | Line 2 of message A | A course or seminar about embedded systems |
| A 9-digit number `"213605572"` | Line 1 of message B | A student ID *(Inferred from format and context)* |
| `"OMAR BARUCH M L"` | Line 2 of message B | Author name, matches `LICENSE` and the git author |
| An informal, profane message addressed to the instructor ("Profe") | Line 1 of message A | The display was meant to be shown to a teacher, as in a lab check-off |
| Shape of the program: one peripheral, one interrupt, two fixed states | Whole sketch | A typical short lab exercise on external interrupts |

## What can be stated

| Topic | Finding | Status |
|---|---|---|
| Author | Omar Baruch M. L. / Baruch Lopez | Confirmed |
| Course / seminar name | Text reads "Seminario de embebidos". The official course title is not given | Confirmed text / Unknown official title |
| University / institution | Not mentioned | Unknown |
| Semester / term | Not mentioned. The upload date is Feb 2021 | Unknown |
| Assignment statement / requirements | Not in the repository | Unknown |
| Learning goal | Using external interrupts (`attachInterrupt`) together with an I2C LCD | Inferred |
| Target board | Not stated. Pin 2 supports interrupts on Uno, Nano and Mega | Unknown (compatible boards inferred) |
| Library version | Not stated | Unknown |
| Trigger hardware on pin 2 | Not stated. Probably a push button with a pull-down resistor | Inferred |
| Whether the project was graded or finished | Not stated | Unknown |

## Scope

The project is small on purpose: one sketch, about 40 lines. It is not a product and not a library. Its value is as a record of an early embedded systems exercise that combines:

- the I2C peripheral (LCD backpack);
- external hardware interrupts;
- simple state held in a global flag.

## Contradictions and gaps

- The second line of message A (`"Seminario de embebidos"`, 22 characters) is longer than the 16-column display, so only the first 16 characters can be seen. The repository gives no sign whether this was intended. See [code-overview.md](code-overview.md#display-output).
- No other contradictions were found. The project has only one source of truth, the sketch.

## A note on displayed content

The original sketch contains an informal message with profanity and a personal student ID. These are kept as they are, because this repository preserves the original implementation. The documentation describes this content without repeating the profanity.
