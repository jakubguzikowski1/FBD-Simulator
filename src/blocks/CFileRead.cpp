#include "CFileRead.h"

#include <fstream>
#include <sstream>

#include "../interfaces/ICOutput.h"

CFileRead::CFileRead(const std::string& name, const std::string& filename)
    : CSourceBase(name, 1U), m_filename(filename) {
}

void CFileRead::initialize() {
    m_values.clear();
    m_index = 0U;

    std::ifstream ifs(m_filename);
    if (!ifs.is_open()) {
        return;
    }

    std::string line;
    while (std::getline(ifs, line)) {
        if (line.empty()) {
            continue;
        }
        std::stringstream ss(line);
        std::string token;
        if (std::getline(ss, token, ',')) {
            try {
                m_values.push_back(std::stod(token));
            } catch (...) {
            }
        }
    }
}

void CFileRead::calculate(STimeStamp _ts, unsigned sampling) {
    (void)sampling;
    SDataSample sample;
    sample.TimeStamp = _ts;

    if (m_index < m_values.size()) {
        sample.Value = m_values[m_index];
        sample.Status = DataSampleStatus::ok;
        ++m_index;
    } else {
        sample.Value = 0.0;
        sample.Status = DataSampleStatus::bad;
    }

    getOutput(0U)->setData(sample);
}
