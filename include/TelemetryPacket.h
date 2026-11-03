#pragma once

#include <cstdint>
#include <string>

// A single telemetry reading coming down from a satellite.
// Kept as a small, copyable value type.
struct TelemetryPacket {
    std::uint64_t timestamp_ms = 0;   // mission elapsed time in milliseconds
    int           satelliteId  = 0;   // which satellite sent it
    double        temperatureC = 0.0; // onboard temperature (deg C)
    double        voltage      = 0.0; // bus voltage (V)
    double        altitudeKm   = 0.0; // orbital altitude (km)

    // Returns true if every field is inside its expected operating range.
    bool isNominal() const;

    // Human-readable one-line summary.
    std::string toString() const;
};
