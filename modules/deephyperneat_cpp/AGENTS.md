# AGENTS.md (deephyperneat_cpp)

## Purpose
This module is a C++ port of the DeepHyperNEAT algorithm.

## How to work in this module
- Keep API-compatible names with the original conceptual modules (`genome`, `decode`, `population`, etc.).
- Prefer small, testable changes to evolutionary logic.
- Keep teaching comments at file top and add comments for non-obvious math decisions.

## Build and run
- Configure: `cmake -S /home/runner/work/DeepHyperNEAT/DeepHyperNEAT/modules/deephyperneat_cpp -B /home/runner/work/DeepHyperNEAT/DeepHyperNEAT/modules/deephyperneat_cpp/build`
- Build: `cmake --build /home/runner/work/DeepHyperNEAT/DeepHyperNEAT/modules/deephyperneat_cpp/build`
- Run example: `/home/runner/work/DeepHyperNEAT/DeepHyperNEAT/modules/deephyperneat_cpp/build/xor_example`

## Guardrails for future AIs
- Do not introduce external dependencies unless required by a clearly scoped feature.
- Keep decode API stable; improve internals behind the same signature.
- Preserve deterministic behavior where seeds are used.
