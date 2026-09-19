#pragma once
#include"Student.h"
#include<vector>
#include<unordered_map>

class StuManager {
private:
	std::vector<Student> m_Stus;
	std::unordered_map<int, int> m_StusIndex;
	friend class GradeStatistics;

public:
	void loadStus();
	void saveStus();
	void addStu();
	void delStu();
	void revStu();
	int findStu(int choose);
};