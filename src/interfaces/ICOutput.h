#ifndef ICOUTPUT_H
#define ICOUTPUT_H

#include "../core/DataTypes.h"

/**
 * @brief Abstract output pin interface for function blocks.
 */
class ICOutput {
public:
    /**
     * @brief Virtual destructor.
     */
    virtual ~ICOutput() = default;

    /**
     * @brief Reads current output sample.
     * @return Current output sample.
     */
    virtual SDataSample getData() const = 0;

    /**
     * @brief Writes current output sample.
     * @param _val Sample to expose on this output.
     */
    virtual void setData(const SDataSample& _val) = 0;
};

#endif  // ICOUTPUT_H
