#ifndef CINTEGRATOR_H
#define CINTEGRATOR_H

#include "CProcessingBlock.h"

/**
 * @brief Processing block performing discrete-time integration.
 */
class CIntegrator : public CProcessingBlock {
public:
    /**
     * @brief Constructs integrator block.
     * @param name Block name.
     */
    explicit CIntegrator(const std::string& name);

    /**
     * @brief Resets internal integral state before simulation.
     */
    void beforeSim() override;

    /**
     * @brief Integrates input over one simulation step.
     * @param _ts Current simulation timestamp.
     * @param sampling Sampling period in milliseconds.
     */
    void calculate(STimeStamp _ts, unsigned sampling) override;

private:
    /**
     * @brief Current integrated value.
     */
    double m_state{0.0};
};

#endif  // CINTEGRATOR_H
