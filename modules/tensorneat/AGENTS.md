# AGENTS.md (tensorneat)

## Purpose
This module is the extracted TensorNEAT codebase (Python/JAX implementation) included as a sibling module in this monorepo.

## How to work in this module
- Preserve package structure rooted at `src/tensorneat`.
- Keep examples and tests aligned with public API updates.
- Document algorithm-level changes in `README.md` and `docs/source` when behavior changes.

## Typical workflows
- Install editable package from module root: `pip install -e .`
- Run focused tests from module root, e.g. `python -m pytest test/test_genome.py`

## Guardrails for future AIs
- Avoid mass formatting across unrelated files.
- Prefer targeted changes with test evidence.
- Treat this module as upstream-derived code; keep changes reviewable and clearly scoped.
