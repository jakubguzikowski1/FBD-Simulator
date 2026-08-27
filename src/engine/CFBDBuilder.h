#ifndef CFBDBUILDER_H
#define CFBDBUILDER_H

#include <string>
#include <vector>

class CContainerFBD;
class ICFunctionBlock;

/**
 * @brief Builds FBD model from text configuration file.
 */
class CFBDBuilder {
public:
    /**
     * @brief Constructs builder bound to container.
     * @param container Target container pointer.
     */
    explicit CFBDBuilder(CContainerFBD* container);

    /**
     * @brief Parses file and configures blocks/connections.
     * @param filename Configuration text file path.
     */
    void configureFBDFromFile(const std::string& filename);

private:
    /**
     * @brief Creates block instance based on type and arguments.
     * @param type Type token.
     * @param name Block name token.
     * @param args Additional constructor arguments.
     * @return Newly allocated function block.
     */
    ICFunctionBlock* createBlock(const std::string& type,
                                 const std::string& name,
                                 const std::vector<std::string>& args) const;

    /**
     * @brief Target container for created objects.
     */
    CContainerFBD* m_container{nullptr};
};

#endif  // CFBDBUILDER_H
