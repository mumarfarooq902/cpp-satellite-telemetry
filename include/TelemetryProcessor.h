#pragma once

#include "TelemetryPacket.h"
#include <cstddef>

// Consumes telemetry packets and maintains running statistics:
// counts, min/max temperature, and number of alerts raised.
class TelemetryProcessor {
public:
    void process(const TelemetryPacket& packet);
    void printSummary() const;

private:
    std::size_t total_   = 0;
    std::size_t alerts_  = 0;
    double      minTemp_ = 1e9;
    double      maxTemp_ = -1e9;
    double      sumTemp_ = 0.0;
};
