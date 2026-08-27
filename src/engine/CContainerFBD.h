#ifndef CCONTAINERFBD_H
#define CCONTAINERFBD_H

#include <string>
#include <unordered_map>
#include <vector>

#include "../interfaces/ICConnection.h"
#include "../interfaces/ICFunctionBlock.h"

/**
 * @brief Owns FBD blocks and connections.
 */
class CContainerFBD {
public:
    /**
     * @brief Constructs an empty container.
     */
    CContainerFBD() = default;

    /**
     * @brief Destroys owned blocks and connections.
     */
    ~CContainerFBD();

    /**
     * @brief Adds a function block to the container.
     * @param block Newly created block pointer.
     */
    void addBlock(ICFunctionBlock* block);

    /**
     * @brief Adds a connection to the container.
     * @param connection Newly created connection pointer.
     */
    void addConnection(ICConnection* connection);

    /**
     * @brief Finds block by logical name.
     * @param name Name to search.
     * @return Block pointer or nullptr.
     */
    ICFunctionBlock* findBlockByName(const std::string& name) const;

    /**
     * @brief Returns all blocks.
     * @return Constant vector reference.
     */
    const std::vector<ICFunctionBlock*>& getBlocks() const;

    /**
     * @brief Returns all connections.
     * @return Constant vector reference.
     */
    const std::vector<ICConnection*>& getConnections() const;

    /**
     * @brief Sets simulation sampling time.
     * @param samplingMs Sampling period in milliseconds.
     */
    void setSamplingTime(unsigned samplingMs);

    /**
     * @brief Returns simulation sampling time.
     * @return Sampling period in milliseconds.
     */
    unsigned getSamplingTime() const;

private:
    /**
     * @brief Owned list of function blocks.
     */
    std::vector<ICFunctionBlock*> m_blocks;

    /**
     * @brief Owned list of connections.
     */
    std::vector<ICConnection*> m_connections;

    /**
     * @brief Name-to-block lookup table.
     */
    std::unordered_map<std::string, ICFunctionBlock*> m_blocksByName;

public:
    /**
     * @brief Simulation sampling period in milliseconds.
     */
    unsigned SamplingTime{100U};
};

#endif  // CCONTAINERFBD_H
