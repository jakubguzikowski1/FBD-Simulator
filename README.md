# FBD Simulator

**Desktop Function Block Diagram simulator for discrete-time signal processing — built with Modern C++17 and Qt 6 Widgets.**

A clean, layered educational/engineering tool inspired by industrial FBD (IEC 61131-3 style) diagrams: define blocks and connections in a text config, run a discrete simulation engine, and monitor live outputs from a Qt GUI.

[![C++](https://img.shields.io/badge/C%2B%2B-17-00599C?logo=cplusplus&logoColor=white)](https://isocpp.org/)
[![Qt](https://img.shields.io/badge/Qt-6%20Widgets-41CD52?logo=qt&logoColor=white)](https://www.qt.io/)
[![CMake](https://img.shields.io/badge/CMake-3.16%2B-064F8C?logo=cmake&logoColor=white)](https://cmake.org/)
[![Platform](https://img.shields.io/badge/platform-Windows%20%7C%20Linux%20%7C%20macOS-lightgrey)](#build--run)
[![License](https://img.shields.io/badge/license-MIT-green)](LICENSE)
[![Docs](https://img.shields.io/badge/docs-Doxygen-2C4AA8)](#documentation-doxygen)

> **PL:** Symulator diagramów bloków funkcyjnych (FBD) — silnik dyskretnej symulacji sygnałów + GUI Qt. Projekt zaliczeniowy z naciskiem na czysty podział warstw i Modern CMake.

---

## Preview

![FBD Simulator demo](docs/screenshots/demo.png)

*Add a screenshot or short GIF of the Control Panel + Monitoring view to `docs/screenshots/demo.png`.*

---

## Elevator pitch

Instead of wiring blocks only on a canvas, this project models an **FBD as a graph of typed function blocks** owned by a container, driven by a **step-based simulation engine**, and observed through a **thin Qt Widgets UI**. Configuration is declarative (`config.txt`); the core engine stays UI-agnostic — the same pattern you want in real SCADA / PLC tooling.

---

## Key features

| Area | What you get |
|------|----------------|
| **Qt GUI** | Start / Pause / Stop / Step, sampling & max-steps controls, live step/time monitoring, dynamic parameter tweaks (`Const`, `Gain`) |
| **FBD model** | Named blocks + point-to-point connections with pin indices |
| **Simulation engine** | Discrete-time loop with lifecycle hooks: `beforeSim` → `initialize` → `calculate` → `afterSimStep` → `afterSim` |
| **Signal model** | `SDataSample` with value, quality (`ok` / `bad`), and `STimeStamp` |
| **Config DSL** | Human-readable `SAMPLING` / `BLOCK` / `CONNECT` file parsed by `CFBDBuilder` |
| **Block library** | Sources, processing blocks, and sinks (see below) |
| **Validation** | Config parse errors (unknown commands, missing args, unknown block names) surfaced as exceptions / message boxes |

### Built-in function blocks

| Block | Role | Notes |
|-------|------|--------|
| `Const` | Source | Constant value |
| `PeriodicGenerator` | Source | Amplitude + frequency (sine-like periodic signal) |
| `FileRead` | Source | Reads samples from a file |
| `Gain` | Processing | Multiplies input by gain |
| `AddSub` | Processing | Multi-input add/subtract via sign string (e.g. `++`, `+-`) |
| `Integrator` | Processing | Discrete integration over sampling period |
| `FileWrite` | Sink | Writes samples to CSV / file |

---

## Architecture

Layered design: **interfaces → IO → blocks → engine → GUI**. The UI depends on the engine; the engine does not depend on Qt widgets beyond the application entry point.

```text
┌─────────────────────────────────────────────────────────┐
│  MainWindow (Qt Widgets)                                │
│  controls · monitoring · parameter injection            │
└──────────────────────────▲──────────────────────────────┘
                           │ dependency injection
┌──────────────────────────┴──────────────────────────────┐
│  Engine                                                 │
│  CSimEngine  ·  CContainerFBD  ·  CFBDBuilder           │
└──────────────────────────▲──────────────────────────────┘
                           │ owns / orchestrates
┌──────────────────────────┴──────────────────────────────┐
│  Blocks (Source / Processing / Sink hierarchy)          │
│  CConst · CGain · CAddSub · CIntegrator · …             │
└──────────────────────────▲──────────────────────────────┘
                           │ pins & wires
┌──────────────────────────┴──────────────────────────────┐
│  IO + Interfaces                                        │
│  CInput / COutput / CConnection                         │
│  ICFunctionBlock · ICInput · ICOutput · ICConnection    │
└─────────────────────────────────────────────────────────┘
                           ▲
                     core/DataTypes.h
                     (STimeStamp, SDataSample)
```

### Design patterns & principles

- **Dependency Injection** — `MainWindow` receives `CContainerFBD*` and `CSimEngine*` (no global simulation singleton).
- **Strategy / Polymorphism** — all blocks implement `ICFunctionBlock` and share a common simulation lifecycle.
- **Template Method (inheritance)** — `CFunctionBlockBase` → `CSourceBase` / `CProcessingBlock` / `CSinkBase` → concrete blocks.
- **Builder** — `CFBDBuilder` constructs the graph from a text configuration.
- **Separation of Concerns** — simulation core is independent of presentation; Qt is a thin control/monitor layer (MVC-like, engine as Model/Controller).

### Repository layout

```text
FBD_Simulator/
├── CMakeLists.txt          # Modern CMake (target-based)
├── config.txt              # Sample FBD diagram
├── Doxyfile                # API documentation generator
├── LICENSE
├── README.md
├── docs/
│   └── screenshots/        # demo.png / GIF for README
└── src/
    ├── main.cpp
    ├── MainWindow.h/.cpp   # Qt GUI
    ├── core/               # Shared value types
    ├── interfaces/         # Pure abstract APIs
    ├── io/                 # Pins & connections
    ├── blocks/             # Function block hierarchy
    └── engine/             # Container, builder, sim loop
```

---

## Requirements

| Dependency | Version |
|------------|---------|
| C++ compiler | C++17 (MSVC 2019+, GCC 9+, Clang 10+) |
| CMake | 3.16+ |
| Qt | **6.x** with **Widgets** module |
| Doxygen *(optional)* | 1.9+ for API docs |
| Graphviz *(optional)* | for Doxygen call/collaboration graphs |

---

## Build & run

### 1. Clone

```bash
git clone https://github.com/<your-username>/FBD-Simulator.git
cd FBD-Simulator
```

### 2. Configure & build (out-of-source)

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release
```

> **Windows + Qt:** if CMake cannot find Qt, pass the prefix, e.g.  
> `cmake -S . -B build -DCMAKE_PREFIX_PATH="C:/Qt/6.x.x/msvc2022_64"`

### 3. Run

The sample `config.txt` must be in the **working directory** (or adjust the path in `main.cpp`).

```bash
# From repo root (so config.txt is found)
./build/FBDSimulator          # Linux / macOS
.\build\Release\FBDSimulator.exe   # MSVC multi-config
.\build\FBDSimulator.exe           # Ninja / single-config
```

### Sample `config.txt`

```text
# Sampling period in milliseconds
SAMPLING 100

BLOCK Const const1 2.5
BLOCK PeriodicGenerator gen1 1.0 0.5
BLOCK AddSub sum1 ++
BLOCK Gain gain1 3.0
BLOCK Integrator int1
BLOCK FileWrite sink1 output.csv

CONNECT const1 0 sum1 0
CONNECT gen1 0 sum1 1
CONNECT sum1 0 gain1 0
CONNECT gain1 0 int1 0
CONNECT int1 0 sink1 0
```

**Grammar**

| Directive | Syntax |
|-----------|--------|
| Sampling | `SAMPLING <ms>` |
| Block | `BLOCK <Type> <Name> [params...]` |
| Connection | `CONNECT <SrcBlock> <SrcOutIdx> <DstBlock> <DstInIdx>` |
| Comment | lines starting with `#` |

---

## Documentation (Doxygen)

Public headers are annotated with Doxygen (`@brief`, `@param`, `@return`). Generate HTML docs:

```bash
doxygen Doxyfile
```

Output: `docs/html/index.html` (open in a browser).

---

## Roadmap / ideas

- [ ] Visual canvas editor for blocks & wires  
- [ ] Connection validation (type checks, fan-out rules, cycle detection)  
- [ ] Unit tests (`tests/`) with CTest  
- [ ] Plot widgets for output traces  
- [ ] Optional C++20 (`std::span`, concepts) migration  

---

## Author

**Jakub Guzikowski** — university project (PROG2) refined as a portfolio showcase for Modern C++, Qt, and clean layered architecture.

---
