#ifndef CCONST_H
#define CCONST_H

#include "CSourceBase.h"

/**
 * @brief Constant signal source block.
 */
class CConst : public CSourceBase {
public:
    /**
     * @brief Constructs constant source.
     * @param name Block name.
     * @param value Initial constant value.
     */
    CConst(const std::string& name, double value = 0.0);

    /**
     * @brief Updates source parameter.
     * @param v New constant value.
     */
    void setParam(double v);

    /**
     * @brief Produces constant output.
     * @param _ts Current simulation timestamp.
     * @param sampling Sampling period in milliseconds.
     */
    void calculate(STimeStamp _ts, unsigned sampling) override;

private:
    /**
     * @brief Constant output value.
     */
    double m_value;
};

#endif  // CCONST_H
