#ifndef CGAIN_H
#define CGAIN_H

#include "CProcessingBlock.h"

/**
 * @brief Processing block that applies scalar gain.
 */
class CGain : public CProcessingBlock {
public:
    /**
     * @brief Constructs gain block.
     * @param name Block name.
     * @param gain Initial gain coefficient.
     */
    CGain(const std::string& name, double gain = 1.0);

    /**
     * @brief Updates gain parameter.
     * @param v New gain value.
     */
    void setParam(double v);

    /**
     * @brief Calculates scaled output from input.
     * @param _ts Current simulation timestamp.
     * @param sampling Sampling period in milliseconds.
     */
    void calculate(STimeStamp _ts, unsigned sampling) override;

private:
    /**
     * @brief Scalar gain coefficient.
     */
    double m_gain;
};

#endif  // CGAIN_H
