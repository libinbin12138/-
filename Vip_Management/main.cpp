#include<iostream>
using namespace std;
#include"Management.h"
#include <windows.h> 
#include<fstream>

void TestTime()
{
	SYSTEMTIME start; //windows.h中  

	GetLocalTime(&start);//time.h的tm结构体一样的效果  

	int Year = start.wYear;
	cout << Year << endl;
	cout << start.wMonth << endl;
	cout << start.wHour << endl;
	cout << start.wMinute << endl;
	cout << start.wSecond << endl;
}

int main()
{
	Management manage;
	string choice = { "0" };
	while (1)
	{
		int num=manage.Login();
		if (num == 1)
		{
			break;
		}
		else
		{
			cout << "用户名或者密码有误，请重试" << endl;
			system("pause");
			system("cls");
		}
	}
	while (1)
	{
		manage.ShowMenu();
		cout << "请输入你的选择" << endl;
		cin >> choice;
		switch (atoi(choice.c_str()))//string 转换为int
		{
		case 100:
			manage.ExitSys();
			break;
		case 1:
			manage.AddMember();
			break;
		case 2:
			manage.ShowMember();
			break;
		case 3:
			manage.DelteMember();
			break;
		case 4:
			manage.Consume();
			break;
		case 5:
			manage.FindMember();
			break;
		case 6:
			manage.ModifyMember();
			break;
		case 7:
			manage.ShowMember_Consume_Info();
			break;
		case 8:
			manage.Show_SpecificMember_Consume_Info();
			break;
		case 9:
			manage.Show_SpecificDate_Year_Consume_Info();
			break;
		case 10:
			manage.Show_SpecificDate_Year_Month_Consume_Info();
			break;
		case 11:
			manage.Show_SpecificDate_Year_Month_Day_Consume_Info();
			break;
		case 12:
			manage.Record_Member_Find();
			break;
		case 13:
			manage.TempCustom_Consume();
			break;
		case 14:
			manage.TempCustom_Consume_Find(manage.FindYear);
			break;
		case 15:
			manage.TempCustom_Consume_Find(manage.FindMonth);
			break;
		case 16:
			manage.TempCustom_Consume_Find(manage.FindDay);
			break;
		default:system("cls");
			break;
		}


	}

}
