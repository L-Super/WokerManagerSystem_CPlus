#include "boss.h"
//����
Boss::Boss(int id, string name, int dId)
{
	this->m_id = id;
	this->m_name = name;
	this->m_deptid = dId;
}
//��ʾ������Ϣ
void Boss::showInfo()
{
	cout << "ְ����ţ� " << this->m_id
		<< "\tְ�������� " << this->m_name;
	cout << "\t��λ�� ";
	cout << this->getDepartName();

	cout << "\t��λְ�� ����˾����ְ�� " << endl;
}
//��ȡ��λ����
string Boss::getDepartName()
{
	return string("Boss");
}