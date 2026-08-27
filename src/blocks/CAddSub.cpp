#include "CAddSub.h"

#include "../interfaces/ICInput.h"
#include "../interfaces/ICOutput.h"

CAddSub::CAddSub(const std::string& name, const std::string& signs)
    : CProcessingBlock(name, signs.size(), 1U), m_signs(signs) {
}

void CAddSub::calculate(STimeStamp _ts, unsigned sampling) {
    (void)sampling;
    bool valid = true;
    double sum = 0.0;
    for (std::size_t i = 0; i < m_signs.size(); ++i) {
        const SDataSample in = getInput(i)->getData();
        if (!in.isOK()) {
            valid = false;
            break;
        }
        const char sign = m_signs[i];
        if (sign == '-') {
            sum -= in.Value;
        } else {
            sum += in.Value;
        }
    }

    SDataSample out;
    out.TimeStamp = _ts;
    out.Status = valid ? DataSampleStatus::ok : DataSampleStatus::bad;
    out.Value = valid ? sum : 0.0;
    getOutput(0U)->setData(out);
}
