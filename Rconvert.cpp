#include<iostream>
#include<string>
#include"commalgo.hh"
std::string Rconvert(std::string s,int line_counter)
{   
    //std::cout<<s<<std::endl;
    std::string hex;
    std::string temp,inst,rs2 = " ",rs1 = " ",rd = " ";
    std::string binary,opcode,funct3,funct7;
    unsigned int i = 0,k = 0;
    
    while (i <= s.length()) {
    while (s[i] == ' ' || s[i] == ',') {
        i++;
    }
    temp = temp + s[i++];
    if(s[i] == ' ' || s[i] == '\0' || s[i] == ','){
           switch(k){
               case 0:
               inst = temp;
               break;
               case 1: 
               rd = temp;
               break;
               case 2: 
               rs1 = temp;
               break;
               case 3:
               rs2 = temp;
               break;
           }
            temp = "";
            k++;
        }
    }
    opcode = "0110011";
    funct7 = "0000000";
    
        if(inst == "add")
        funct3 = "000";
        else if(inst == "sub"){
        funct3 = "000";
        funct7 = "0100000";
        }
        else if(inst == "xor")
        funct3 = "100";
        else if(inst == "or") 
        funct3 = "110";
        else if(inst == "and")
        funct3 = "111";
        else if(inst == "sll")
        funct3 = "001";
        else if(inst == "srl")
        funct3 = "101";
        else if(inst == "sra"){
        funct3 = "101";
        funct7 = "0100000";
        }
        else if(inst == "slt")
        funct3 = "010";
        else if(inst == "sltu")
        funct3 = "011";
        
    binary = funct7 + register_to_bi(rs2,line_counter) + register_to_bi(rs1,line_counter) + funct3 + register_to_bi(rd,line_counter) + opcode;
    return decimal_to_hex(binary_to_decimal(binary));


}
