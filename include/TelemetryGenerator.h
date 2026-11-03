#pragma once

#include "TelemetryPacket.h"
#include <random>

// Simulates a satellite downlink by generating realistic-looking telemetry
// packets, occasionally producing out-of-range ("alert") values.
class TelemetryGenerator {
public:
    explicit TelemetryGenerator(int satelliteId, unsigned seed = 42);

    // Produces the next packet, advancing the simulated mission clock.
    TelemetryPacket next();

private:
    int                                    satelliteId_;
    std::uint64_t                          clockMs_ = 0;
    std::mt19937                           rng_;
    std::normal_distribution<double>       tempDist_{25.0, 8.0};
    std::normal_distribution<double>       voltDist_{4.0, 0.3};
    std::normal_distribution<double>       altDist_{550.0, 20.0};
    std::uniform_real_distribution<double> faultDist_{0.0, 1.0};
};
