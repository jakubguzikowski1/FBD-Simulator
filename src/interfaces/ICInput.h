#ifndef ICINPUT_H
#define ICINPUT_H

#include "../core/DataTypes.h"

class ICConnection;

/**
 * @brief Abstract input pin interface for function blocks.
 */
class ICInput {
public:
    /**
     * @brief Virtual destructor.
     */
    virtual ~ICInput() = default;

    /**
     * @brief Adds a connection feeding this input.
     * @param _con Pointer to connection object.
     */
    virtual void addConnection(ICConnection* _con) = 0;

    /**
     * @brief Reads input sample from connection(s).
     * @return Sample value delivered to this input.
     */
    virtual SDataSample getData() const = 0;
};

#endif  // ICINPUT_H
