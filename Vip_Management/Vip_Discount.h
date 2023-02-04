#pragma once
#include "Vip.h"
#include<string>


class Vip_Discount :
    public Vip
{
    friend class Management;
public:
    Vip_Discount();
    ~Vip_Discount();
   
   
private:
    std::string v_name;
    std::string v_phone;
    int v_flag;
    std::string v_money;
    float discount;//уш©ш

    void func();
};

