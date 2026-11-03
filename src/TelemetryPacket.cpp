#include "TelemetryPacket.h"

#include <sstream>
#include <iomanip>

bool TelemetryPacket::isNominal() const {
    // Simple range checks representing nominal spacecraft operating limits.
    const bool tempOk = temperatureC > -40.0 && temperatureC < 85.0;
    const bool voltOk = voltage       > 3.0  && voltage       < 5.5;
    const bool altOk  = altitudeKm    > 150.0 && altitudeKm   < 2000.0;
    return tempOk && voltOk && altOk;
}

std::string TelemetryPacket::toString() const {
    std::ostringstream os;
    os << "[t=" << timestamp_ms << "ms]"
       << " SAT-" << satelliteId
       << " | T=" << std::fixed << std::setprecision(1) << temperatureC << "C"
       << " | V=" << std::setprecision(2) << voltage << "V"
       << " | Alt=" << std::setprecision(1) << altitudeKm << "km"
       << (isNominal() ? "  [OK]" : "  [ALERT]");
    return os.str();
}
