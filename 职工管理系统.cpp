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
	//Worker* worker = NULL;//不先设NULL，new失败的话，就会变成野指针
	////Worker* worker = 0;//设置0也可以
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

	//实例化管理者对象
	WorkManager w;
	int choice = 0;//用户选项
	/*cout << "输入选项" << endl;
	w.Show_Menu();*/
	while (true)
	{
		w.Show_Menu();
		cout << "输入选项" << endl;
		cin >> choice;
		switch (choice)
		{
			//退出系统
		case 0:
			w.exitsystem();
			break;

			//增加员工
		case 1:
			w.Add_Emp();
			break;

			//显示员工
		case 2:
			w.ShowEmp();
			break;

			//删除员工
		case 3:
		//{//测试
		//	int ret = w.IsExist(1);
		//	if (ret != -1)
		//		cout << "职工存在" << endl;
		//	else
		//		cout << "职工不存在" << endl;

		//	break; 
		//}
			w.Del_Emp();
			break;

			//修改员工
		case 4:
			w.Mod_Emp();
			break;

			//查找职工
		case 5:
			w.Find_Emp();
			break;

			//职工排序
		case 6:
			w.Sort_Emp();
			break;

			//清空文档
		case 7:
			w.Clean_File();
			break;

		default:
			//清屏
			system("cls");
			break;
		}
		//w.Show_Menu();
	}

	return 0;
}