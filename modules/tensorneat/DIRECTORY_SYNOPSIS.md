# Directory Synopsis: tensorneat

## `src/tensorneat/`
Core Python package implementing algorithms (`algorithm`), genomes (`genome`), reusable utilities (`common`), optimization pipeline (`pipeline.py`), and problem definitions (`problem`).

## `examples/`
Runnable usage examples by environment/domain:
- `func_fit/` for supervised function fitting (XOR variants).
- `gymnax/`, `brax/`, and `mujoco_playground/` for RL benchmarks.
- `interpret_visualize/` for symbolic and visualization workflows.
- `with_evox/` for EvoX integration examples.

## `test/`
Regression checks, experiments, and benchmark scripts covering mutation/crossover, genome behavior, and runtime characteristics.

## `docs/`
Sphinx documentation configuration plus generated module-level API pages.

## `tutorials/`
Notebook-based walkthroughs and related artifacts for onboarding and experimentation.

## `imgs/`
Static assets and generated visualization outputs used by documentation and README examples.

## `.github/workflows/`
Packaging/publishing automation for PyPI release workflows.
