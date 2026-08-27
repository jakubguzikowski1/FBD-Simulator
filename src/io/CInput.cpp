#include "CInput.h"

#include "../interfaces/ICConnection.h"

void CInput::addConnection(ICConnection* _con) {
    if (_con != nullptr) {
        m_connections.push_back(_con);
    }
}

SDataSample CInput::getData() const {
    if (m_connections.empty() || m_connections.front() == nullptr) {
        return SDataSample{};
    }
    return m_connections.front()->getData();
}
