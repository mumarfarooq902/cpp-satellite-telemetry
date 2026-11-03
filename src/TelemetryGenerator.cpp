#include "TelemetryGenerator.h"

TelemetryGenerator::TelemetryGenerator(int satelliteId, unsigned seed)
    : satelliteId_(satelliteId), rng_(seed) {}

TelemetryPacket TelemetryGenerator::next() {
    TelemetryPacket p;
    clockMs_ += 100;  // one reading every 100 ms of mission time
    p.timestamp_ms = clockMs_;
    p.satelliteId  = satelliteId_;
    p.temperatureC = tempDist_(rng_);
    p.voltage      = voltDist_(rng_);
    p.altitudeKm   = altDist_(rng_);

    // ~5% of the time, inject an anomalous value to exercise the alert path.
    if (faultDist_(rng_) < 0.05) {
        p.temperatureC = 120.0;  // overheating event
    }
    return p;
}
