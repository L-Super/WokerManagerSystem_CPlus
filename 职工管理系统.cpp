#include <iostream>
#include "WorkerManager.h"
#include "worker.h"
#include "employee.h"
#include "boss.h"
#include "manager.h"
using namespace std;
int main()
{
	//test
	//Worker* worker = NULL;//������NULL��newʧ�ܵĻ����ͻ���Ұָ��
	////Worker* worker = 0;//����0Ҳ����
	//worker = new Employee(1, "jack", 1);
	//worker->showInfo();
	//delete worker;
	//worker = new Manager(2, "tom", 2);
	//worker->showInfo();
	//delete worker;
	//worker = new Boss(3, "bob", 3);
	//worker->showInfo();
	//delete worker;

	/*++++++++++++++++++++++++++++++++++++++++++++++++++*/

	//ʵ���������߶���
	WorkManager w;
	int choice = 0;//�û�ѡ��
	/*cout << "����ѡ��" << endl;
	w.Show_Menu();*/
	while (true)
	{
		w.Show_Menu();
		cout << "����ѡ��" << endl;
		cin >> choice;
		switch (choice)
		{
			//�˳�ϵͳ
		case 0:
			w.exitsystem();
			break;

			//����Ա��
		case 1:
			w.Add_Emp();
			break;

			//��ʾԱ��
		case 2:
			w.ShowEmp();
			break;

			//ɾ��Ա��
		case 3:
		//{//����
		//	int ret = w.IsExist(1);
		//	if (ret != -1)
		//		cout << "ְ������" << endl;
		//	else
		//		cout << "ְ��������" << endl;

		//	break; 
		//}
			w.Del_Emp();
			break;

			//�޸�Ա��
		case 4:
			w.Mod_Emp();
			break;

			//����ְ��
		case 5:
			w.Find_Emp();
			break;

			//ְ������
		case 6:
			w.Sort_Emp();
			break;

			//����ĵ�
		case 7:
			w.Clean_File();
			break;

		default:
			//����
			system("cls");
			break;
		}
		//w.Show_Menu();
	}

	return 0;
}