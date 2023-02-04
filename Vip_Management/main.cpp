#include<iostream>
using namespace std;
#include"Management.h"
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
		default:system("cls");
			break;
		}


	}

}
