#ifndef ICFUNCTIONBLOCK_H
#define ICFUNCTIONBLOCK_H

#include <cstddef>
#include <string>

#include "../core/DataTypes.h"

class ICInput;
class ICOutput;

/**
 * @brief Abstract interface for all function blocks in the simulator.
 */
class ICFunctionBlock {
public:
    /**
     * @brief Virtual destructor.
     */
    virtual ~ICFunctionBlock() = default;

    /**
     * @brief Called once before simulation starts.
     */
    virtual void beforeSim() = 0;

    /**
     * @brief Called once to initialize runtime resources.
     */
    virtual void initialize() = 0;

    /**
     * @brief Calculates outputs for one simulation step.
     * @param _ts Current simulation timestamp.
     * @param sampling Sampling period in milliseconds.
     */
    virtual void calculate(STimeStamp _ts, unsigned sampling) = 0;

    /**
     * @brief Called after all block calculations in the step.
     */
    virtual void afterSimStep() = 0;

    /**
     * @brief Called once after simulation completes.
     */
    virtual void afterSim() = 0;

    /**
     * @brief Returns logical block name.
     * @return Block name.
     */
    virtual std::string getName() const = 0;

    /**
     * @brief Returns input interface by index.
     * @param idx Input index.
     * @return Input pointer or nullptr if index is invalid.
     */
    virtual ICInput* getInput(std::size_t idx) const = 0;

    /**
     * @brief Returns output interface by index.
     * @param idx Output index.
     * @return Output pointer or nullptr if index is invalid.
     */
    virtual ICOutput* getOutput(std::size_t idx) const = 0;

    /**
     * @brief Returns number of outputs.
     * @return Output count.
     */
    virtual std::size_t getOutCount() const = 0;

    /**
     * @brief Indicates whether block is a source type.
     * @return True for source blocks.
     */
    virtual bool isSource() const = 0;

    /**
     * @brief Indicates whether block is a sink type.
     * @return True for sink blocks.
     */
    virtual bool isSink() const = 0;
};

#endif  // ICFUNCTIONBLOCK_H
