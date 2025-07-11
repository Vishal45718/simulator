#include<iostream>
#include<string>
#include"commalgo.hh"

std::string Uconvert(std::string s, int line_counter)
{
    std::string hex;
    std::string binary,temp,inst,rd = " ";
    std::string opcode;
    std::string imm = "";
    int imm_dup;
    unsigned int i = 0,k = 0;
   
 while (i < s.length()) {
        while (s[i] == ' ' || s[i] == ',' || s[i] == '(' || s[i] == ')') {
            i++;
        }   
        temp = temp + s[i++];
        if(s[i] == ' ' || s[i] == '\0'|| s[i] == ',' || s[i] == '(' || s[i] == ')'){
            if(k == 0)
                inst = temp;
            else if(k == 1)
                rd = temp;
            else if(k == 2)
                imm = temp;
            temp = "";
            k++;
        }
}

if (inst == "auipc") { opcode = "0010111"; }
    if (inst == "lui") { opcode = "0110111"; }

   
    if (imm.substr(0, 2) == "0x") {
        
        imm_dup = hex_to_deci(imm.substr(2)); 
    } else {
    
        imm_dup = stoi(imm);
    }

   
    imm = deci_to_bi(imm_dup, 20);

    
    binary = imm + register_to_bi(rd, line_counter) + opcode;

   
    return decimal_to_hex(binary_to_decimal(binary));

}
