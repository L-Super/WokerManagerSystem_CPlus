#pragma once
//��ְͨ���ļ�
#include <iostream>
#include "worker.h"
using namespace std;
class Employee:public Worker
{
public:
	//����
	Employee(int id,string name,int did);
	//��ʾ������Ϣ
	virtual void showInfo();
	//��ȡ��λ����
	virtual string getDepartName();

};
