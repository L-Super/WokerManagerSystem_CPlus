#include "WorkerManager.h"
#include "worker.h"
#include "employee.h"
#include "boss.h"
#include "manager.h"
void WorkManager::Show_Menu()
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
void WorkManager::exitsystem()
{
	cout << "系统已退出，欢迎下次使用！" << endl;
	//system("pause");
	exit(0);
}
WorkManager::~WorkManager()
{
	if (this->m_EmpArray != NULL)
	{
		delete[] this->m_EmpArray;
		this->m_EmpArray = NULL;
	}
}


WorkManager::WorkManager()
{
	//1、文件不存在
	ifstream ifs;
	ifs.open(FILENAME, ios::in);//读文件,#define FILENAME "File.txt"
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
int WorkManager::get_EmpNum()
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


//添加职工
void WorkManager::Add_Emp()
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
void WorkManager::save()
{
	ofstream ofs;
	ofs.open(FILENAME, ios::out);//以输出模式打开文件
	//数据写入文件
	for (int i = 0; i < this->m_EmpNum; i++)
	{
		ofs << this->m_EmpArray[i]->m_id << "  "
			<< this->m_EmpArray[i]->m_name << "  "
			<< this->m_EmpArray[i]->m_deptid << endl;
	}
	ofs.close();
}

//初始化员工
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
void WorkManager::ShowEmp()
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

//删除职工
void WorkManager::Del_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或记录为空！" << endl;
	}
	else
	{
		//按照编号删除
		cout << "输入想要删除的职工编号" << endl;
		int id = 0;
		cin >> id;
		int index = this->IsExist(id);
		if (index != -1)//说明存在
		{
			/*//客户若想删除最后一个对象 则调用这个if语句
			if (index == this->m_EmpNum - 1)
			{
				delete this->m_EmpArray[index];
				this->m_EmpArray[index] = NULL;
			}
			else {*/
				//数据前移
				for (int i = index; i < this->m_EmpNum - 1; i++)
				{
					//若删除最后一个员工，m_EmpArray[i+1]会出现溢出问题
					this->m_EmpArray[i] = this->m_EmpArray[i + 1];
				}
			//}
			
			this->m_EmpNum--;//更新数组中记录的人数
			//数据同步到文件中
			this->save();

			cout << "删除成功" << endl;
		}
		else
		{
			cout << "删除失败，未找到" << endl;
		}
	}
	
}
//判断职工是否存在 如果存在返回职工所在数组中的位置，不存在返回-1
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
//修改职工
void WorkManager::Mod_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或记录为空！" << endl;
	}
	else
	{
		//按照编号删除
		cout << "输入想要修改的职工编号" << endl;
		int id = 0;
		cin >> id;
		int ret = this->IsExist(id);
		if (ret != -1)
		{
			//查找该编号职工
			//delete this->m_EmpArray[ret];
			int newId = 0;
			string newName = " ";
			int if_mod_name = 0;
			int dSelcet = 0;
			cout << "查到： " << id << "号职工，输入新职工号： " << endl;
			cin >> newId;
			cout << "是否修改姓名：1.是 2.否" << endl;
			cin >> if_mod_name;
			if ( if_mod_name == 1)
			{
				cout << "输入新姓名： " << endl;
				cin >> newName;
			}
			else
				newName = this->m_EmpArray[ret]->m_name;
			cout << "输入岗位：\n1、职工\n2、经理\n3、老板" << endl;
			cin >> dSelcet;
			Worker* worker = NULL;
			switch (dSelcet)
			{
			case 1:
				//const string name=Employee::Employee-> m_name;
				//没法不修改姓名，后期可尝试
				//2021.01.24 解决不修改名字问题
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
			//更新数据到数组中
			this->m_EmpArray[ret] = worker;
			cout << "修改成功！" << endl;
			//保存到文件中
			this->save();

		}
		else
			cout << "修改失败，查无此人！" << endl;
	}
}

//查找职工
void WorkManager::Find_Emp()
{
	if (this->m_FileIsEmpty)
		cout << "文件不存在或为空!" << endl;
	else
	{
		cout << "请输入查找的方式:" << endl;
		cout << "1、按职工编号查找" << endl;
		cout << "2、按职工姓名查找" << endl;
		int select = 0;
		cin >> select;
		if (select == 1)
		{
			//按照编号查
			int id;
			cout << "输入查找的职工编号：" << endl;
			cin >> id;
			int ret = IsExist(id);
			if (ret != -1)
			{
				//找到职工
				cout << "查找成功！该职工信息如下" << endl;
				this->m_EmpArray[ret]->showInfo();
			}
			else
				cout << "查找失败，查无此人" << endl;
		}
		else if (select == 2)
		{
			//按照姓名查
			string name;
			
			cout << "请输入查找的姓名：" << endl;
			cin >> name;
			//加入判断是否查到的标志
			bool flag = false;
			for (int i = 0; i < m_EmpNum; i++)
			{
				if (this->m_EmpArray[i]->m_name == name)
				{
					cout << "查找成功，职工编号为：" << this->m_EmpArray[i]->m_id << "号职工信息如下：" << endl;
					flag = true;
					this->m_EmpArray[i]->showInfo();

				}
			}
			if (flag == false)
				cout << "查找失败，查无此人！" << endl;
		}
		else
			cout << "输入选项有误！" << endl;
	}
	system("pause");
	//system("cls");
}

//排序职工
void WorkManager::Sort_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或记录为空！" << endl;
	}
	else
	{
		cout << "选择排序方式：" << endl;
		cout << "1.按职工号进行升序" << endl;
		cout << "2.按职工号进行降序" << endl;
		int select = 0;
		cin >> select;
		for (int i = 0; i < m_EmpNum; i++)
		{
			int minormax = i;//声明最大值或最小值
			for(int j=i+1;j<this->m_EmpNum;j++)
			//升序
				if (select == 1)
				{
					if (this->m_EmpArray[minormax]->m_id > this->m_EmpArray[j]->m_id)
						minormax = j;
				}
			//降序
				else
				{
					if (this->m_EmpArray[minormax]->m_id < this->m_EmpArray[j]->m_id)
						minormax = j;
				}
			//判断一开始认定的minormax是不是计算的最大值或最小值，如果不是交换数据
			if (i != minormax)
			{
				Worker* temp = this->m_EmpArray[i];
				this->m_EmpArray[i] = this->m_EmpArray[minormax];
				this->m_EmpArray[minormax] = temp;
			}

		}
		cout << "排序成功！结果为：" << endl;
		this->save();
		this->ShowEmp();
	}
}

//清空文档
void WorkManager::Clean_File()
{
	cout << "确定清空？" << endl;
	cout << "1.确定" << endl;
	cout << "2.取消" << endl;
	int select = 0;
	cin >> select;
	if (select == 1)
	{
		//清空
		ofstream ofs(FILENAME, ios::trunc);//删除文件后重新创建
		ofs.close();
		if (this->m_EmpArray != NULL)
		{
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				if (this->m_EmpArray[i] != NULL)
					delete this->m_EmpArray[i];
				
			}
			this->m_EmpNum = 0;
			delete[] this->m_EmpArray;
			this->m_EmpArray = NULL;
			this->m_FileIsEmpty = true;
		}
		cout << "清空成功！" << endl;
	}
	system("pause");
}