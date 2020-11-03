#include "employee.h"
//#include <iostream>
Employee::Employee(int id,string name,int did)
{
	this->m_id = id;
	this->m_name = name;
	this->m_deptid = did;
 }
void Employee::showInfo()
{
	cout << "职工编号： " << this->m_id
		<< "\t职工姓名： " << this->m_name;
	cout << "\t岗位： ";
	cout << this->getDepartName();

	cout<<"\t岗位职责： 完成任务 " << endl;
}
string Employee::getDepartName()
{
	return string("员工");
}