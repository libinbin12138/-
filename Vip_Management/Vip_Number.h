#pragma once
#include "Vip.h"
#include<string>
class Vip_Number :
    public Vip
{

      friend class Management;
 public:
        Vip_Number();
        ~Vip_Number();


 private:
        int v_flag;
        std::string v_name;
        std::string v_phone;
        std::string v_money;
        int v_num;//理发次数

        void func();
 };

