#include "COutput.h"

SDataSample COutput::getData() const {
    return m_data;
}

void COutput::setData(const SDataSample& _val) {
    m_data = _val;
}
