#include "TelemetryProcessor.h"

#include <algorithm>
#include <iostream>

void TelemetryProcessor::process(const TelemetryPacket& packet) {
    ++total_;
    sumTemp_ += packet.temperatureC;
    minTemp_ = std::min(minTemp_, packet.temperatureC);
    maxTemp_ = std::max(maxTemp_, packet.temperatureC);

    if (!packet.isNominal()) {
        ++alerts_;
        std::cout << "  ALERT -> " << packet.toString() << '\n';
    }
}

void TelemetryProcessor::printSummary() const {
    std::cout << "\n===== Telemetry Summary =====\n";
    std::cout << "Packets processed : " << total_ << '\n';
    std::cout << "Alerts raised     : " << alerts_ << '\n';
    if (total_ > 0) {
        std::cout << "Temp min / max    : " << minTemp_ << " / " << maxTemp_ << " C\n";
        std::cout << "Temp average      : " << (sumTemp_ / static_cast<double>(total_)) << " C\n";
    }
    std::cout << "=============================\n";
}
