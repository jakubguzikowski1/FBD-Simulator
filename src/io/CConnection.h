#ifndef CCONNECTION_H
#define CCONNECTION_H

#include "../interfaces/ICConnection.h"

class ICInput;
class ICOutput;

/**
 * @brief Concrete point-to-point connection implementation.
 */
class CConnection : public ICConnection {
public:
    /**
     * @brief Default constructor.
     */
    CConnection() = default;

    /**
     * @brief Connects producer output endpoint.
     * @param _out Output endpoint.
     */
    void connectBegin(ICOutput* _out) override;

    /**
     * @brief Connects consumer input endpoint.
     * @param _in Input endpoint.
     */
    void connectEnd(ICInput* _in) override;

    /**
     * @brief Returns data currently available on the connection.
     * @return Data sample from connected output or bad sample.
     */
    SDataSample getData() const override;

private:
    /**
     * @brief Connected output endpoint.
     */
    ICOutput* m_out{nullptr};

    /**
     * @brief Connected input endpoint.
     */
    ICInput* m_in{nullptr};
};

#endif  // CCONNECTION_H
