# Directory Synopsis: deephyperneat_cpp

## `include/deephyperneat/`
Public API headers grouped by conceptual subsystem:
- `activations.hpp`: activation function registry used by genes and phenomes.
- `util.hpp`: shared statistics helpers.
- `phenomes.hpp`: executable feed-forward neural representations.
- `genome.hpp`: genotype representation and mutation operators.
- `species.hpp`: compatibility-distance based species grouping.
- `stagnation.hpp`: species stagnation filtering logic.
- `reproduction.hpp`: new generation construction.
- `decode.hpp`: CPPN-to-substrate decoding boundary.
- `population.hpp`: top-level evolutionary loop.
- `reporters.hpp`: textual progress reporting.
- `visualize.hpp`: visualization output hook.

## `src/`
Implementation files matching one-to-one with public headers.

## `examples/`
Runnable demonstration programs; currently `xor_main.cpp` mirrors the XOR task flow.
