#include "WorkerManager.h"
#include "worker.h"
#include "employee.h"
#include "boss.h"
#include "manager.h"
WorkManger::WorkManger()
{
	//1���ļ�������
	ifstream ifs;
	ifs.open(FILENAME, ios::in);//���ļ�
	if (!ifs.is_open())
	{
		cout << "�ļ������ڣ�" << endl;
		//��ʼ������
		//��ʼ����¼����
		this->m_EmpNum = 0;
		//��ʼ������ָ��
		this->m_EmpArray = NULL;
		//��ʼ���ļ��Ƿ�Ϊ��
		this->m_FileIsEmpty = true;
		ifs.close();
		return;//return�����Ϊ����������ǿ�ƽ����������÷�������ѭ���ṹ�е�break�������á�
	}
	//2���ļ����ڣ�����Ϊ��
	char ch;
	ifs >> ch;
	if (ifs.eof())//���ж��ļ��Ƿ�Ϊ�ջ����Ƿ�����ļ���β
	{
		//�ļ�Ϊ��
		cout << "�ļ�Ϊ��" << endl;
		//��ʼ����¼����
		this->m_EmpNum = 0;
		//��ʼ������ָ��
		this->m_EmpArray = NULL;
		//��ʼ���ļ��Ƿ�Ϊ��
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}
	//3���ļ����ڣ��Ҵ�������
	int num = this->get_EmpNum();
	cout << "ְ�������� " << num << endl;
	this->m_EmpNum = num;

	//���ٿռ�
	this->m_EmpArray = new Worker * [this->m_EmpNum];
	//���ļ��е����ݴ���������
	this->init_Emp();

	//test
/*	for (int i = 0; i < this->m_EmpNum; i++)
	{
		cout << "ְ����� : " << this->m_EmpArray[i]->m_id<<endl;
		cout << "ְ������ : " << this->m_EmpArray[i]->m_name<<endl;
		cout << "ְ������ : " << this->m_EmpArray[i]->m_deptid<<endl;

	}
	*/
}
		
//ͳ���ļ��е�����
int WorkManger::get_EmpNum()
{
	ifstream ifs2;
	ifs2.open(FILENAME, ios::in);//���ļ������ļ�
	int id;
	string name;
	int dId;
	int num = 0;
	while (ifs2>>id&&ifs2>>name&&ifs2>>dId)
	{
		//ͳ����������
		num++;
	}
	return num;
}

WorkManger::~WorkManger()
{
	if (this->m_EmpArray != NULL)
	{
		delete[] this->m_EmpArray;
		this->m_EmpArray = NULL;
	}
}

void WorkManger::Show_Menu()
{
	cout << "*********************" << endl;
	cout << "��ӭʹ��ְ������ϵͳ" << endl;
	cout << "1.����ְ����Ϣ" << endl;
	cout << "2.��ʾְ����Ϣ" << endl;
	cout << "3.ɾ����ְְ��" << endl;
	cout << "4.�޸�ְ����Ϣ" << endl;
	cout << "5.����ְ����Ϣ" << endl;
	cout << "6.���ձ������" << endl;
	cout << "7.��������ĵ�" << endl;
	cout << "0.�˳�����ϵͳ" << endl;
	cout << "++++++++++++++++++++++" << endl;
	cout << endl;
}
void WorkManger::exitsystem()
{
	cout << "ϵͳ���˳�����ӭ�´�ʹ�ã�" << endl;
	//system("pause");
	exit(0);
}

//���ְ��
void WorkManger::Add_Emp()
{
	cout << "�������ְ������:" << endl;
	int addNum = 0;//�����û���������
	cin >> addNum;
	if (addNum > 0)
	{
		//���
		//��������¿ռ��С
		int newSize = this->m_EmpNum + addNum;//�¿ռ�����
		//�����¿ռ�
		
		Worker** newSpace = new Worker * [newSize];
		
		//��ԭ���ռ������ݣ��������¿ռ�
		if (this->m_EmpArray != NULL)
		{
			for (int i = 0; i < this->m_EmpNum; i++)
				newSpace[i] = this->m_EmpArray[i];
		}
		//���������
		for (int i = 0; i < addNum; i++)
		{
			int id;
			string name;
			int dSelect;//����
			cout << "�����" << i + 1 << "����ְ����ţ�" << endl;
			cin >> id;
			cout << "�����" << i + 1 << "����ְ��������" << endl;
			cin >> name;
			cout << "ѡ����ְ����λ��" << endl;
			cout << "1.��ְͨ��" << endl;
			cout << "2.����" << endl;
			cout << "3.BOSS" << endl;
			cin >> dSelect;
			Worker* worker = NULL;
			switch (dSelect)
			{
			case 1:
				worker = new Employee(id, name, 1);
				break;
			case 2:
				worker = new Manager(id, name, 2);
				break;
			case 3:
				worker = new Boss(id, name, 3);
				break;

			default:
				break;
			}
			//������ְ��ָ�룬������������
			//�����ڴ��������
			newSpace[this->m_EmpNum + i] = worker;

		}
		//�ͷ�ԭ�пռ�
		delete[] this->m_EmpArray;
		//�����¿ռ�ָ��
		this->m_EmpArray = newSpace;
		//������ְ������
		this->m_EmpNum = newSize;

		//����ְ���ļ���Ϊ�յı�־
		this->m_FileIsEmpty = false;
		
		//��ʾ��ӳɹ�
		cout << "�ɹ����" << addNum << "����ְ����" << endl;
		//save
		this->save();
	}
	else
	{
		cout << "������������" << endl;
	}
	system("pause");
}

//�����ļ�
void WorkManger::save()
{
	ofstream ofs;
	ofs.open(FILENAME, ios::out);//�����ģʽ���ļ�
	//����д���ļ�
	for (int i = 0; i < this->m_EmpNum; i++)
	{
		ofs << this->m_EmpArray[i]->m_id << " "
			<< this->m_EmpArray[i]->m_name << " "
			<< this->m_EmpArray[i]->m_deptid << endl;
	}
	ofs.close();
}

//��ʼ��Ա��
void WorkManger::init_Emp()
{
	ifstream ifs3;
	ifs3.open(FILENAME, ios::in);
	int id;
	string name;
	int dId;
	int index = 0;
	while (ifs3 >> id && ifs3 >> name && ifs3 >> dId)
	{
		Worker* worker = NULL;
		if (dId == 1)//��ְͨ��
		{
			worker = new Employee(id, name, dId);
		}
		else if(dId==2)//����
			worker = new Manager(id, name, dId);
		else
			worker = new Boss(id, name, dId);
		this->m_EmpArray[index] = worker;
		index++;
	}
	ifs3.close();
}

//��ʾְ��
void WorkManger::ShowEmp()
{
	//�ж��ļ��Ƿ�Ϊ��
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ��¼Ϊ�գ�" << endl;
	}
	else
	{
		for (int i = 0; i < m_EmpNum; i++)
		{
			//���ö�̬�ӿ�
			this->m_EmpArray[i]->showInfo();
		}
	}
	system("pause");
	system("cls");
}