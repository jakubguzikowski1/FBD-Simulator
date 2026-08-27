#include "CFBDBuilder.h"

#include <fstream>
#include <sstream>
#include <stdexcept>

#include "../blocks/CAddSub.h"
#include "../blocks/CConst.h"
#include "../blocks/CFileRead.h"
#include "../blocks/CFileWrite.h"
#include "../blocks/CGain.h"
#include "../blocks/CIntegrator.h"
#include "../blocks/CPeriodicGenerator.h"
#include "../interfaces/ICFunctionBlock.h"
#include "../io/CConnection.h"
#include "CContainerFBD.h"

namespace {
/**
 * @brief Splits text line by whitespace.
 * @param line Input text line.
 * @return Token sequence.
 */
std::vector<std::string> splitTokens(const std::string& line) {
    std::stringstream ss(line);
    std::vector<std::string> tokens;
    std::string tok;
    while (ss >> tok) {
        tokens.push_back(tok);
    }
    return tokens;
}
}  // namespace

CFBDBuilder::CFBDBuilder(CContainerFBD* container)
    : m_container(container) {
}

void CFBDBuilder::configureFBDFromFile(const std::string& filename) {
    if (m_container == nullptr) {
        throw std::runtime_error("Builder has no target container.");
    }

    std::ifstream ifs(filename);
    if (!ifs.is_open()) {
        throw std::runtime_error("Cannot open config file: " + filename);
    }

    std::string line;
    while (std::getline(ifs, line)) {
        if (line.empty() || line[0] == '#') {
            continue;
        }

        const std::vector<std::string> tokens = splitTokens(line);
        if (tokens.empty()) {
            continue;
        }

        if (tokens[0] == "SAMPLING") {
            if (tokens.size() < 2U) {
                throw std::runtime_error("SAMPLING requires one argument.");
            }
            m_container->setSamplingTime(static_cast<unsigned>(std::stoul(tokens[1])));
        } else if (tokens[0] == "BLOCK") {
            if (tokens.size() < 3U) {
                throw std::runtime_error("BLOCK requires type and name.");
            }
            std::vector<std::string> args;
            for (std::size_t i = 3U; i < tokens.size(); ++i) {
                args.push_back(tokens[i]);
            }
            ICFunctionBlock* block = createBlock(tokens[1], tokens[2], args);
            m_container->addBlock(block);
        } else if (tokens[0] == "CONNECT") {
            if (tokens.size() < 5U) {
                throw std::runtime_error("CONNECT requires srcName srcOut dstName dstIn.");
            }
            ICFunctionBlock* src = m_container->findBlockByName(tokens[1]);
            ICFunctionBlock* dst = m_container->findBlockByName(tokens[3]);
            if (src == nullptr || dst == nullptr) {
                throw std::runtime_error("CONNECT references unknown blocks.");
            }

            const std::size_t srcOutIdx = static_cast<std::size_t>(std::stoul(tokens[2]));
            const std::size_t dstInIdx = static_cast<std::size_t>(std::stoul(tokens[4]));

            CConnection* connection = new CConnection();
            connection->connectBegin(src->getOutput(srcOutIdx));
            connection->connectEnd(dst->getInput(dstInIdx));
            m_container->addConnection(connection);
        } else {
            throw std::runtime_error("Unknown config command: " + tokens[0]);
        }
    }
}

ICFunctionBlock* CFBDBuilder::createBlock(const std::string& type,
                                          const std::string& name,
                                          const std::vector<std::string>& args) const {
    if (type == "Const") {
        const double v = args.empty() ? 0.0 : std::stod(args[0]);
        return new CConst(name, v);
    }
    if (type == "PeriodicGenerator") {
        const double amp = args.size() >= 1U ? std::stod(args[0]) : 1.0;
        const double freq = args.size() >= 2U ? std::stod(args[1]) : 1.0;
        return new CPeriodicGenerator(name, amp, freq);
    }
    if (type == "FileRead") {
        if (args.empty()) {
            throw std::runtime_error("FileRead requires filename.");
        }
        return new CFileRead(name, args[0]);
    }
    if (type == "Gain") {
        const double gain = args.empty() ? 1.0 : std::stod(args[0]);
        return new CGain(name, gain);
    }
    if (type == "AddSub") {
        if (args.empty()) {
            throw std::runtime_error("AddSub requires signs string.");
        }
        return new CAddSub(name, args[0]);
    }
    if (type == "Integrator") {
        return new CIntegrator(name);
    }
    if (type == "FileWrite") {
        if (args.empty()) {
            throw std::runtime_error("FileWrite requires filename.");
        }
        return new CFileWrite(name, args[0]);
    }

    throw std::runtime_error("Unsupported block type: " + type);
}
