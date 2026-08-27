#include "CConst.h"

#include "../interfaces/ICOutput.h"

CConst::CConst(const std::string& name, double value)
    : CSourceBase(name, 1U), m_value(value) {
}

void CConst::setParam(double v) {
    m_value = v;
}

void CConst::calculate(STimeStamp _ts, unsigned sampling) {
    (void)sampling;
    SDataSample sample;
    sample.Value = m_value;
    sample.Status = DataSampleStatus::ok;
    sample.TimeStamp = _ts;
    getOutput(0U)->setData(sample);
}
