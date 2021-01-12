#include "WorkerManager.h"
#include "worker.h"
#include "employee.h"
#include "boss.h"
#include "manager.h"
WorkManager::WorkManager()
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
int WorkManager::get_EmpNum()
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

WorkManager::~WorkManager()
{
	if (this->m_EmpArray != NULL)
	{
		delete[] this->m_EmpArray;
		this->m_EmpArray = NULL;
	}
}

void WorkManager::Show_Menu()
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
void WorkManager::exitsystem()
{
	cout << "ϵͳ���˳�����ӭ�´�ʹ�ã�" << endl;
	//system("pause");
	exit(0);
}

//���ְ��
void WorkManager::Add_Emp()
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
void WorkManager::save()
{
	ofstream ofs;
	ofs.open(FILENAME, ios::out);//�����ģʽ���ļ�
	//����д���ļ�
	for (int i = 0; i < this->m_EmpNum; i++)
	{
		ofs << this->m_EmpArray[i]->m_id << "  "
			<< this->m_EmpArray[i]->m_name << "  "
			<< this->m_EmpArray[i]->m_deptid << endl;
	}
	ofs.close();
}

//��ʼ��Ա��
void WorkManager::init_Emp()
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
void WorkManager::ShowEmp()
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
//ɾ��ְ��
void WorkManager::Del_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ��¼Ϊ�գ�" << endl;
	}
	else
	{
		//���ձ��ɾ��
		cout << "������Ҫɾ����ְ�����" << endl;
		int id = 0;
		cin >> id;
		int index = this->IsExist(id);
		if (index != -1)//˵������
		{
			//����ǰ��
			for (int i = index; i < this->m_EmpNum - 1; i++)
			{
				this->m_EmpArray[i] = this->m_EmpArray[i + 1];
			}
			this->m_EmpNum--;//���������м�¼������
			//����ͬ�����ļ���
			this->save();
			cout << "ɾ���ɹ�" << endl;
		}
		else
		{
			cout << "ɾ��ʧ�ܣ�δ�ҵ�" << endl;
		}
	}
	
}
//�ж�ְ���Ƿ���� ������ڷ���ְ�����������е�λ�ã������ڷ���-1
int WorkManager::IsExist(int id)
{
	int index = -1;
	for (int i = 0; i < this->m_EmpNum; i++)
	{
		if (this->m_EmpArray[i]->m_id == id)
		{
			//found worker
			index = i;
			break;
		}
	}
	return index;
}
//�޸�ְ��
void WorkManager::Mod_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ��¼Ϊ�գ�" << endl;
	}
	else
	{
		
		//���ձ��ɾ��
		cout << "������Ҫ�޸ĵ�ְ�����" << endl;
		int id = 0;
		cin >> id;
		int ret = this->IsExist(id);
		if (ret != -1)
		{
			//���Ҹñ��ְ��
			delete this->m_EmpArray[ret];
			int newId = 0;
			string newName = " ";
			int dSelcet = 0;
			cout << "�鵽�� " << id << "��ְ����������ְ���ţ� " << endl;
			cin >> newId;
			//cout << "������������ " << endl;
			//cin >> newName;
			cout << "�����λ��\n1��ְ��\n2������\n3���ϰ�" << endl;
			cin >> dSelcet;
			Worker* worker = NULL;
			switch (dSelcet)
			{
			case 1:
				//const string name=Employee::Employee-> m_name;
				//û�����޸����������ڿɳ���
				worker = new Employee(newId, newName, dSelcet);
				break;
			case 2:
				worker = new Manager(newId, newName, dSelcet);

				break;
			case 3:
				worker = new Boss(newId, newName, dSelcet);

				break;
			default:
				break;
			}
			//�������ݵ�������
			this->m_EmpArray[ret] = worker;
			cout << "�޸ĳɹ���" << endl;
			//���浽�ļ���
			this->save();

		}
		else
			cout << "�޸�ʧ�ܣ����޴��ˣ�" << endl;
	}
}

//����ְ��
void WorkManager::Find_Emp()
{
	if (this->m_FileIsEmpty)
		cout << "�ļ������ڻ�Ϊ��!" << endl;
	else
	{
		cout << "��������ҵķ�ʽ:" << endl;
		cout << "1����ְ����Ų���" << endl;
		cout << "2����ְ����������" << endl;
		int select = 0;
		cin >> select;
		if (select == 1)
		{
			//���ձ�Ų�
			int id;
			cout << "������ҵ�ְ����ţ�" << endl;
			cin >> id;
			int ret = IsExist(id);
			if (ret != -1)
			{
				//�ҵ�ְ��
				cout << "���ҳɹ�����ְ����Ϣ����" << endl;
				this->m_EmpArray[ret]->showInfo();
			}
			else
				cout << "����ʧ�ܣ����޴���" << endl;
		}
		else if (select == 2)
		{
			//����������
			string name;
			
			cout << "��������ҵ�������" << endl;
			cin >> name;
			//�����ж��Ƿ�鵽�ı�־
			bool flag = false;
			for (int i = 0; i < m_EmpNum; i++)
			{
				if (this->m_EmpArray[i]->m_name == name)
				{
					cout << "���ҳɹ���ְ�����Ϊ��" << this->m_EmpArray[i]->m_id << "��ְ����Ϣ���£�" << endl;
					flag = true;
					this->m_EmpArray[i]->showInfo();

				}
			}
			if (flag == false)
				cout << "����ʧ�ܣ����޴��ˣ�" << endl;
		}
		else
			cout << "����ѡ������" << endl;
	}
	system("pause");
	//system("cls");
}