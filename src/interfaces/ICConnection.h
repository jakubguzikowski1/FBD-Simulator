#ifndef ICCONNECTION_H
#define ICCONNECTION_H

#include "../core/DataTypes.h"

class ICInput;
class ICOutput;

/**
 * @brief Abstract connection linking one output to one input.
 */
class ICConnection {
public:
    /**
     * @brief Virtual destructor.
     */
    virtual ~ICConnection() = default;

    /**
     * @brief Connects output side of a connection.
     * @param _out Output pin.
     */
    virtual void connectBegin(ICOutput* _out) = 0;

    /**
     * @brief Connects input side of a connection.
     * @param _in Input pin.
     */
    virtual void connectEnd(ICInput* _in) = 0;

    /**
     * @brief Reads sample flowing through the connection.
     * @return Sample from connected output.
     */
    virtual SDataSample getData() const = 0;
};

#endif  // ICCONNECTION_H
