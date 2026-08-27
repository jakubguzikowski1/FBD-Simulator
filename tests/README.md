# Tests

Automated tests are not included yet. Planned approach:

- **CTest** + GoogleTest or Catch2
- Focus on: `CFBDBuilder` parsing, `CConnection` wiring, block `calculate()` math (`Gain`, `AddSub`, `Integrator`)
- Keep tests under `tests/` and gate them with `BUILD_TESTING` in the root `CMakeLists.txt`

Contributions welcome once the CI skeleton is added.
