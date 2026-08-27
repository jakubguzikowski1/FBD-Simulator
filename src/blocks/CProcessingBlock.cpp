#include "CProcessingBlock.h"

CProcessingBlock::CProcessingBlock(const std::string& name, std::size_t inCount, std::size_t outCount)
    : CFunctionBlockBase(name, inCount, outCount) {
}
