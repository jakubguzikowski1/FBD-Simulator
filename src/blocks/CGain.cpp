#include "CGain.h"

#include "../interfaces/ICInput.h"
#include "../interfaces/ICOutput.h"

CGain::CGain(const std::string& name, double gain)
    : CProcessingBlock(name, 1U, 1U), m_gain(gain) {
}

void CGain::setParam(double v) {
    m_gain = v;
}

void CGain::calculate(STimeStamp _ts, unsigned sampling) {
    (void)sampling;
    SDataSample in = getInput(0U)->getData();
    SDataSample out;
    out.TimeStamp = _ts;
    if (!in.isOK()) {
        out.Status = DataSampleStatus::bad;
        out.Value = 0.0;
    } else {
        out.Status = DataSampleStatus::ok;
        out.Value = in.Value * m_gain;
    }
    getOutput(0U)->setData(out);
}
