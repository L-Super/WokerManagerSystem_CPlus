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
	cout << "ְ����ţ� " << this->m_id
		<< "\tְ�������� " << this->m_name;
	cout << "\t��λ�� ";
	cout << this->getDepartName();

	cout<<"\t��λְ�� ������� " << endl;
}
string Employee::getDepartName()
{
	return string("Ա��");
}