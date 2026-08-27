#ifndef CFILEWRITE_H
#define CFILEWRITE_H

#include <fstream>
#include <string>

#include "CSinkBase.h"

/**
 * @brief Sink block writing incoming samples to CSV file.
 */
class CFileWrite : public CSinkBase {
public:
    /**
     * @brief Constructs CSV writer sink.
     * @param name Block name.
     * @param filename Output CSV filename.
     */
    CFileWrite(const std::string& name, const std::string& filename);

    /**
     * @brief Closes output stream on destruction.
     */
    ~CFileWrite() override;

    /**
     * @brief Opens output CSV file.
     */
    void initialize() override;

    /**
     * @brief Captures current input sample.
     * @param _ts Current simulation timestamp.
     * @param sampling Sampling period in milliseconds.
     */
    void calculate(STimeStamp _ts, unsigned sampling) override;

    /**
     * @brief Writes captured sample at end of simulation step.
     */
    void afterSimStep() override;

    /**
     * @brief Flushes and closes output stream.
     */
    void afterSim() override;

private:
    /**
     * @brief Output CSV file path.
     */
    std::string m_filename;

    /**
     * @brief File stream for output writing.
     */
    std::ofstream m_ofs;

    /**
     * @brief Last captured sample from input.
     */
    SDataSample m_lastSample;
};

#endif  // CFILEWRITE_H
