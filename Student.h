#pragma once
#include<iostream>
#include<chrono>
class Student {
public:
	//20260001 | 张伟 | 2005 - 03 - 20 | 63 | 93 | 85 | 72 | 0001
	int m_ID;
	std::string m_Name;
	std::chrono::year_month_day m_Birth;
	int m_Math;
	int m_English;
	int m_Cpp;
	int m_Qt;
private:
	int m_Key;
	friend class StuManager;
	friend bool loginUI(int choose);
};