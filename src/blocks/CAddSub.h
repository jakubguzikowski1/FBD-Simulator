#ifndef CADDSUB_H
#define CADDSUB_H

#include <string>

#include "CProcessingBlock.h"

/**
 * @brief Processing block performing signed sum of inputs.
 */
class CAddSub : public CProcessingBlock {
public:
    /**
     * @brief Constructs add/subtract block.
     * @param name Block name.
     * @param signs String containing '+' and '-' operators.
     */
    CAddSub(const std::string& name, const std::string& signs);

    /**
     * @brief Calculates output as weighted sum by signs.
     * @param _ts Current simulation timestamp.
     * @param sampling Sampling period in milliseconds.
     */
    void calculate(STimeStamp _ts, unsigned sampling) override;

private:
    /**
     * @brief Operator string defining input signs.
     */
    std::string m_signs;
};

#endif  // CADDSUB_H
