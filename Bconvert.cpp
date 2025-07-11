#include<iostream>
#include<string>
#include<cmath>
#include"commalgo.hh"

std::string Bconvert(std::string s , int line_counter, struct store_label label_line[])
{
    std::string hex;
    std::string label,temp,inst,rs2 = " ",rs1 = " ";
    std::string binary,opcode,funct3;
    std::string imm_1 = "";
    std::string imm_2 = "";
    std::string imm_3 = "";
    std::string imm_4 = "";
    std::string imm = "";

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
                rs1 = temp;
            else if(k == 2)
                rs2 = temp;
            else if(k == 3)
                label = temp;
            temp = "";
            k++;
        }
    }
    if(!search_label(label , label_line))
    {
        std::cout<<"No such label present as '" << label << "' in code to point to" <<std::endl;
        return "No such label present";
    }
    int imm_int= 4*(search_label(label , label_line) - line_counter);
    if(!((imm_int) < (pow(2,11) - 1) && (imm_int) >= -pow(2,11)))
        {
            std::cout<<"label out of bounds :"<< label <<" at line number: "<<line_counter<<std::endl;
            return "label out of bounds";
        }
    imm = deci_to_bi(imm_int,13); 

    imm_1 = imm.substr(0,1);
    imm_2 = imm.substr(2,6);
    imm_3 = imm.substr(8,4);
    imm_4 = imm.substr(1,1);

    opcode = "1100011";
    if(inst == "beq") funct3 = "000";
    if(inst == "bne") funct3 = "001";
    if(inst == "blt") funct3 = "100";
    if(inst == "bge") funct3 = "101";
    if(inst == "bltu") funct3 = "110";
    if(inst == "bgeu") funct3 = "111";



    binary = imm_1 + imm_2 + register_to_bi(rs2,line_counter) + register_to_bi(rs1,line_counter) + funct3 + imm_3 + imm_4 + opcode;

    return decimal_to_hex(binary_to_decimal((binary)));

}
