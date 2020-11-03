#pragma once
#include <iostream>
#include "worker.h"
using namespace std;
//经理类
class Manager :public Worker
{
public:
	//构造
	Manager(int id, string name, int did);
	//显示个人信息
	virtual void showInfo();
	//获取岗位名称
	virtual string getDepartName();
};