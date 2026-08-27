#ifndef CFILEREAD_H
#define CFILEREAD_H

#include <string>
#include <vector>

#include "CSourceBase.h"

/**
 * @brief Source block that reads values from a CSV file.
 */
class CFileRead : public CSourceBase {
public:
    /**
     * @brief Constructs CSV reader source.
     * @param name Block name.
     * @param filename CSV filename.
     */
    CFileRead(const std::string& name, const std::string& filename);

    /**
     * @brief Loads source data from file.
     */
    void initialize() override;

    /**
     * @brief Publishes next sample from loaded data.
     * @param _ts Current simulation timestamp.
     * @param sampling Sampling period in milliseconds.
     */
    void calculate(STimeStamp _ts, unsigned sampling) override;

private:
    /**
     * @brief Input CSV file path.
     */
    std::string m_filename;

    /**
     * @brief Loaded sequence of values.
     */
    std::vector<double> m_values;

    /**
     * @brief Current read index.
     */
    std::size_t m_index{0U};
};

#endif  // CFILEREAD_H
