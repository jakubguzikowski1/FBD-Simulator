#include "CPeriodicGenerator.h"

#include <cmath>

#include "../interfaces/ICOutput.h"

namespace {
/**
 * @brief PI constant for sine generation.
 */
constexpr double kPi = 3.14159265358979323846;
}  // namespace

CPeriodicGenerator::CPeriodicGenerator(const std::string& name, double amplitude, double frequencyHz)
    : CSourceBase(name, 1U), m_amplitude(amplitude), m_frequencyHz(frequencyHz) {
}

void CPeriodicGenerator::calculate(STimeStamp _ts, unsigned sampling) {
    (void)sampling;
    const double t = _ts.getInSeconds();
    SDataSample sample;
    sample.Value = m_amplitude * std::sin(2.0 * kPi * m_frequencyHz * t);
    sample.Status = DataSampleStatus::ok;
    sample.TimeStamp = _ts;
    getOutput(0U)->setData(sample);
}
