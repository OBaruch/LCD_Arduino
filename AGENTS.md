# Contribution Guidelines (humans and automated agents)

This repository is a **historical archive** of an original Arduino project. Anyone contributing must follow these rules, whether a person or an automated coding agent.

## Hard rules

1. **Do not modify** anything under `src/`. This covers logic, formatting, comments, identifiers, encoding and CRLF line endings.
2. The original sketch must keep this SHA-256:
   `3678b01cdd5f937708459a360ae461a7e794ff07a0cddbf4473e77393a130d52`
3. Do not apply the items in [`docs/possible-improvements.md`](docs/possible-improvements.md) to the original sketch. Any modernized version must go in a new, clearly labelled location.
4. Do not add build or infrastructure tooling (CI, Docker, PlatformIO, linters, tests) unless there is a documented reason.
5. Documentation must tag claims as **Confirmed**, **Inferred** or **Unknown**, and must not invent context.

## Where things live

| Path | Purpose |
|---|---|
| `src/LCD_ConInterrupciones/` | Original sketch (read-only) |
| `docs/` | Context, code overview, improvement notes |
| `docs/sdlc/` | Intent → Spec → Plan artifacts |

## Workflow

Intent ([`docs/sdlc/intent.md`](docs/sdlc/intent.md)) → Spec ([`docs/sdlc/spec.md`](docs/sdlc/spec.md)) → Plan ([`docs/sdlc/plan.md`](docs/sdlc/plan.md)) → change on a branch → pull request. Update these artifacts when the scope of the repository changes.
