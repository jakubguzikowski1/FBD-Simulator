#include "CSourceBase.h"

CSourceBase::CSourceBase(const std::string& name, std::size_t outCount)
    : CFunctionBlockBase(name, 0U, outCount) {
}

bool CSourceBase::isSource() const {
    return true;
}
