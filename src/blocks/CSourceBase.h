#ifndef CSOURCEBASE_H
#define CSOURCEBASE_H

#include "CFunctionBlockBase.h"

/**
 * @brief Intermediate base class for source blocks.
 */
class CSourceBase : public CFunctionBlockBase {
public:
    /**
     * @brief Constructs a source block.
     * @param name Block name.
     * @param outCount Number of outputs.
     */
    CSourceBase(const std::string& name, std::size_t outCount);

    /**
     * @brief Checks if block is source.
     * @return Always true.
     */
    bool isSource() const override;
};

#endif  // CSOURCEBASE_H
