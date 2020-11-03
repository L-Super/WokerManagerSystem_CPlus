#include "manager.h"
//构造
Manager::Manager(int id, string name, int did)
{
	this->m_id = id;
	this->m_name = name;
	this->m_deptid = did;
}
//显示个人信息
void Manager::showInfo()
{
	cout << "职工编号： " << this->m_id
		<< "\t职工姓名： " << this->m_name;
	cout << "\t岗位： ";
	cout << this->getDepartName();

	cout << "\t岗位职责： 完成boss任务 " << endl;
}
//获取岗位名称
string Manager::getDepartName()
{
	return string("经理");
}