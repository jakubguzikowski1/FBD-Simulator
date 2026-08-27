#ifndef CFUNCTIONBLOCKBASE_H
#define CFUNCTIONBLOCKBASE_H

#include <string>
#include <vector>

#include "../interfaces/ICFunctionBlock.h"

class ICInput;
class ICOutput;

/**
 * @brief Base implementation shared by all function blocks.
 */
class CFunctionBlockBase : public ICFunctionBlock {
public:
    /**
     * @brief Creates a block with a fixed number of pins.
     * @param name Logical block name.
     * @param inCount Number of inputs to allocate.
     * @param outCount Number of outputs to allocate.
     */
    CFunctionBlockBase(const std::string& name, std::size_t inCount, std::size_t outCount);

    /**
     * @brief Virtual destructor.
     */
    ~CFunctionBlockBase() override;

    /**
     * @brief Default pre-simulation hook.
     */
    void beforeSim() override;

    /**
     * @brief Default initialization hook.
     */
    void initialize() override;

    /**
     * @brief Performs block-specific computation.
     * @param _ts Current simulation timestamp.
     * @param sampling Sampling period in milliseconds.
     */
    virtual void calculate(STimeStamp _ts, unsigned sampling) override = 0;

    /**
     * @brief Default post-step hook.
     */
    void afterSimStep() override;

    /**
     * @brief Default post-simulation hook.
     */
    void afterSim() override;

    /**
     * @brief Returns block name.
     * @return Logical name.
     */
    std::string getName() const override;

    /**
     * @brief Gets input by index.
     * @param idx Input index.
     * @return Input pointer or nullptr.
     */
    ICInput* getInput(std::size_t idx) const override;

    /**
     * @brief Gets output by index.
     * @param idx Output index.
     * @return Output pointer or nullptr.
     */
    ICOutput* getOutput(std::size_t idx) const override;

    /**
     * @brief Returns number of outputs.
     * @return Output pin count.
     */
    std::size_t getOutCount() const override;

    /**
     * @brief Default source check.
     * @return False.
     */
    bool isSource() const override;

    /**
     * @brief Default sink check.
     * @return False.
     */
    bool isSink() const override;

protected:
    /**
     * @brief Block name.
     */
    std::string m_name;

    /**
     * @brief Dynamically allocated input interfaces.
     */
    std::vector<ICInput*> m_inputs;

    /**
     * @brief Dynamically allocated output interfaces.
     */
    std::vector<ICOutput*> m_outputs;
};

#endif  // CFUNCTIONBLOCKBASE_H
