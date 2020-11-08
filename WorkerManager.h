#pragma once
//防止头文件重复包含
#include <iostream>
#include <string>
#include <fstream>
#include "worker.h"
#define FILENAME "File.txt"
using namespace std;
class WorkManager
{
public:
	//构造函数
	WorkManager();
	//展示菜单
	void Show_Menu();
	//记录职工人数
	int m_EmpNum;
	//职工数组指针
	Worker** m_EmpArray;
	//添加职工
	void Add_Emp();
	//保存文件
	void save();
	//判断文件是否为空 标志
	bool m_FileIsEmpty;
	//统计文件中的人数
	int get_EmpNum();
	//初始化员工
	void init_Emp();
	//显示职工
	void ShowEmp();
	//删除职工
	void Del_Emp();
	//判断职工是否存在 如果存在返回职工所在数组中的位置，不存在返回-1
	int IsExist(int id);
	//修改职工
	void Mod_Emp();

	void exitsystem();
	~WorkManager();
private:

};
