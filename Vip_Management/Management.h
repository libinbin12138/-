#pragma once
#include<list>
#include<string>
class Vip;
class Vip_Discount;
class Vip_Number;

class Management
{
	int Vip_num;
	std::list<Vip*>L_saved;
	std::list<Vip_Discount*>L_DTemp;//用于打印时的区分
	std::list<Vip_Number*>L_NTemp;
public:
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
};

