#pragma once
#include "StuManager.h"

class GradeStatistics {
public:
    GradeStatistics(StuManager& manager);

    void sortGrade();
    void analysisGrade();

private:
    StuManager& m_Manager;
};
