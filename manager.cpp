#include "manager.h"
//����
Manager::Manager(int id, string name, int did)
{
	this->m_id = id;
	this->m_name = name;
	this->m_deptid = did;
}
//��ʾ������Ϣ
void Manager::showInfo()
{
	cout << "ְ����ţ� " << this->m_id
		<< "\tְ�������� " << this->m_name;
	cout << "\t��λ�� ";
	cout << this->getDepartName();

	cout << "\t��λְ�� ���boss���� " << endl;
}
//��ȡ��λ����
string Manager::getDepartName()
{
	return string("����");
}