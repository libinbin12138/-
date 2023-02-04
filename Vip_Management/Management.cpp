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

