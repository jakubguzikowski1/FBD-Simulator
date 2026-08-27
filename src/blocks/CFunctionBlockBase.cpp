#include "CFunctionBlockBase.h"

#include "../interfaces/ICInput.h"
#include "../interfaces/ICOutput.h"
#include "../io/CInput.h"
#include "../io/COutput.h"

CFunctionBlockBase::CFunctionBlockBase(const std::string& name, std::size_t inCount, std::size_t outCount)
    : m_name(name) {
    m_inputs.reserve(inCount);
    for (std::size_t i = 0; i < inCount; ++i) {
        m_inputs.push_back(new CInput());
    }

    m_outputs.reserve(outCount);
    for (std::size_t i = 0; i < outCount; ++i) {
        m_outputs.push_back(new COutput());
    }
}

CFunctionBlockBase::~CFunctionBlockBase() {
    for (ICInput* in : m_inputs) {
        delete in;
    }
    for (ICOutput* out : m_outputs) {
        delete out;
    }
}

void CFunctionBlockBase::beforeSim() {
}

void CFunctionBlockBase::initialize() {
}

void CFunctionBlockBase::afterSimStep() {
}

void CFunctionBlockBase::afterSim() {
}

std::string CFunctionBlockBase::getName() const {
    return m_name;
}

ICInput* CFunctionBlockBase::getInput(std::size_t idx) const {
    if (idx >= m_inputs.size()) {
        return nullptr;
    }
    return m_inputs[idx];
}

ICOutput* CFunctionBlockBase::getOutput(std::size_t idx) const {
    if (idx >= m_outputs.size()) {
        return nullptr;
    }
    return m_outputs[idx];
}

std::size_t CFunctionBlockBase::getOutCount() const {
    return m_outputs.size();
}

bool CFunctionBlockBase::isSource() const {
    return false;
}

bool CFunctionBlockBase::isSink() const {
    return false;
}
