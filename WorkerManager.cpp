#include "WorkerManager.h"
#include "worker.h"
#include "employee.h"
#include "boss.h"
#include "manager.h"
WorkManger::WorkManger()
{
	//1、文件不存在
	ifstream ifs;
	ifs.open(FILENAME, ios::in);//读文件
	if (!ifs.is_open())
	{
		cout << "文件不存在！" << endl;
		//初始化属性
		//初始化记录人数
		this->m_EmpNum = 0;
		//初始化数组指针
		this->m_EmpArray = NULL;
		//初始化文件是否为空
		this->m_FileIsEmpty = true;
		ifs.close();
		return;//return语句是为了引起函数的强制结束，这种用法类似于循环结构中的break语句的作用。
	}
	//2、文件存在，数据为空
	char ch;
	ifs >> ch;
	if (ifs.eof())//来判断文件是否为空或者是否读到文件结尾
	{
		//文件为空
		cout << "文件为空" << endl;
		//初始化记录人数
		this->m_EmpNum = 0;
		//初始化数组指针
		this->m_EmpArray = NULL;
		//初始化文件是否为空
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}
	//3、文件存在，且存在数据
	int num = this->get_EmpNum();
	cout << "职工人数： " << num << endl;
	this->m_EmpNum = num;

	//开辟空间
	this->m_EmpArray = new Worker * [this->m_EmpNum];
	//将文件中的数据存入数组中
	this->init_Emp();

	//test
/*	for (int i = 0; i < this->m_EmpNum; i++)
	{
		cout << "职工编号 : " << this->m_EmpArray[i]->m_id<<endl;
		cout << "职工姓名 : " << this->m_EmpArray[i]->m_name<<endl;
		cout << "职工部门 : " << this->m_EmpArray[i]->m_deptid<<endl;

	}
	*/
}
		
//统计文件中的人数
int WorkManger::get_EmpNum()
{
	ifstream ifs2;
	ifs2.open(FILENAME, ios::in);//打开文件，读文件
	int id;
	string name;
	int dId;
	int num = 0;
	while (ifs2>>id&&ifs2>>name&&ifs2>>dId)
	{
		//统计人数变量
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
	cout << "欢迎使用职工管理系统" << endl;
	cout << "1.增加职工信息" << endl;
	cout << "2.显示职工信息" << endl;
	cout << "3.删除离职职工" << endl;
	cout << "4.修改职工信息" << endl;
	cout << "5.查找职工信息" << endl;
	cout << "6.按照编号排序" << endl;
	cout << "7.清空所有文档" << endl;
	cout << "0.退出管理系统" << endl;
	cout << "++++++++++++++++++++++" << endl;
	cout << endl;
}
void WorkManger::exitsystem()
{
	cout << "系统已退出，欢迎下次使用！" << endl;
	//system("pause");
	exit(0);
}

//添加职工
void WorkManger::Add_Emp()
{
	cout << "输入添加职工数量:" << endl;
	int addNum = 0;//保存用户输入数量
	cin >> addNum;
	if (addNum > 0)
	{
		//添加
		//计算添加新空间大小
		int newSize = this->m_EmpNum + addNum;//新空间人数
		//开辟新空间
		
		Worker** newSpace = new Worker * [newSize];
		
		//将原来空间下数据，拷贝到新空间
		if (this->m_EmpArray != NULL)
		{
			for (int i = 0; i < this->m_EmpNum; i++)
				newSpace[i] = this->m_EmpArray[i];
		}
		//添加新数据
		for (int i = 0; i < addNum; i++)
		{
			int id;
			string name;
			int dSelect;//部门
			cout << "输入第" << i + 1 << "个新职工编号：" << endl;
			cin >> id;
			cout << "输入第" << i + 1 << "个新职工姓名：" << endl;
			cin >> name;
			cout << "选择新职工岗位：" << endl;
			cout << "1.普通职工" << endl;
			cout << "2.经理" << endl;
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
			//将创建职工指针，保存在数组中
			//存在内存溢出问题
			newSpace[this->m_EmpNum + i] = worker;

		}
		//释放原有空间
		delete[] this->m_EmpArray;
		//更改新空间指向
		this->m_EmpArray = newSpace;
		//更新新职工人数
		this->m_EmpNum = newSize;

		//更新职工文件不为空的标志
		this->m_FileIsEmpty = false;
		
		//提示添加成功
		cout << "成功添加" << addNum << "名新职工！" << endl;
		//save
		this->save();
	}
	else
	{
		cout << "输入数据有误" << endl;
	}
	system("pause");
}

//保存文件
void WorkManger::save()
{
	ofstream ofs;
	ofs.open(FILENAME, ios::out);//以输出模式打开文件
	//数据写入文件
	for (int i = 0; i < this->m_EmpNum; i++)
	{
		ofs << this->m_EmpArray[i]->m_id << " "
			<< this->m_EmpArray[i]->m_name << " "
			<< this->m_EmpArray[i]->m_deptid << endl;
	}
	ofs.close();
}

//初始化员工
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
		if (dId == 1)//普通职工
		{
			worker = new Employee(id, name, dId);
		}
		else if(dId==2)//经理
			worker = new Manager(id, name, dId);
		else
			worker = new Boss(id, name, dId);
		this->m_EmpArray[index] = worker;
		index++;
	}
	ifs3.close();
}

//显示职工
void WorkManger::ShowEmp()
{
	//判断文件是否为空
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或记录为空！" << endl;
	}
	else
	{
		for (int i = 0; i < m_EmpNum; i++)
		{
			//利用多态接口
			this->m_EmpArray[i]->showInfo();
		}
	}
	system("pause");
	system("cls");
}