#pragma once
#include <iostream>
#include <string>
using namespace std;
//职工抽象类
class Worker
{
public:
	//显示个人信息
	virtual void showInfo() = 0;
	//获取岗位名称
	virtual string getDepartName() = 0;
	//职工编号
	int m_id;
	//职工姓名
	string m_name;
	//部门编号
	int m_deptid;
};