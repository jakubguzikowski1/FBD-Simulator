#include "CConnection.h"

#include "../interfaces/ICInput.h"
#include "../interfaces/ICOutput.h"

void CConnection::connectBegin(ICOutput* _out) {
    m_out = _out;
}

void CConnection::connectEnd(ICInput* _in) {
    m_in = _in;
    if (m_in != nullptr) {
        m_in->addConnection(this);
    }
}

SDataSample CConnection::getData() const {
    if (m_out == nullptr) {
        return SDataSample{};
    }
    return m_out->getData();
}
