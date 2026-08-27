#ifndef CSINKBASE_H
#define CSINKBASE_H

#include "CFunctionBlockBase.h"

/**
 * @brief Intermediate base class for sink blocks.
 */
class CSinkBase : public CFunctionBlockBase {
public:
    /**
     * @brief Constructs a sink block.
     * @param name Block name.
     * @param inCount Number of inputs.
     */
    CSinkBase(const std::string& name, std::size_t inCount);

    /**
     * @brief Checks if block is sink.
     * @return Always true.
     */
    bool isSink() const override;
};

#endif  // CSINKBASE_H
