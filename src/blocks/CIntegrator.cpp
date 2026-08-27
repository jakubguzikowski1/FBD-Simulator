#include "CIntegrator.h"

#include "../interfaces/ICInput.h"
#include "../interfaces/ICOutput.h"

CIntegrator::CIntegrator(const std::string& name)
    : CProcessingBlock(name, 1U, 1U) {
}

void CIntegrator::beforeSim() {
    m_state = 0.0;
}

void CIntegrator::calculate(STimeStamp _ts, unsigned sampling) {
    SDataSample in = getInput(0U)->getData();
    SDataSample out;
    out.TimeStamp = _ts;
    if (!in.isOK()) {
        out.Status = DataSampleStatus::bad;
        out.Value = 0.0;
    } else {
        const double dt = static_cast<double>(sampling) / 1000.0;
        m_state += in.Value * dt;
        out.Status = DataSampleStatus::ok;
        out.Value = m_state;
    }
    getOutput(0U)->setData(out);
}
