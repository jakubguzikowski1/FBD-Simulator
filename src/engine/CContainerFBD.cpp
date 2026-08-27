#include "CContainerFBD.h"

CContainerFBD::~CContainerFBD() {
    for (ICConnection* connection : m_connections) {
        delete connection;
    }
    for (ICFunctionBlock* block : m_blocks) {
        delete block;
    }
}

void CContainerFBD::addBlock(ICFunctionBlock* block) {
    if (block == nullptr) {
        return;
    }
    m_blocks.push_back(block);
    m_blocksByName[block->getName()] = block;
}

void CContainerFBD::addConnection(ICConnection* connection) {
    if (connection == nullptr) {
        return;
    }
    m_connections.push_back(connection);
}

ICFunctionBlock* CContainerFBD::findBlockByName(const std::string& name) const {
    const auto it = m_blocksByName.find(name);
    if (it == m_blocksByName.end()) {
        return nullptr;
    }
    return it->second;
}

const std::vector<ICFunctionBlock*>& CContainerFBD::getBlocks() const {
    return m_blocks;
}

const std::vector<ICConnection*>& CContainerFBD::getConnections() const {
    return m_connections;
}

void CContainerFBD::setSamplingTime(unsigned samplingMs) {
    SamplingTime = samplingMs;
}

unsigned CContainerFBD::getSamplingTime() const {
    return SamplingTime;
}
