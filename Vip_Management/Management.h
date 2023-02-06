#pragma once
#include<list>
#include<string>
#include <windows.h> 

class Vip;
class Vip_Discount;
class Vip_Number;
class Vip_Count;

class Manager
{
public:
	friend class Management;
	Manager();
	~Manager();
	void SetUser(std::string name,std::string password);

private:
	std::string Username;
	std::string PassWord;
};
class Management
{
	int Vip_num;
	SYSTEMTIME Vip_Time;
	Manager manager;
	std::list<Vip*>L_saved;
	std::list<Vip_Discount*>L_DTemp;//用于查找、打印等时的区分
	std::list<Vip_Number*>L_NTemp;

	std::list<Vip_Count*>L_Consume_Temp;//统计消费

	std::list<Manager>L_manager;
public:
	enum FindType
	{
		ConsumeFile = 1,
		RecordFile = 2
	};
	Management();
	~Management();
	int InitMember();
	void ClaerList();
	void ShowMenu();
	void ExitSys();

	void AddMember();
	int SaveMember(int choice_flag,Vip*vip);//保存新增会员
	int SaveMember();
	void ShowMember();
	void ReadMemberInfo();

	int FindMember();
	int FindMember_Name(std::string Fname);
	int FindMember_Phone(std::string Phone);

	int DelteMember();
	int DeleteMember_Name(std::string choice, int flag);
	int DeleteMember_Phone(std::string choice,int flag);
	
	void Consume();
	void Consume_DName(std::string choice);
	void Consume_NUM_Name(std::string choice);
	void Consume_DPhone(std::string choice);
	void Consume_NUM_Phone(std::string choice);

	void ModifyMember();
	void ModifyMember_Name();
	void ModifyMember_DName(std::string choice);
	void ModifyMember_NUM_Name(std::string choice);
	void ModifyMember_Phone();
	void ModifyMember_DPhone(std::string choice);
	void ModifyMember_NUM_Phone(std::string choice);

	void ReadMember_Consume_Info(FindType type);
	void ShowMember_Consume_Info();
	void AddMember_Consume(int flag, Vip* p, float money);
	void SaveMember_Consume(Vip_Count* p);
	void Show_SpecificMember_Consume_Info();
	void Show_SpecificDate_Year_Consume_Info();
	void Show_SpecificDate_Year_Month_Consume_Info();
	void Show_SpecificDate_Year_Month_Day_Consume_Info();

	int ReadLoginFile();
	int Login();
	void CreateManeger();

	void Record_Member_Add(int flag, Vip* p, float money);
	void Record_Member_Save(Vip_Count* p);

	void Record_Member_Find();
};

