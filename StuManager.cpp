#include"StuManager.h"
#include <fstream> 
#include <iostream> 
#include <string>
#include <iomanip>

void StuManager::loadStus() {
	// 打开读文件
	std::ifstream file("./students.txt");
	if(!file.is_open()) {
		std::cout << "文件打开失败\n";
		return;
	}

	std::string line;
	while (std::getline(file, line)) {
		//20260001 | 张伟 | 2005 - 03 - 20 | 63 | 93 | 85 | 72 | 0001
		std::stringstream ss(line);

		std::string id;
		std::string name;
		std::string birth;
		std::string math;
		std::string english;
		std::string cpp;
		std::string qt;
		std::string key;

		std::getline(ss, id, '|');
		std::getline(ss, name, '|');
		std::getline(ss, birth, '|');
		std::getline(ss, math, '|');
		std::getline(ss, english, '|');
		std::getline(ss, cpp, '|');
		std::getline(ss, qt, '|');
		std::getline(ss, key, '|');

		// 创建Student对象
		Student stu;
		stu.m_ID = std::stoi(id);
		stu.m_Name = name;
		//提取日期
		int year = std::stoi(birth.substr(0, 4));
		int month = std::stoi(birth.substr(5, 2));
		int day = std::stoi(birth.substr(8, 2));

		stu.m_Birth = std::chrono::year_month_day{
			std::chrono::year{year},
			std::chrono::month{static_cast<unsigned>(month)},
			std::chrono::day{static_cast<unsigned>(day)}
		};
		stu.m_Math = std::stoi(math);
		stu.m_English = std::stoi(english);
		stu.m_Cpp = std::stoi(cpp);
		stu.m_Qt = std::stoi(qt);
		stu.m_Key = stu.m_ID %10000;

		// 用vector放Student，map建立学号索引
		m_Stus.push_back(stu);
		m_StusIndex[stu.m_ID] = m_Stus.size() - 1;
	}

	file.close();

}

void StuManager::saveStus() {
	// 打开写文件
	std::ofstream file("./students.txt", std::ios::out | std::ios::trunc);
	if (!file.is_open()) {
		std::cout << "文件打开失败，保存失败！" << std::endl;
		return;
	}

	for (const Student& stu : m_Stus) {
		auto year = int(stu.m_Birth.year());
		auto month = unsigned(stu.m_Birth.month());
		auto day = unsigned(stu.m_Birth.day());

		file<<stu.m_ID<<'|'
			<<stu.m_Name<<'|'
			<< year << "-"<< std::setfill('0') << std::setw(2) 
			<< month << "-"<< std::setw(2) 
			<< day << std::setfill(' ') << '|'
			<< stu.m_Math << '|'
			<< stu.m_English << '|'
			<< stu.m_Cpp << '|'
			<< stu.m_Qt << '|'
			<< std::setfill('0') << std::setw(4) << stu.m_Key
			<< std::setfill(' ') << "\n";
	}

	if (file.fail()) {
		std::cout << "文件写入失败！" << std::endl;
		return;
	}

	file.close();
}

void StuManager::addStu() {
	std::string name;
	std::string birth;
	int math;
	int english;
	int cpp;
	int qt;

	std::cout << "姓名：";
	std::cin >> name;
	std::cout << "出生日期：";
	std::cin >> birth;
	std::cout << "数学：";
	std::cin >> math;
	std::cout << "英语：";
	std::cin >> english;
	std::cout << "CPP：";
	std::cin >> cpp;
	std::cout << "Qt：";
	std::cin >> qt;

	Student stu;
	stu.m_ID = m_Stus.back().m_ID + 1;
	stu.m_Name = name;
	//提取日期
	int year = std::stoi(birth.substr(0, 4));
	int month = std::stoi(birth.substr(5, 2));
	int day = std::stoi(birth.substr(8, 2));

	stu.m_Birth = std::chrono::year_month_day{
		std::chrono::year{year},
		std::chrono::month{static_cast<unsigned>(month)},
		std::chrono::day{static_cast<unsigned>(day)}
	};
	stu.m_Math = math;
	stu.m_English = english;
	stu.m_Cpp = cpp;
	stu.m_Qt = qt;
	stu.m_Key = stu.m_ID % 10000;

	// 更新容器
	m_Stus.push_back(stu);
	m_StusIndex.clear();
	for (int i = 0; i < m_Stus.size(); i++)	{
		m_StusIndex[m_Stus[i].m_ID] = i;
	}
	// 更新文件
	saveStus();
}

int StuManager::findStu(int choose) {
	int id;
	std::cout << "ID：";
	std::cin >> id;

	// 更具ID查找下标
	auto it = m_StusIndex.find(id);
	if(it==m_StusIndex.end()){
		std::cout << "没有找到该学生！" << std::endl;
		return -1;
	}

	//找到了，获取vector下标
	int index = it->second;

	//根据下标找到学生信息
	Student& stu = m_Stus[index];

	switch (choose) {
	case 0:break;
	case 1:std::cout << stu.m_ID << '|'
		<< stu.m_Name << '|'
		<< stu.m_Birth << std::endl;
		break;
	case 2:std::cout << stu.m_Math << '|'
		<< stu.m_English << '|'
		<< stu.m_Cpp << '|'
		<< stu.m_Qt << std::endl;
		break;
	case 3:	std::cout << stu.m_ID << '|'
		<< stu.m_Name << '|'
		<< stu.m_Birth << '|'
		<< stu.m_Math << '|'
		<< stu.m_English << '|'
		<< stu.m_Cpp << '|'
		<< stu.m_Qt << std::endl;
	}


	return index;
}

void StuManager::delStu() {
	int index = findStu(0);

	if (index == -1) {
		return;
	}

	int id = m_Stus[index].m_ID;

	m_Stus.erase(m_Stus.begin() + index);
	m_StusIndex.erase(id);

	// 重新建立索引
	m_StusIndex.clear();

	for (size_t i = 0; i < m_Stus.size(); ++i) {
		m_StusIndex[m_Stus[i].m_ID] = i;
	}

	saveStus();

	std::cout << "删除成功！" << std::endl;
}

void StuManager::revStu() {
	int index = findStu(0);

	if (index == -1) {
		return;
	}

	Student& stu = m_Stus[index];

	int choice;
	while (true) {
		std::cout << "\n===== 修改学生信息 =====" << std::endl;
		std::cout << "1. 修改姓名" << std::endl;
		std::cout << "2. 修改出生日期" << std::endl;
		std::cout << "3. 修改数学成绩" << std::endl;
		std::cout << "4. 修改英语成绩" << std::endl;
		std::cout << "5. 修改CPP成绩" << std::endl;
		std::cout << "6. 修改Qt成绩" << std::endl;
		std::cout << "0. 取消修改" << std::endl;
		std::cout << ">请选择序号：";
		std::cin >> choice;

		switch (choice) {
		case 1:
			std::cout << ">请输入新姓名：";
			std::cin >> stu.m_Name;
			break;

		case 2:
		{
			std::string birth;
			std::cout << ">请输入新的出生日期：";
			std::cin >> birth;

			int year = std::stoi(birth.substr(0, 4));
			int month = std::stoi(birth.substr(5, 2));
			int day = std::stoi(birth.substr(8, 2));

			stu.m_Birth = std::chrono::year_month_day{
				std::chrono::year{year},
				std::chrono::month{static_cast<unsigned>(month)},
				std::chrono::day{static_cast<unsigned>(day)}
			};

			break;
		}

		case 3:
			std::cout << ">请输入新的数学成绩：";
			std::cin >> stu.m_Math;
			break;

		case 4:
			std::cout << ">请输入新的英语成绩：";
			std::cin >> stu.m_English;
			break;

		case 5:
			std::cout << ">请输入新的CPP成绩：";
			std::cin >> stu.m_Cpp;
			break;

		case 6:
			std::cout << ">请输入新的Qt成绩：";
			std::cin >> stu.m_Qt;
			break;

		case 0:
			std::cout << "<取消修改。" << std::endl;
			return;

		default:
			std::cout << "<请正确输入" << std::endl;
			continue;
		}
	}
	

	saveStus();

	std::cout << "修改成功！" << std::endl;
}