#include "CFileWrite.h"

#include "../interfaces/ICInput.h"

CFileWrite::CFileWrite(const std::string& name, const std::string& filename)
    : CSinkBase(name, 1U), m_filename(filename) {
}

CFileWrite::~CFileWrite() {
    if (m_ofs.is_open()) {
        m_ofs.close();
    }
}

void CFileWrite::initialize() {
    if (m_ofs.is_open()) {
        m_ofs.close();
    }
    m_ofs.open(m_filename, std::ios::out | std::ios::trunc);
    if (m_ofs.is_open()) {
        m_ofs << "time_s,value,status\n";
    }
}

void CFileWrite::calculate(STimeStamp _ts, unsigned sampling) {
    (void)_ts;
    (void)sampling;
    m_lastSample = getInput(0U)->getData();
}

void CFileWrite::afterSimStep() {
    if (!m_ofs.is_open()) {
        return;
    }
    m_ofs << m_lastSample.TimeStamp.getInSeconds() << ","
          << m_lastSample.Value << ","
          << (m_lastSample.Status == DataSampleStatus::ok ? 0 : 1) << "\n";
}

void CFileWrite::afterSim() {
    if (m_ofs.is_open()) {
        m_ofs.flush();
        m_ofs.close();
    }
}
