#pragma once
#include <iostream>
#include "worker.h"
using namespace std;
//BOSS��
class Boss :public Worker
{
public:
	//����
	Boss(int id, string name, int dId);
	//��ʾ������Ϣ
	virtual void showInfo();
	//��ȡ��λ����
	virtual string getDepartName();
};