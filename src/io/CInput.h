#ifndef CINPUT_H
#define CINPUT_H

#include <vector>

#include "../interfaces/ICInput.h"

class ICConnection;

/**
 * @brief Concrete input pin implementation.
 */
class CInput : public ICInput {
public:
    /**
     * @brief Default constructor.
     */
    CInput() = default;

    /**
     * @brief Adds upstream connection.
     * @param _con Connection pointer.
     */
    void addConnection(ICConnection* _con) override;

    /**
     * @brief Reads sample from first connected source.
     * @return Sample from connection or bad sample if disconnected.
     */
    SDataSample getData() const override;

private:
    /**
     * @brief List of connected links feeding this input.
     */
    std::vector<ICConnection*> m_connections;
};

#endif  // CINPUT_H
