# Satellite Telemetry Processing System

A multithreaded C++17 application that simulates a satellite downlink and processes the telemetry stream in real time. Built as a portfolio project demonstrating modern C++, concurrency, and a clean CMake-based workflow — oriented toward aerospace and defence software.

## Overview

The system models a **producer–consumer pipeline**:

- A **producer thread** simulates a satellite downlink, generating telemetry packets (temperature, bus voltage, orbital altitude) with occasional injected anomalies.
- A **consumer thread** processes each packet, computes running statistics, and raises an alert whenever a reading falls outside nominal operating limits.
- The two threads communicate through a **bounded, thread-safe queue** built with `std::mutex` and `std::condition_variable`.

## Key C++ concepts demonstrated

- **Modern C++ (C++17):** `std::optional`, structured bindings-ready APIs, templates
- **Concurrency:** `std::thread`, `std::atomic`, condition-variable-based synchronisation
- **Memory management:** `std::shared_ptr` / `std::unique_ptr`, RAII throughout (no raw `new`/`delete`)
- **Design:** header/implementation separation, a reusable templated `ThreadSafeQueue<T>`
- **Tooling:** CMake build, portable across GCC/Clang/MSVC, compiler warnings enabled

## Project structure

```
cpp-satellite-telemetry/
├── CMakeLists.txt
├── include/
│   ├── TelemetryPacket.h
│   ├── ThreadSafeQueue.h
│   ├── TelemetryGenerator.h
│   └── TelemetryProcessor.h
└── src/
    ├── main.cpp
    ├── TelemetryPacket.cpp
    ├── TelemetryGenerator.cpp
    └── TelemetryProcessor.cpp
```

## Build & run

### Using CMake (command line)

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
./build/telemetry 200      # optional argument: number of packets to simulate
```

### Using Qt Creator

Open `CMakeLists.txt` in Qt Creator, select a kit, and click **Run**.

## Example output

```
Satellite Telemetry Processing System
Simulating 200 telemetry packets...

  ALERT -> [t=400ms] SAT-7 | T=120.0C | V=3.95V | Alt=541.4km  [ALERT]
  ...

===== Telemetry Summary =====
Packets processed : 200
Alerts raised     : 9
Temp min / max    : 5.3 / 120.0 C
Temp average      : 29.3 C
=============================
```

## What I learned

- Designing a safe producer–consumer pipeline with condition variables
- Managing object lifetime with smart pointers and RAII in a multithreaded context
- Structuring a multi-file C++ project with CMake for portability

## License

MIT
