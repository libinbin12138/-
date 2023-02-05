#include<iostream>
using namespace std;
#include"Management.h"
#include <windows.h> 
void testTime()
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
	while (true)
	{
		manage.ShowMenu();
		cout << "请输入你的选择" << endl;
		cin >> choice;
		switch (atoi(choice.c_str()))//string 转换为int
		{
		case 0:
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
		default:system("cls");
			break;
		}


	}

}
