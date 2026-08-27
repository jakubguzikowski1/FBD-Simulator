#ifndef CPROCESSINGBLOCK_H
#define CPROCESSINGBLOCK_H

#include "CFunctionBlockBase.h"

/**
 * @brief Intermediate base class for processing blocks.
 */
class CProcessingBlock : public CFunctionBlockBase {
public:
    /**
     * @brief Constructs a processing block.
     * @param name Block name.
     * @param inCount Number of inputs.
     * @param outCount Number of outputs.
     */
    CProcessingBlock(const std::string& name, std::size_t inCount, std::size_t outCount);
};

#endif  // CPROCESSINGBLOCK_H
