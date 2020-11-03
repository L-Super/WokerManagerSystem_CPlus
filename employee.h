#pragma once
//普通职工文件
#include <iostream>
#include "worker.h"
using namespace std;
class Employee:public Worker
{
public:
	//构造
	Employee(int id,string name,int did);
	//显示个人信息
	virtual void showInfo();
	//获取岗位名称
	virtual string getDepartName();

};
