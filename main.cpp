#include<iostream>
#include<windows.h>
#include"StuManager.h"
#include"GradeStatistics.h"
StuManager sm;
GradeStatistics gs(sm);

void stuUI() {
	std::cout << "===============" << std::endl;
	std::cout << "    学生界面    " << std::endl;
	std::cout << "===============" << std::endl;
	std::cout << "1. 查询个人信息" << std::endl;
	std::cout << "2. 查询个人成绩" << std::endl;
	std::cout << "0. 退出" << std::endl;

	int choose;
	while (true) {
		std::cout << ">请选择序号：";
		std::cin >> choose;

		// 页面跳转
		switch (choose) {
		case 1:
			std::cout << "<查询个人信息" << std::endl;
			sm.findStu(1);
			break;
		case 2:
			std::cout << "<查询个人成绩" << std::endl;
			sm.findStu(2);
			break;
		case 0:
			std::cout << "<退出成功" << std::endl;
			return;
		default:
			std::cout << "<请正确输入" << std::endl;
			continue;
		}
	}
}
void teaUI() {
	int choose;
	while (true) {
		std::cout << "===============" << std::endl;
		std::cout << "    教师界面    " << std::endl;
		std::cout << "===============" << std::endl;
		std::cout << "1. 添加学生" << std::endl;
		std::cout << "2. 删掉学生" << std::endl;
		std::cout << "3. 修改学生" << std::endl;
		std::cout << "4. 查询学生" << std::endl;
		std::cout << "5. 排序成绩" << std::endl;
		std::cout << "6. 统计成绩" << std::endl;
		std::cout << "0. 退出" << std::endl;
		std::cout << ">请选择序号：";
		std::cin >> choose;

		// 页面跳转
		switch (choose) {
		case 1:
			std::cout << "<添加学生" << std::endl;
			sm.addStu();
			break;
		case 2:
			std::cout << "<删掉学生" << std::endl;
			sm.delStu();
			break;
		case 3:
			std::cout << "<修改学生" << std::endl;
			sm.revStu();
			break;
		case 4:
			std::cout << "<查询学生" << std::endl;
			sm.findStu(3);
			break;
		case 5:
			std::cout << "<排序成绩" << std::endl;
			gs.sortGrade();
			break;
		case 6:
			std::cout << "<统计成绩" << std::endl;
			gs.analysisGrade();
			break;
		case 0:
			std::cout << "<退出成功" << std::endl;
			return;
		default:
			std::cout << "<请正确输入" << std::endl;
			continue;
		}
	}
}

void indexUI() {
	int choose;
	while (true) {
		std::cout << "===============" << std::endl;
		std::cout << "学生成绩管理系统" << std::endl;
		std::cout << "===============" << std::endl;
		std::cout << "1. 学生登入" << std::endl;
		std::cout << "2. 教师登入" << std::endl;
		std::cout << "0. 退出" << std::endl;
		std::cout << ">请选择序号：";
		std::cin >> choose;

		// 页面跳转
		switch (choose) {
		case 1:
			std::cout << "<进入学生系统" << std::endl;
			stuUI();// 进入学生系统
			break;
		case 2:
			std::cout << "<进入教师系统" << std::endl;
			teaUI();// 进入教师系统
			break;
		case 0:
			std::cout << "<退出成功" << std::endl;
			return;
		default:
			std::cout << "<请正确输入" << std::endl;
			continue;
		}
	}

}

int main() {
	SetConsoleCP(CP_UTF8);
	SetConsoleOutputCP(CP_UTF8);

	sm.loadStus();
	//std::cout << sm.m_Stus.back().m_ID << std::endl;

	indexUI();
	
	
	return 0;
}