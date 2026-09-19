#include "GradeStatistics.h"
#include <iostream>
#include <algorithm>
#include <iomanip>

GradeStatistics::GradeStatistics(StuManager& manager)
    : m_Manager(manager) {
}

void GradeStatistics::sortGrade() {
    auto& stus = m_Manager.m_Stus;

    std::sort(stus.begin(), stus.end(),
        [](const Student& a, const Student& b) {
            int totalA = a.m_Math + a.m_English + a.m_Cpp + a.m_Qt;
            int totalB = b.m_Math + b.m_English + b.m_Cpp + b.m_Qt;
            return totalA > totalB;
        });

    std::cout << "===== 成绩排名 =====" << std::endl;

    for (size_t i = 0; i < stus.size(); ++i) {
        int total = stus[i].m_Math + stus[i].m_English +
            stus[i].m_Cpp + stus[i].m_Qt;

        std::cout << "第" << i + 1 << "名 "
            << "ID：" << stus[i].m_ID
            << " 姓名：" << stus[i].m_Name
            << " 总成绩：" << total << std::endl;
    }
}

void GradeStatistics::analysisGrade() {
    auto& stus = m_Manager.m_Stus;

    if (stus.empty()) {
        std::cout << "暂无学生数据！" << std::endl;
        return;
    }

    int mathTotal = 0;
    int englishTotal = 0;
    int cppTotal = 0;
    int qtTotal = 0;

    int maxTotal = -1;
    int minTotal = 999999;

    for (const Student& stu : stus) {
        int total = stu.m_Math + stu.m_English +
            stu.m_Cpp + stu.m_Qt;

        mathTotal += stu.m_Math;
        englishTotal += stu.m_English;
        cppTotal += stu.m_Cpp;
        qtTotal += stu.m_Qt;

        if (total > maxTotal)
            maxTotal = total;

        if (total < minTotal)
            minTotal = total;
    }

    int count = static_cast<int>(stus.size());

    std::cout << "===== 成绩分析 =====" << std::endl;
    std::cout << std::fixed << std::setprecision(2);

    std::cout << "学生人数：" << count << std::endl;
    std::cout << "数学平均分：" << static_cast<double>(mathTotal) / count << std::endl;
    std::cout << "英语平均分：" << static_cast<double>(englishTotal) / count << std::endl;
    std::cout << "Cpp平均分：" << static_cast<double>(cppTotal) / count << std::endl;
    std::cout << "Qt平均分：" << static_cast<double>(qtTotal) / count << std::endl;
    std::cout << "最高总分：" << maxTotal << std::endl;
    std::cout << "最低总分：" << minTotal << std::endl;
}

