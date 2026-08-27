#include "CSinkBase.h"

CSinkBase::CSinkBase(const std::string& name, std::size_t inCount)
    : CFunctionBlockBase(name, inCount, 0U) {
}

bool CSinkBase::isSink() const {
    return true;
}
