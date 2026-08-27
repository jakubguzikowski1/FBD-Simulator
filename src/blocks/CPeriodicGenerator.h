#ifndef CPERIODICGENERATOR_H
#define CPERIODICGENERATOR_H

#include "CSourceBase.h"

/**
 * @brief Sine-wave source block driven by simulation time.
 */
class CPeriodicGenerator : public CSourceBase {
public:
    /**
     * @brief Constructs periodic source.
     * @param name Block name.
     * @param amplitude Wave amplitude.
     * @param frequencyHz Wave frequency in hertz.
     */
    CPeriodicGenerator(const std::string& name, double amplitude = 1.0, double frequencyHz = 1.0);

    /**
     * @brief Produces sine-wave output.
     * @param _ts Current simulation timestamp.
     * @param sampling Sampling period in milliseconds.
     */
    void calculate(STimeStamp _ts, unsigned sampling) override;

private:
    /**
     * @brief Output wave amplitude.
     */
    double m_amplitude;

    /**
     * @brief Output wave frequency in Hz.
     */
    double m_frequencyHz;
};

#endif  // CPERIODICGENERATOR_H
