#include "boss.h"
//构造
Boss::Boss(int id, string name, int dId)
{
	this->m_id = id;
	this->m_name = name;
	this->m_deptid = dId;
}
//显示个人信息
void Boss::showInfo()
{
	cout << "职工编号： " << this->m_id
		<< "\t职工姓名： " << this->m_name;
	cout << "\t岗位： ";
	cout << this->getDepartName();

	cout << "\t岗位职责： 管理公司所有职务 " << endl;
}
//获取岗位名称
string Boss::getDepartName()
{
	return string("Boss");
}