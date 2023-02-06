#define _CRT_SECURE_NO_WARNINGS
#include "Management.h"
#include<iostream>
#include<fstream>


#include<list>
#include<vector>
using namespace std;

#include"Vip.h"
#include"Vip_Discount.h"
#include"Vip_Number.h"
#include"Vip_Count.h"

Management::Management() :Vip_num (0)
{
	InitMember();
}

Management::~Management()
{
}

int Management::InitMember()
{
	ifstream ifs;
	ifs.open("./Member.txt", ios::in);
	if (!ifs.is_open())
	{
		cout << "当前会员录入文件不存在,请确认！！！" << endl;
		system("pause");
		return 0;
	}
	char buf[1024];

	memset(buf, 0, sizeof(buf));
	while (ifs.getline(buf,sizeof(buf)))
	{
		Vip_num++;
	}
	ifs.close();

	//记录当天时间
	//SYSTEMTIME Vip_Time; //windows.h中  
	GetLocalTime(&Vip_Time);//time.h的tm结构体一样的效果 

	return Vip_num;
}

void Management::ClaerList()
{
	L_saved.clear();
	L_NTemp.clear();
	L_DTemp.clear();
}

void Management::ShowMenu()
{
	cout << "****************************************" << endl;
	cout << "***0.退出当前管理系统*******************" << endl;
	cout << "***1.新增会员***************************" << endl;
	cout << "***2.显示当前已录入会员信息*************" << endl;
	cout << "***3.删除相关会员信息*******************" << endl;
	cout << "***4.会员消费***************************" << endl;
	cout << "***5.查找会员信息***********************" << endl;
	cout << "***6.修改会员信息***********************" << endl;
	cout << "***7.显示当前所有消费记录***************" << endl;
	cout << "***8.查找某会员的消费记录***************" << endl;
	cout << "***9.查找整年的消费记录*****************" << endl;
	cout << "***10.查找某年某月的消费记录*****************" << endl;
	cout << "***11.查找某年某月某日的消费记录*****************" << endl;
	cout << "****************************************" << endl;
	cout << "当前会员人数为: "<<this->Vip_num << endl;
}

void Management::ExitSys()
{
	exit(0);
}

void Management::AddMember()
{
	string choice;
	cout << "请为该新增会员选择" << endl;
	cout << "1.按折扣消费" << endl;
	cout << "2.按次数消费" << endl;

	cin >> choice;
	Vip* Vip_Member;
	switch (atoi(choice.c_str()))
	{
	case 1:
		Vip_Member = new Vip_Discount;
		dynamic_cast<Vip_Discount*>(Vip_Member)->v_flag = 1;

		cout << "请输入新增会员的姓名" << endl;
		cin >> choice;
		dynamic_cast<Vip_Discount*>(Vip_Member)->v_name= choice;	

		cout << "请输入新增会员的手机号码" << endl;
		cin >> choice;
		dynamic_cast<Vip_Discount*>(Vip_Member)->v_phone = choice;

		cout << "请输入新增会员的充值金额" << endl;
		cin >> choice;
		dynamic_cast<Vip_Discount*>(Vip_Member)->v_money = choice;

		cout << "请输入新增会员的折扣" << endl;
		cin >> choice;
		dynamic_cast<Vip_Discount*>(Vip_Member)->discount= atoi(choice.c_str());

		SaveMember(1,Vip_Member);
		break;

	case 2:
		Vip_Member = new Vip_Number;
		dynamic_cast<Vip_Number*>(Vip_Member)->v_flag = 2;

		cout << "请输入新增会员的姓名" << endl;
		cin >> choice;
		dynamic_cast<Vip_Number*>(Vip_Member)->v_name = choice;

		cout << "请输入新增会员的手机号码" << endl;
		cin >> choice;
		dynamic_cast<Vip_Number*>(Vip_Member)->v_phone = choice;

		cout << "请输入新增会员的充值金额" << endl;
		cin >> choice;
		dynamic_cast<Vip_Number*>(Vip_Member)->v_money = choice;

		cout << "请输入新增会员的剩余理发次数" << endl;
		cin >> choice;
		dynamic_cast<Vip_Number*>(Vip_Member)->v_num = atoi(choice.c_str());

		SaveMember(2, Vip_Member);
		break;
	default:
		system("cls");
		cout << "输入有误，已返回" << endl;
		return;
	}

	
	
}

int Management::SaveMember(int choice_flag, Vip* vip)
{
	ReadMemberInfo();
	switch (choice_flag)
	{
	case 1:
		L_DTemp.push_back(dynamic_cast<Vip_Discount*>(vip));
		break;
	case 2:
		L_NTemp.push_back(dynamic_cast<Vip_Number*>(vip));
		break;
	}
	//L_saved.push_back(vip);
	SaveMember();
	this->Vip_num++;
	
	cout << "新增会员已保存成功，按任意键返回" << endl;
	system("pause");
	system("cls");
	return 0;
}

int Management::SaveMember()
{
	ofstream ofs;
	ofs.open("./Member.txt", ios::out);
	if (!ofs.is_open())
	{
		cout << "文件打开或创建失败,请联系管理员检查" << endl;
		return -1;
	}

	for (auto single : L_DTemp)
	{
		ofs << single->v_flag << " "
			<< single->v_name << " "
			<< single->v_phone << " "
			<< single->v_money << " "
			<< single->discount << " "
			<< endl;
		ofs.flush();
	}
	for (auto single : L_NTemp)
	{
		ofs << single->v_flag << " "
			<< single->v_name << " "
			<< single->v_phone << " "
			<< single->v_money << " "
			<< single->v_num << " "
			<< endl;
		ofs.flush();
	}
	ofs.close();
	ClaerList();
	return 0;
}

void Management::ShowMember()
{
	ReadMemberInfo();	

	cout << "目前所有会员信息如下所示：" << endl;
	cout << "会员卡类别" << "\t"
	 << "会员的姓名" << "\t"
		<< "会员电话号码" << "\t"
		<< "会员剩余金额" << "\t"
		<< "会员享受的折扣" << "\t" << endl;
	for (auto single : L_DTemp)
	{
		cout << "按折扣消费" << "\t"
			<<" " << single->v_name << "\t"
			<< "        " << single->v_phone << "\t"
			<< "    " << single->v_money << "\t"
			<< "            " << single->discount << "\t"
			 << endl;
	}
	cout << endl; cout << endl;
	cout << "----------------------------------------------------------------------------------------------------------" << endl;
	cout << "----------------------------------------------------------------------------------------------------------" << endl;
	cout << endl; cout << endl;

	cout << "会员卡类别" << "\t"
			<< "会员的姓名"  << "\t"
			<< "会员电话号码" << "\t"
			<< "会员剩余金额" << "\t"
			<< "会员剩余次数"  << "\t" << endl;
		for (auto single : L_NTemp)
		{
			cout<<"按次数扣费" << "\t"
				<< "  " << single->v_name << "\t"
				<< "        " << single->v_phone << "\t"
				<< "    " << single->v_money << "\t"
				<< "            " << single->v_num << "\t"
				<< endl;
		}
	
		ClaerList();
	cout << "----------------------------------------------------------------------------------------------------------" << endl;
	cout << "----------------------------------------------------------------------------------------------------------" << endl;
	cout << endl; cout << endl;
	cout << "目前所有会员信息已打印完毕" << endl;
	system("pause");
	system("cls");
}

void Management::ReadMemberInfo()
{
	ifstream ifs;
	ifs.open("./Member.txt", ios::in);
	if (!ifs.is_open())
	{
		cout << "当前会员录入文件不存在,请确认！！！" << endl;
		system("pause");
	}

	char infor_buf[1024];
	memset(infor_buf, 0, sizeof(infor_buf));


	while (ifs.getline(infor_buf, sizeof(infor_buf)))
	{
		if (strlen(infor_buf) == 0)
			break;
		int flag = 888;
		char name[128];
		memset(name, 0, sizeof(name));
		char phone[128];
		memset(phone, 0, sizeof(phone));
		char money[128];
		memset(money, 0, sizeof(money));
		int discount = 888;
		/*char temp[1024];
		memset(temp, 0, sizeof(temp));*/
		sscanf(infor_buf, "%d %s %s %s %d", &flag, name, phone, money, &discount);

		Vip* vip_saved = NULL;

		switch (flag)
		{
		case 1:
			vip_saved = new Vip_Discount;

			dynamic_cast<Vip_Discount*>(vip_saved)->v_flag = flag;
			//cout << "已从所到文件将v_flag赋值为：" << flag << endl;
			dynamic_cast<Vip_Discount*>(vip_saved)->v_name = name;
			//cout << "已从所到文件将v_name赋值为：" << name << endl;
			dynamic_cast<Vip_Discount*>(vip_saved)->v_phone = phone;
			//cout << "已从所到文件将v_phone赋值为：" << phone << endl;
			dynamic_cast<Vip_Discount*>(vip_saved)->v_money = money;
			//cout << "已从所到文件将v_money赋值为：" << money << endl;
			dynamic_cast<Vip_Discount*>(vip_saved)->discount = discount;
			//cout << "已从所到文件将discount赋值为：" << discount << endl;
			L_DTemp.push_back(dynamic_cast<Vip_Discount*>(vip_saved));
			break;
		case 2:
			vip_saved = new Vip_Number;

			dynamic_cast<Vip_Number*>(vip_saved)->v_flag = flag;
			//cout << "已从所到文件将v_flag赋值为：" << flag << endl;
			dynamic_cast<Vip_Number*>(vip_saved)->v_name = name;
			//cout << "已从所到文件将v_name赋值为：" << name << endl;
			dynamic_cast<Vip_Number*>(vip_saved)->v_phone = phone;
			//cout << "已从所到文件将v_phone赋值为：" << phone << endl;
			dynamic_cast<Vip_Number*>(vip_saved)->v_money = money;
			//cout << "已从所到文件将v_money赋值为：" << money << endl;
			dynamic_cast<Vip_Number*>(vip_saved)->v_num = discount;
			//cout << "已从所到文件将discount赋值为：" << discount << endl;
			L_NTemp.push_back(dynamic_cast<Vip_Number*>(vip_saved));
			break;
		}

		L_saved.push_back(vip_saved);

	}
	ifs.close();
}

int Management::FindMember()
{
	string choice;
	int Found_Member = 0;
	cout << "请选择你要查找的方式" << endl;
	cout << "1.按姓名查找" << endl;
	cout << "2.按手机号查找" << endl;
	cin >> choice;
	ReadMemberInfo();

	switch (atoi(choice.c_str()))
	{
	case 1:
		cout << "请输入所要查找的会员的姓名"<<endl;
		cin >> choice;
		Found_Member=FindMember_Name(choice);
		ClaerList();
		system("pause");
		system("cls");
		break;
	case 2:
		cout << "请输入所要查找的会员的手机号" << endl;
		cin >> choice;
		Found_Member = FindMember_Phone(choice);
		ClaerList();
		system("pause");
		system("cls");
		break;
	default:
		cout << "输入有误,已返回" << endl;
		ClaerList();
		system("cls");
		break;
	}
	return Found_Member;
}

int Management::FindMember_Name(string Fname)
{
	int Found_Member = 0;
	
	for (auto single : L_DTemp)
	{
		if (single->v_name == Fname)
		{
			cout << "查到该会员，他的相关信息如下：" << endl;
				cout<< "会员类型： "<<"按折扣扣费\t"
				<<"姓名: " <<single->v_name<<"\t"
				<<"手机号: " <<single->v_phone << "\t"
				<<"余额: " <<single->v_money << "\t"
				<<"折扣: " <<single->discount << "\t"
				<< endl;
				Found_Member=1;
		}
	}
	for (auto single : L_NTemp)
	{
		if (single->v_name == Fname)
		{
			cout << "查到该会员，他的相关信息如下：" << endl;
			cout << "会员类型 " << "按次数扣费\t"
				<< "姓名: " << single->v_name << "\t"
				<< "手机号: " << single->v_phone << "\t"
				<< "余额: " << single->v_money << "\t"
				<< "剩余次数: " << single->v_num << "\t"
				<< endl;
			Found_Member=2;
		}
	}
	if (Found_Member == 0)
	{
		cout << "查无此人" << endl;
	}
	return Found_Member;
}

int Management::FindMember_Phone(std::string Phone)
{
	int Found_Member = 0;

	for (auto single : L_DTemp)
	{
		if (single->v_phone == Phone||(single->v_phone).find(Phone)<= (single->v_phone).size())
		{
			cout << "查到该会员，他的相关信息如下：" << endl;
			cout << "会员类型： " << "按折扣扣费\t"
				<< "姓名: " << single->v_name << "\t"
				<< "手机号: " << single->v_phone << "\t"
				<< "余额: " << single->v_money << "\t"
				<< "折扣: " << single->discount << "\t"
				<< endl;
			Found_Member=1;
		}
	}
	for (auto single : L_NTemp)
	{
		if (single->v_phone == Phone || (single->v_phone).find(Phone) <= (single->v_phone).size())
		{
			cout << "查到该会员，他的相关信息如下：" << endl;
			cout << "会员类型 " << "按次数扣费\t"
				<< "姓名: " << single->v_name << "\t"
				<< "手机号: " << single->v_phone << "\t"
				<< "余额: " << single->v_money << "\t"
				<< "剩余次数: " << single->v_num << "\t"
				<< endl;
			Found_Member=2;
		}
	}
	if (Found_Member == 0)
	{
		cout << "查无此人" << endl;
	}
	return Found_Member;
}

int Management::DelteMember()
{
	cout << "请选择按照以下哪一种方式删除：" << endl;
	cout << "1.会员姓名" << endl;
	cout << "2.会员手机号" << endl;
	string choice;
	cin >> choice;

	ReadMemberInfo();
	int flag = 0;

	switch (atoi(choice.c_str()))
	{
	case 1:
		DeleteMember_Name(choice,flag);
		break;
	case 2:
		DeleteMember_Phone(choice, flag);
		break;
	default:
		cout << "输入有误，已返回" << endl;
		ClaerList();
		system("pause");
		system("cls");
		break;
	}
	return 0;
}

int Management::DeleteMember_Name(string choice, int flag)
{
	cout << "请输入要删除会员的姓名：" << endl;
	cin >> choice;
	flag = FindMember_Name(choice);
	switch (flag)
	{
	case 1:
		for (auto single : L_DTemp)
		{
			if (single->v_name == choice)
			{
				cout << "请确认是否删除" << endl;
				cout << "是请输入y（不区分大小写）" << endl;
				cout << "否则输入其他任意键，回车键返回" << endl;
				cin >> choice;
				
				if (choice[choice.size()-1] == 'y' || choice[choice.size() - 1] == 'Y')
				{
					L_DTemp.remove(single);
					SaveMember();
					this->Vip_num--;
					cout << "删除成功" << endl;
					system("pause");
					system("cls");
					break;
				}
				else
				{
					ClaerList();
					system("pause");
					system("cls");
					break;
				}
			}
			
		}
		break;
	case 2:
		for (auto single : L_NTemp)
		{
			if (single->v_name == choice)
			{
				cout << "请确认是否删除" << endl;
				cout << "是请输入y（不区分大小写）" << endl;
				cout << "否则输入其他任意键，回车键返回" << endl;
				cin >> choice;

				if (choice[choice.size() - 1] == 'y' || choice[choice.size() - 1] == 'Y')
				{
					L_NTemp.remove(single);
					SaveMember();
					this->Vip_num--;
					cout << "删除成功" << endl;
					system("pause");
					system("cls");
					break;
				}
				else
				{
					ClaerList();
					system("pause");
					system("cls");
					break;
				}
			}
			else
			{
				if (single == L_NTemp.back())
				{
					ClaerList();
					system("pause");
					system("cls");
					break;
				}
			}
		}
		break;
	case 0:
		system("pause");
		system("cls");
		return -1;
		break;
	}
	return 0;
}

int Management::DeleteMember_Phone(string choice, int flag)
{
	
	cout << "请输入要删除会员的手机号码：" << endl;
	cout << "目前功能尚不完善，建议输入全部手机号码：" << endl;
	cin >> choice;
	flag = FindMember_Phone(choice);
	switch (flag)
	{
	case 1:
		for (auto single : L_DTemp)
		{
			if (single->v_phone == choice)
			{
				cout << "请确认是否删除" << endl;
				cout << "是请输入y（不区分大小写）" << endl;
				cout << "否则输入其他任意键，回车键返回" << endl;
				cin >> choice;

				if (choice[choice.size() - 1] == 'y' || choice[choice.size() - 1] == 'Y')
				{
					L_DTemp.remove(single);
					SaveMember();
					this->Vip_num--;
					cout << "删除成功" << endl;
					system("pause");
					system("cls");
					break;
				}
				else
				{
					ClaerList();
					system("pause");
					system("cls");
					break;
				}
			}
			else
			{
				if (single == L_DTemp.back())
				{
					ClaerList();
					system("pause");
					system("cls");
					break;
				}
			}
		}
		break;
	case 2:
		for (auto single : L_NTemp)
		{
			if (single->v_phone == choice)
			{
				cout << "请确认是否删除" << endl;
				cout << "是请输入y（不区分大小写）" << endl;
				cout << "否则输入其他任意键，回车键返回" << endl;
				cin >> choice;

				if (choice[choice.size() - 1] == 'y' || choice[choice.size() - 1] == 'Y')
				{
					L_NTemp.remove(single);
					SaveMember();
					this->Vip_num--;
					cout << "删除成功" << endl;
					system("pause");
					system("cls");
					break;
				}
				else
				{
					ClaerList();
					system("pause");
					system("cls");
					break;
				}
			}
			else
			{
				if (single == L_NTemp.back())
				{
					ClaerList();
					system("pause");
					system("cls");
					break;
				}
			}
		}
		break;

	case 0:
		system("pause");
		system("cls");
		break;
	}
	
	return 0;
}

void Management::Consume()
{
	string choice; int flag = 0,location=0;
	cout << "请选择按照会员的姓名或手机号码来扣费" << endl;
	cout<<"1.姓名" << endl;
	cout << "2.手机号码" << endl;
	cin >> choice;

	ReadMemberInfo();

	switch (atoi(choice.c_str()))
	{
	case 1:
		cout << "请输入会员的姓名" << endl;
		cin >> choice;
		flag = FindMember_Name(choice);
		switch (flag)
		{
		case 1:			
			Consume_DName(choice);
			break;
		case 2:
			Consume_NUM_Name(choice);
			break;
		case 0:
			ClaerList();
			system("pause");
			system("cls");
			break;
		}
		break;

	case 2:
		cout << "请输入会员的电话号码" << endl;
		cout << "(请注意当前功能不完善，如果搜索结果显示多个会员不要确认删除)" << endl;
		cin >> choice;
		flag = FindMember_Phone(choice);
		switch (flag)
		{
		case 1:
			Consume_DPhone(choice);
			break;
		case 2:
			Consume_NUM_Phone(choice);
			break;
		case 0:
			ClaerList();
			system("pause");
			system("cls");
			break;
		}
		break;
	default:
		cout << "输入有误" << endl;
		ClaerList();
		system("pause");
		system("cls");
		break;
	}
}

void Management::Consume_DName(string choice)
{
	for (auto single : L_DTemp)
	{
		if (single->v_name == choice)
		{
			Vip_Discount* vip_temp = new Vip_Discount;
			vip_temp = single;

			cout << "请输入该会员本次的消费金额" << endl;
			float num = 0; float remain_money = 0, consume_money = 0;
			cin >> num;
			remain_money = atoi(vip_temp->v_money.c_str());
			consume_money = num * (vip_temp->discount / 10);
			remain_money = (remain_money - consume_money);
			vip_temp->v_money = to_string(remain_money);

			cout << "该会员本次打折后消费\t"<< consume_money <<"\t" << endl;
			cout << "请确认结果(当前功能尚不完善，如果结果显示多个会员，请不要进行确认)" << endl;
			cout << "是请输入y（不区分大小写）" << endl;
			cout << "否则输入其他任意键，回车键返回" << endl;
			cin >> choice;
			if (choice[choice.size() - 1] == 'y' || choice[choice.size() - 1] == 'Y')
			{
				L_DTemp.remove(single);
				L_DTemp.push_back(vip_temp);

				this->SaveMember();
				cout << "消费完成,现更新该会员信息为" << endl;

				ReadMemberInfo();
				FindMember_Name(vip_temp->v_name);
				ClaerList();

				AddMember_Consume(1, vip_temp, consume_money);

				system("pause");
				system("cls");
			}
			else
			{
				ClaerList();
				system("cls");
			}
			break;
		}
	}
}

void Management::Consume_NUM_Name(std::string choice)
{
	for (auto single : L_NTemp)
	{
		if (single->v_name == choice)
		{
			Vip_Number* vip_temp = new Vip_Number;
			vip_temp = single;

			cout << "会员"<<single->v_name<<"进行消费" << endl;
			cout << "请确认是否扣除当前会员一次次数" << endl;
			cout << "是请输入y（不区分大小写）" << endl;
			cout << "否则输入其他任意键，回车键返回" << endl;
			cin >> choice;
			if (choice[choice.size() - 1] == 'y' || choice[choice.size() - 1] == 'Y')
			{
				vip_temp->v_num--;
				L_NTemp.remove(single);
				L_NTemp.push_back(vip_temp);

				this->SaveMember();
				cout << "消费完成,现更新该会员信息为" << endl;

				ReadMemberInfo();
				FindMember_Name(vip_temp->v_name);

				AddMember_Consume(2, vip_temp,0);

				ClaerList();
				system("pause");
				system("cls");
			}
			else
			{
				ClaerList();
				system("cls");
			}
			break;
		}
	}
}

void Management::Consume_DPhone(std::string choice)
{
	for (auto single : L_DTemp)
	{
		if (single->v_phone == choice || (single->v_phone).find(choice) <= (single->v_phone).size())
		{
			Vip_Discount* vip_temp = new Vip_Discount;
			vip_temp = single;

			cout << "请输入该会员本次的消费金额" << endl;
			float num = 0; float remain_money = 0, consume_money = 0;
			cin >> num;
			remain_money = atoi(vip_temp->v_money.c_str());
			consume_money = num * (vip_temp->discount / 10);
			remain_money = (remain_money - consume_money);
			vip_temp->v_money = to_string(remain_money);

			cout << "该会员本次打折后消费\t" << consume_money << "\t" << endl;
			cout << "请确认结果(当前功能尚不完善，如果结果显示多个会员，请不要进行确认)" << endl;
			cout << "是请输入y（不区分大小写）" << endl;
			cout << "否则输入其他任意键，回车键返回" << endl;
			cin >> choice;

			if (choice[choice.size() - 1] == 'y' || choice[choice.size() - 1] == 'Y')
			{
				L_DTemp.remove(single);
				L_DTemp.push_back(vip_temp);

				this->SaveMember();
				cout << "消费完成,现更新该会员信息为" << endl;

				ReadMemberInfo();
				FindMember_Name(vip_temp->v_name);
				ClaerList();

				AddMember_Consume(1, vip_temp, consume_money);
				system("pause");
				system("cls");
			}
			else
			{
				ClaerList();
				system("cls");
			}
			break;
		}
	}
}

void Management::Consume_NUM_Phone(std::string choice)
{
	for (auto single : L_NTemp)
	{
		if (single->v_phone == choice || (single->v_phone).find(choice) <= (single->v_phone).size())
		{
			Vip_Number* vip_temp = new Vip_Number;
			vip_temp = single;

			cout << "会员" << single->v_name << "进行消费" << endl;
			
			cout << "请确认结果(当前功能尚不完善，如果结果显示多个会员，请不要进行确认)" << endl;
			cout << "是请输入y（不区分大小写）" << endl;
			cout << "否则输入其他任意键，回车键返回" << endl;
			cin >> choice;

			if (choice[choice.size() - 1] == 'y' || choice[choice.size() - 1] == 'Y')
			{
				vip_temp->v_num--;
				L_NTemp.remove(single);
				L_NTemp.push_back(vip_temp);

				this->SaveMember();
				cout << "消费完成,现更新该会员信息为" << endl;

				ReadMemberInfo();
				FindMember_Name(vip_temp->v_name);
				ClaerList();

				AddMember_Consume(2, vip_temp, 0);
				system("pause");
				system("cls");
			}
			else
			{
				ClaerList();
				system("cls");
			}
			break;
		}
	}
}

void Management::ModifyMember()
{
	string choice;
	cout << "请输入你要修改的方式" << endl;
	cout << "1.按姓名" << endl;
	cout << "2.按手机号" << endl;
	cin >> choice;
	switch (atoi(choice.c_str()))
	{
	case 1:
		ModifyMember_Name();
		break;
	case 2:
		ModifyMember_Phone();
		break;
	default:
		cout << "输入有误" << endl;
		system("pause");
		system("cls");
		break;
	}

}

void Management::ModifyMember_Name()
{
	string choice;
	int flag=-1;
	cout << "请输入要修改会员的姓名" << endl;
	cin >> choice;
	ReadMemberInfo();
	flag = FindMember_Name(choice);
	switch (flag)
	{
	case 1:
		ModifyMember_DName(choice);
		break;
	case 2:
		ModifyMember_NUM_Name(choice);
		break;
	case 0:
		ClaerList();
		system("pause");
		system("cls");
		break;
	}
}

void Management::ModifyMember_DName(std::string choice)
{
	for (auto single : L_DTemp)
	{
		if (single->v_name == choice)
		{

			Vip_Discount* viptemp = new Vip_Discount;
			viptemp = single;

			cout << "请输入要修改会员的姓名" << endl;
			cout << "无需修改则输入n跳过" << endl;
			cin >> choice;
			if (choice[choice.size()-1] != 'n' && choice[choice.size()  -1] != 'N')
			{
				viptemp->v_name = choice;
			}

			cout << "请输入要修改会员的手机号" << endl;
			cout << "无需修改则输入n跳过" << endl;
			cin >> choice;
			if (choice[choice.size()  -1] != 'n' && choice[choice.size()  -1] != 'N')
			{
				viptemp->v_phone = choice;
			}

			cout << "请输入会员新充值金额" << endl;
			cout << "无新充值则输入n跳过" << endl;
			cin >> choice;
			if (choice[choice.size()  -1] != 'n' && choice[choice.size()  -1] != 'N')
			{
				float RemianNum = 0, num = -1;
				RemianNum = atoi(viptemp->v_money.c_str());
				num = atoi(choice.c_str());
				RemianNum += num;
				viptemp->v_money = to_string(RemianNum);
			}

			cout << "请为该会员选择充值后的新折扣" << endl;
			cout << "无需修改则输入n跳过" << endl;
			cin >> choice;
			if (choice[choice.size() -1] != 'n' && choice[choice.size()  -1] != 'N')
			{
				viptemp->discount = atoi(choice.c_str());
			}

			L_DTemp.remove(single);
			L_DTemp.push_back(viptemp);
			SaveMember();
			cout << "修改成功，修改后该会员的信息如下： " << endl;

			ReadMemberInfo();
			FindMember_Name(viptemp->v_name);
			ClaerList();
			system("pause");
			system("cls");
			break;
		}
	}
}

void Management::ModifyMember_NUM_Name(std::string choice)
{
	for (auto single : L_NTemp)
	{
		if (single->v_name == choice)
		{
			Vip_Number* viptemp = new Vip_Number;
			viptemp = single;

			cout << "请输入要修改会员的姓名" << endl;
			cout << "无需修改则输入n跳过" << endl;
			cin >> choice;
			if (choice[choice.size()  -1] != 'n' && choice[choice.size() -1] != 'N')
			{
				viptemp->v_name = choice;
			}

			cout << "请输入要修改会员的手机号" << endl;
			cout << "无需修改则输入n跳过" << endl;
			cin >> choice;
			if (choice[choice.size() - 1] != 'n' && choice[choice.size() -1] != 'N')
			{
				viptemp->v_phone = choice;
			}

			cout << "请输入会员新充值金额" << endl;
			cout << "无需修改则输入n跳过" << endl;
			cin >> choice;
			if (choice[choice.size() - 1] != 'n' && choice[choice.size() -1] != 'N')
			{
				float RemianNum = 0, num = -1;
				RemianNum = atoi(viptemp->v_money.c_str());
				num = atoi(choice.c_str());
				RemianNum += num;
				viptemp->v_money = to_string(RemianNum);
			}

			cout << "请为该会员选择新增的次数" << endl;
			cout << "无需修改则输入n跳过" << endl;
			cin >> choice;
			if (choice[choice.size() - 1] != 'n' && choice[choice.size()-1] != 'N')
			{
				viptemp->v_num += atoi(choice.c_str());
			}

			L_NTemp.remove(single);
			L_NTemp.push_back(viptemp);
			SaveMember();
			cout << "修改成功，修改后该会员的信息如下： " << endl;

			ReadMemberInfo();
			FindMember_Name(viptemp->v_name);
			ClaerList();
			system("pause");
			system("cls");
			break;
		}
	}
}

void Management::ModifyMember_Phone()
{
	string choice;
	int flag = -1;
	cout << "请输入要修改会员的电话号码" << endl;
	cin >> choice;
	ReadMemberInfo();
	flag = FindMember_Phone(choice);
	switch (flag)
	{
	case 1:
		ModifyMember_DPhone(choice);
		break;
	case 2:
		ModifyMember_NUM_Phone(choice);
		break;
	case 0:
		ClaerList();
		system("pause");
		system("cls");
		break;
	}
}

void Management::ModifyMember_DPhone(std::string choice)
{
	for (auto single : L_DTemp)
	{
		if (single->v_phone == choice|| (single->v_phone.find(choice))< ((single->v_phone).size()))
		{

			Vip_Discount* viptemp = new Vip_Discount;
			viptemp = single;

			cout << "请输入要修改会员的姓名" << endl;
			cout << "无需修改则输入n跳过" << endl;
			cin >> choice;
			if (choice[choice.size() - 1] != 'n' && choice[choice.size() - 1] != 'N')
			{
				viptemp->v_name = choice;
			}

			cout << "请输入要修改会员的手机号" << endl;
			cout << "无需修改则输入n跳过" << endl;
			cin >> choice;
			if (choice[choice.size() - 1] != 'n' && choice[choice.size() - 1] != 'N')
			{
				viptemp->v_phone = choice;
			}

			cout << "请输入会员新充值金额" << endl;
			cout << "无新充值则输入n跳过" << endl;
			cin >> choice;
			if (choice[choice.size() - 1] != 'n' && choice[choice.size() - 1] != 'N')
			{
				float RemianNum = 0, num = -1;
				RemianNum = atoi(viptemp->v_money.c_str());
				num = atoi(choice.c_str());
				RemianNum += num;
				viptemp->v_money = to_string(RemianNum);
			}

			cout << "请为该会员选择充值后的新折扣" << endl;
			cout << "无需修改则输入n跳过" << endl;
			cin >> choice;
			if (choice[choice.size() - 1] != 'n' && choice[choice.size() - 1] != 'N')
			{
				viptemp->discount = atoi(choice.c_str());
			}

			L_DTemp.remove(single);
			L_DTemp.push_back(viptemp);
			SaveMember();
			cout << "修改成功，修改后该会员的信息如下： " << endl;

			ReadMemberInfo();
			FindMember_Name(viptemp->v_name);
			ClaerList();
			system("pause");
			system("cls");
			break;
		}
	}
}

void Management::ModifyMember_NUM_Phone(std::string choice)
{
	for (auto single : L_NTemp)
	{
		if (single->v_phone == choice || (single->v_phone.find(choice)) < ((single->v_phone).size()))
		{
			Vip_Number* viptemp = new Vip_Number;
			viptemp = single;

			cout << "请输入要修改会员的姓名" << endl;
			cout << "无需修改则输入n跳过" << endl;
			cin >> choice;
			if (choice[choice.size() - 1] != 'n' && choice[choice.size() - 1] != 'N')
			{
				viptemp->v_name = choice;
			}

			cout << "请输入要修改会员的手机号" << endl;
			cout << "无需修改则输入n跳过" << endl;
			cin >> choice;
			if (choice[choice.size() - 1] != 'n' && choice[choice.size() - 1] != 'N')
			{
				viptemp->v_phone = choice;
			}

			cout << "请输入会员新充值金额" << endl;
			cout << "无需修改则输入n跳过" << endl;
			cin >> choice;
			if (choice[choice.size() - 1] != 'n' && choice[choice.size() - 1] != 'N')
			{
				float RemianNum = 0, num = -1;
				RemianNum = atoi(viptemp->v_money.c_str());
				num = atoi(choice.c_str());
				RemianNum += num;
				viptemp->v_money = to_string(RemianNum);
			}

			cout << "请为该会员选择新增的次数" << endl;
			cout << "无需修改则输入n跳过" << endl;
			cin >> choice;
			if (choice[choice.size() - 1] != 'n' && choice[choice.size() - 1] != 'N')
			{
				viptemp->v_num += atoi(choice.c_str());
			}

			L_NTemp.remove(single);
			L_NTemp.push_back(viptemp);
			SaveMember();
			cout << "修改成功，修改后该会员的信息如下： " << endl;

			ReadMemberInfo();
			FindMember_Name(viptemp->v_name);
			ClaerList();
			system("pause");
			system("cls");
			break;
		}
	}
}

void Management::ReadMember_Consume_Info()
{
	ifstream ifs;
	ifs.open("./Member_Consume.txt", ios::in);
	if (!ifs.is_open())
	{
		cout << "当前会员录入文件不存在,请确认！！！" << endl;
		system("pause");
	}

	char infor_buf[4096];
	memset(infor_buf, 0, sizeof(infor_buf));

	while (ifs.getline(infor_buf, sizeof(infor_buf)))
	{
		if (strlen(infor_buf) == 0)
			break;
		char name[1024];
		memset(name, 0, sizeof(name));
		char phone[128];
		memset(phone, 0, sizeof(phone));
		float money = -1;
		int num = -1, year=-1,month=-1,day=-1;
		
		sscanf(infor_buf, "%s %s %f %d %d %d %d", name,phone,&money, &num,&year,&month,&day);

		Vip_Count* vip_consume = new Vip_Count;
		
		vip_consume->v_name = name;
		vip_consume->v_phone = phone; 
		vip_consume->v_Remain_money = money;
		vip_consume->v_Sum_Num = num;
		vip_consume->ConsumTime.wYear = year;
		vip_consume->ConsumTime.wMonth = month;
		vip_consume->ConsumTime.wDay = day;
		
		L_Consume_Temp.push_back(vip_consume);

	}
	ifs.close();
}

void Management::ShowMember_Consume_Info()
{
	ReadMember_Consume_Info();
	if (L_Consume_Temp.size() == 0)
	{
		cout << "当前会员记录为空" << endl;
		system("pause");
		system("cls");
		return;
	}
	cout << "当前所有会员消费记录如下" << endl;
	cout << "姓名\t" << "手机号码\t" << "消费金额\t" << "消耗次数\t" << "时间\t" << endl;
	float Income=0.0;
	int num = 0;
	for (auto single : L_Consume_Temp)
	{
		Income += single->v_Remain_money;
		num += single->v_Sum_Num;
		cout << single->v_name << "\t" << single->v_phone<<"\t"
			<< single->v_Remain_money << "\t" << "\t" << single->v_Sum_Num << "\t" << "\t"
			<< single->ConsumTime.wYear << "."
			<< single->ConsumTime.wMonth << "."
			<< single->ConsumTime.wDay << "\t" << endl;
	}
	cout << endl; cout << endl; cout << endl;
	cout << "你当前的总收入 ：" << endl;
		cout << "按折扣消费 ：" << Income <<endl;
		cout << "按次数消费 ：" << num << endl;
	L_Consume_Temp.clear();

	system("pause");
	system("cls");
}

void Management::AddMember_Consume(int flag, Vip* p,float money)
{
	Vip_Discount* vip_Dtemp;
	Vip_Number* vip_Ntemp;
	Vip_Count* vip_count_temp;
	switch (flag)
	{
	case 1:
		vip_Dtemp = dynamic_cast<Vip_Discount*> (p);
		 vip_count_temp = new Vip_Count;
		vip_count_temp->v_name = vip_Dtemp->v_name;
		vip_count_temp->v_phone = vip_Dtemp->v_phone;
		vip_count_temp->v_Remain_money = money;
		vip_count_temp->ConsumTime.wYear = Vip_Time.wYear;
		vip_count_temp->ConsumTime.wMonth = Vip_Time.wMonth;
		vip_count_temp->ConsumTime.wDay = Vip_Time.wDay;
		SaveMember_Consume(vip_count_temp);
		if (vip_count_temp != NULL)
		{
			delete vip_count_temp;
			vip_count_temp = NULL;
		}
		if (vip_Dtemp != NULL)
		{
			delete vip_Dtemp;
			vip_Dtemp = NULL;
		}
		break;
	case 2:
		vip_Ntemp = dynamic_cast<Vip_Number*> (p);
		vip_count_temp = new Vip_Count;
		vip_count_temp->v_name = vip_Ntemp->v_name;
		vip_count_temp->v_phone = vip_Ntemp->v_phone;
		vip_count_temp->v_Sum_Num = 1;
		vip_count_temp->ConsumTime.wYear = Vip_Time.wYear;
		vip_count_temp->ConsumTime.wMonth = Vip_Time.wMonth;
		vip_count_temp->ConsumTime.wDay = Vip_Time.wDay;
		SaveMember_Consume(vip_count_temp);
		if (vip_count_temp != NULL)
		{
			delete vip_count_temp;
			vip_count_temp = NULL;
		}
		if (vip_Ntemp != NULL)
		{
			delete vip_Ntemp;
			vip_Ntemp = NULL;
		}
		break;
	}

	
	
}

void Management::SaveMember_Consume(Vip_Count* p)
{
	ofstream ofs;
	ofs.open("./Member_Consume.txt", ios::out | ios::app);
	if (!ofs.is_open())
	{
		cout << "文件打开或创建失败,请联系管理员检查" << endl;
		return ;
	}

		ofs << p->v_name << " "
			<<p->v_phone<<" "
			<<p->v_Remain_money<<" "
			<<p->v_Sum_Num<<" "
			<<p->ConsumTime.wYear<<" "
			<<p->ConsumTime.wMonth<<" "
			<<p->ConsumTime.wDay<<" "
			<< endl;
		ofs.flush();
	ofs.close();
	
}

void Management::Show_SpecificMember_Consume_Info()
{
	int num = 0;
	string choice;
	cout << "请输入要查找的会员的姓名或手机号码" << endl;
	cin >> choice;
	this->ReadMember_Consume_Info();

	for (auto single : L_Consume_Temp)
	{
		if (single->v_name == choice || single->v_phone == choice || single->v_phone.find(choice) < single->v_phone.size())
		{
			if (num == 0)
			{
				cout << "当前所有会员消费记录如下" << endl;
				cout << "姓名\t" << "手机号码\t" << "消费金额\t" << "消耗次数\t" << "时间\t" << endl;

			}
				cout << single->v_name << "\t" << single->v_phone << "\t"
					<< single->v_Remain_money << "\t" << "\t" << single->v_Sum_Num << "\t" << "\t"
					<< single->ConsumTime.wYear << "."
					<< single->ConsumTime.wMonth << "."
					<< single->ConsumTime.wDay << "\t" << endl;
				num++;
			
		}
		if (single ==L_Consume_Temp.back() && num == 0)
		{
			cout << "查无此人" << endl;
			break;
		}
	}
	L_Consume_Temp.clear();
	system("pause");
	system("cls");
}

void Management::Show_SpecificDate_Year_Consume_Info()
{
	string date;
	cout << "请输入要查找的年份" << endl;
	cin >> date;
	int Year_num = atoi(date.c_str()),num=0,income=0,use_num=0;
	this->ReadMember_Consume_Info();
	for (auto single : L_Consume_Temp)
	{
		if (single->ConsumTime.wYear== Year_num)
		{
			if (num == 0)
			{
				cout<<Year_num << "年所有会员消费记录如下" << endl;
				cout << "姓名\t" << "手机号码\t" << "消费金额\t" << "消耗次数\t" << "时间\t" << endl;

			}
			cout << single->v_name << "\t" << single->v_phone << "\t"
				<< single->v_Remain_money << "\t" << "\t" << single->v_Sum_Num << "\t" << "\t"
				<< single->ConsumTime.wYear << "."
				<< single->ConsumTime.wMonth << "."
				<< single->ConsumTime.wDay << "\t" << endl;
			num++;
			income += single->v_Remain_money;
			use_num += single->v_Sum_Num;
		}
		if (single == L_Consume_Temp.back() && num == 0)
		{
			cout << "该年份暂无记录" << endl;
			break;
		}
	}
	if (num!=0)
	{
		cout << endl; cout << endl;
		cout << Year_num << "年，按折扣消费共收入 ：" << income << endl;
		cout << Year_num << "年，按次数消费共收入 ：" << use_num << endl;
	}
	L_Consume_Temp.clear();
	system("pause");
	system("cls");
}

void Management::Show_SpecificDate_Year_Month_Consume_Info()
{
	string date;
	cout << "请输入要查找的年份" << endl;
	cin >> date;
	int Year_num = atoi(date.c_str()), num = 0,income = 0, use_num = 0;

	cout << "请输入要查找的月份" << endl;
	cin >> date;
	int Month_num = atoi(date.c_str());

	this->ReadMember_Consume_Info();
	for (auto single : L_Consume_Temp)
	{
		if (single->ConsumTime.wYear == Year_num&&single->ConsumTime.wMonth==Month_num)
		{
			if (num == 0)
			{
				cout << Year_num << "年"<<Month_num<<"月所有会员消费记录如下" << endl;
				cout << "姓名\t" << "手机号码\t" << "消费金额\t" << "消耗次数\t" << "时间\t" << endl;

			}
			cout << single->v_name << "\t" << single->v_phone << "\t"
				<< single->v_Remain_money << "\t" << "\t" << single->v_Sum_Num << "\t" << "\t"
				<< single->ConsumTime.wYear << "."
				<< single->ConsumTime.wMonth << "."
				<< single->ConsumTime.wDay << "\t" << endl;
			num++;
			income += single->v_Remain_money;
			use_num += single->v_Sum_Num;
		}
		if (single == L_Consume_Temp.back() && num == 0)
		{
			cout << "该年该月份暂无记录" << endl;
			break;
		}
	}

	L_Consume_Temp.clear();
	if (num != 0)
	{
		cout << endl; cout << endl;
		cout << Year_num << "年" << Month_num << "月，按折扣消费共收入 ：" << income << endl;
		cout << Year_num << "年" << Month_num << "月，按折扣消费共收入 ：" << use_num << endl;
	}
	system("pause");
	system("cls");
}

void Management::Show_SpecificDate_Year_Month_Day_Consume_Info()
{
	string date;
	cout << "请输入要查找的年份" << endl;
	cin >> date;
	int Year_num = atoi(date.c_str()), num = 0, income = 0, use_num = 0;

	cout << "请输入要查找的月份" << endl;
	cin >> date;
	int Month_num = atoi(date.c_str());

	cout << "请输入要查找日子" << endl;
	cin >> date;
	int Day_num = atoi(date.c_str());

	this->ReadMember_Consume_Info();
	for (auto single : L_Consume_Temp)
	{
		if (single->ConsumTime.wYear == Year_num && single->ConsumTime.wMonth == Month_num&&single->ConsumTime.wDay== Day_num)
		{
			if (num == 0)
			{
				cout << Year_num << "年" << Month_num << "月"<< Day_num <<"日所有会员消费记录如下" << endl;
				cout << "姓名\t" << "手机号码\t" << "消费金额\t" << "消耗次数\t" << "时间\t" << endl;

			}
			cout << single->v_name << "\t" << single->v_phone << "\t"
				<< single->v_Remain_money << "\t" << "\t" << single->v_Sum_Num << "\t" << "\t"
				<< single->ConsumTime.wYear << "."
				<< single->ConsumTime.wMonth << "."
				<< single->ConsumTime.wDay << "\t" << endl;
			num++;
			income += single->v_Remain_money;
			use_num += single->v_Sum_Num;

		}
		if (single == L_Consume_Temp.back() && num == 0)
		{
			cout << "该年该月该日份暂无记录" << endl;
			break;
		}
	}

	L_Consume_Temp.clear();

	if (num != 0)
	{
		cout << endl; cout << endl;
		cout << Year_num << "年" << Month_num << "月" << Day_num << "日，按折扣消费共收入 ：" << income << endl;
		cout << Year_num << "年" << Month_num << "月" << Day_num << " 日,按折扣消费共收入 ：" << use_num << endl;
	}
	
	system("pause");
	system("cls");
}

int Management::ReadLoginFile()
{
	int num = 0;
	ifstream ifs;
	ifs.open("login.txt", ios::in);
	if (!ifs.is_open())
	{
		cout << "读取登陆文件失败" << endl;
		return num;
	}
	char buf[1024];
	char username[128], password[128];
	while (!ifs.eof())
	{
		ifs >> username >> password;
		manager.SetUser(username, password);
		L_manager.push_back(manager);
		num++;
	}
	ifs.close();
	return num;
}

int Management::Login()
{
	cout << "欢迎登录尚雅美学理发管理系统" << endl;
	int num = ReadLoginFile();
	if (num == 0)
	{
		cout << "当前暂无管理者用户，请创建" << endl;
		CreateManeger();
	}

	ReadLoginFile();
	string choice1, choice2;
	cout << "请输入管理者用户名" << endl;
	cin >> choice1;

	cout << "请输入用户的密码" << endl;
	cin >> choice2;

	manager.SetUser(choice1, choice2);

	int flag = -1;
	for (auto single : L_manager)
	{
		if (single.Username == choice1 && single.PassWord == choice2)
		{
			flag = 1;
			cout << "登录成功"<<endl;
			system("pause");
			system("cls");
			break;
		}
		
	}
	return flag;
}

void Management::CreateManeger()
{
	string choice1, choice2;
	cout << "请输入新用户的用户名" << endl;
	cin >> choice1;

	cout << "请输入新用户的密码" << endl;
	cin >> choice2;
	manager.SetUser(choice1, choice2);
	L_manager.push_back(manager);

	ofstream ofs;

	ReadLoginFile();
	
	ofs.open("login.txt", ios::out | ios::_Noreplace);

	for (auto single : L_manager)
	{
		ofs << single.Username <<" " << single.PassWord << endl;
	}
	ofs.close();
	cout << "创建成功" << endl;
	system("pause");
	system("cls");
	L_manager.clear();
}

Manager::Manager()
{
}

Manager::~Manager()
{
}

void Manager::SetUser(string name, string password)
{
	Username = name;
	PassWord = password;
}

