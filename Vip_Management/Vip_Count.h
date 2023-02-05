#pragma once
#include "Vip.h"
#include<string>
#include <windows.h>

class Vip_Count :
    public Vip
{
public:
    Vip_Count();
    ~Vip_Count();
    friend class Management;

private:
    std::string v_name;
    std::string v_phone;
    float v_Remain_money;//���ѽ��
    int v_Sum_Num;//����
    SYSTEMTIME ConsumTime;

    void func();
};

