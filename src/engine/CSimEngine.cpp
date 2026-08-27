#include "CSimEngine.h"

#include "CContainerFBD.h"

CSimEngine::CSimEngine(CContainerFBD* container)
    : m_container(container) {
}

void CSimEngine::resetSimulation() {
    m_currentTime = STimeStamp{};
    m_currentStep = 0U;

    if (m_container == nullptr) {
        return;
    }

    for (ICFunctionBlock* block : m_container->getBlocks()) {
        block->beforeSim();
        block->initialize();
    }
}

void CSimEngine::doSimStep() {
    if (m_container == nullptr || !canStep()) {
        return;
    }

    m_currentTime.addSampling(m_container->getSamplingTime());
    ++m_currentStep;

    for (ICFunctionBlock* block : m_container->getBlocks()) {
        block->calculate(m_currentTime, m_container->getSamplingTime());
    }

    for (ICFunctionBlock* block : m_container->getBlocks()) {
        block->afterSimStep();
    }
}

void CSimEngine::finalizeSimulation() {
    if (m_container == nullptr) {
        return;
    }
    for (ICFunctionBlock* block : m_container->getBlocks()) {
        block->afterSim();
    }
}

void CSimEngine::setMaxSteps(unsigned maxSteps) {
    m_maxSteps = maxSteps;
}

unsigned CSimEngine::getCurrentStep() const {
    return m_currentStep;
}

STimeStamp CSimEngine::getCurrentTime() const {
    return m_currentTime;
}

bool CSimEngine::canStep() const {
    return m_currentStep < m_maxSteps;
}
