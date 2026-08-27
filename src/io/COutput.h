#ifndef COUTPUT_H
#define COUTPUT_H

#include "../interfaces/ICOutput.h"

/**
 * @brief Concrete output pin implementation.
 */
class COutput : public ICOutput {
public:
    /**
     * @brief Default constructor.
     */
    COutput() = default;

    /**
     * @brief Returns current output sample.
     * @return Stored sample.
     */
    SDataSample getData() const override;

    /**
     * @brief Updates current output sample.
     * @param _val New sample value.
     */
    void setData(const SDataSample& _val) override;

private:
    /**
     * @brief Last produced sample.
     */
    SDataSample m_data;
};

#endif  // COUTPUT_H
