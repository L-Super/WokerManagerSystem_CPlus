#pragma once
//��ֹͷ�ļ��ظ�����
#include <iostream>
#include <string>
#include <fstream>
#include "worker.h"
#define FILENAME "File.txt"
using namespace std;
class WorkManager
{
public:
	//���캯��
	WorkManager();
	//չʾ�˵�
	void Show_Menu();
	//��¼ְ������
	int m_EmpNum;
	//ְ������ָ��
	Worker** m_EmpArray;
	//���ְ��
	void Add_Emp();
	//�����ļ�
	void save();
	//�ж��ļ��Ƿ�Ϊ�� ��־
	bool m_FileIsEmpty;
	//ͳ���ļ��е�����
	int get_EmpNum();
	//��ʼ��Ա��
	void init_Emp();
	//��ʾְ��
	void ShowEmp();
	//ɾ��ְ��
	void Del_Emp();
	//�ж�ְ���Ƿ���� ������ڷ���ְ�����������е�λ�ã������ڷ���-1
	int IsExist(int id);
	//�޸�ְ��
	void Mod_Emp();

	void exitsystem();
	~WorkManager();
private:

};
