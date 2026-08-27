#ifndef CSIMENGINE_H
#define CSIMENGINE_H

#include "../core/DataTypes.h"

class CContainerFBD;

/**
 * @brief Simulation engine executing discrete FBD steps.
 */
class CSimEngine {
public:
    /**
     * @brief Constructs engine bound to a container.
     * @param container Simulation container pointer.
     */
    explicit CSimEngine(CContainerFBD* container);

    /**
     * @brief Initializes all blocks and resets counters.
     */
    void resetSimulation();

    /**
     * @brief Executes one simulation step.
     */
    void doSimStep();

    /**
     * @brief Finalizes simulation and calls block shutdown hooks.
     */
    void finalizeSimulation();

    /**
     * @brief Sets maximum allowed steps.
     * @param maxSteps Maximum step count.
     */
    void setMaxSteps(unsigned maxSteps);

    /**
     * @brief Returns executed step count.
     * @return Current step counter.
     */
    unsigned getCurrentStep() const;

    /**
     * @brief Returns current simulation timestamp.
     * @return Current timestamp.
     */
    STimeStamp getCurrentTime() const;

    /**
     * @brief Indicates whether further steps are allowed.
     * @return True when current step is below configured limit.
     */
    bool canStep() const;

private:
    /**
     * @brief Attached simulation container.
     */
    CContainerFBD* m_container{nullptr};

    /**
     * @brief Current simulation time.
     */
    STimeStamp m_currentTime{};

    /**
     * @brief Number of executed steps.
     */
    unsigned m_currentStep{0U};

    /**
     * @brief Maximum number of simulation steps.
     */
    unsigned m_maxSteps{1000U};
};

#endif  // CSIMENGINE_H
