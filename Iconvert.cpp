#include <iostream>
#include <cmath>
#include "commalgo.hh"
std::string Iconvert(std::string s, int line_counter)
{
    std::string hex;
    std::string temp, inst, rs1 = " ", rd = " ";
    std::string binary, opcode_1, opcode_2, opcode_3, funct3;
    std::string imm = "";
    unsigned int i = 0, k = 0;

    while (i <= s.length())
    {
        while (s[i] == ' ' || s[i] == ',' || s[i] == '(' || s[i] == ')')
        {
            i++;
        }
        temp = temp + s[i++];
        if (s[i] == ' ' || s[i] == '\0' || s[i] == ',' || s[i] == '(' || s[i] == ')')
        {
            if (k == 0)
                inst = temp;
            else if (inst == "lb" || inst == "lh" || inst == "lw" || inst == "ld" || inst == "lbu" || inst == "lhu" || inst == "lwu")
            {
                switch (k)
                {
                    break;
                case 1:
                    rd = temp;
                    break;
                case 2:
                    imm = temp;
                    break;
                case 3:
                    rs1 = temp;
                    break;
                }
            }
            else if (k != 0)
            {
                switch (k)
                {
                    break;
                case 1:
                    rd = temp;
                    break;
                case 2:
                    if(inst == "jalr" && s[i] == '(')
                    {
                        if ((temp[0] <= '9' && temp[0] >= '0') || temp[0] == '-')  
                           imm = temp;
                        else
                            rs1 = temp;
                        break;
                    }
                    rs1 = temp;
                    break;
                case 3:
                    if(inst == "jalr" && s[i] == ')')
                    {
                        if ((temp[0] <= '9' && temp[0] >= '0') || temp[0] == '-')
                            imm = temp;
                        else
                            rs1 = temp;
                        break;
                    }
                    imm = temp;
                    break;
                }
            }
            temp = "";
            k++;
        }
    }

    i = 0;
    while (i < imm.length())
    {
        if (!((imm[i] <= '9' && imm[i] >= '0') || imm[i] == '-'))
        {
            std::cout << "Invalid immediate (Iformat) :" << imm << " at line number: " << line_counter << std::endl;
            return "Invalid immediate value(Iformat) at line number: " + std::to_string(line_counter);
        }
        i++;
    }
    if (!(stoi(imm) < (pow(2, 11) - 1) && stoi(imm) >= -pow(2, 11)))
    {
        std::cout << "immediate out of bounds :" << imm << " at line number: " << line_counter << std::endl;
        return "Immediate out of bounds";
    }
    
    opcode_1 = "0010011";
    opcode_2 = "0000011";
    opcode_3 = "1100111";

    if (inst == "addi" || inst == "lb" || inst == "jalr")
        funct3 = "000";
    else if (inst == "xori" || inst == "lbu")
        funct3 = "100";
    else if (inst == "ori" || inst == "lwu")
        funct3 = "110";
    else if (inst == "andi")
        funct3 = "111";
    else if (inst == "slli" || inst == "lh")
        funct3 = "001";
    else if (inst == "srli" || inst == "srai" || inst == "lhu")
        funct3 = "101";
    else if (inst == "slti" || inst == "lw")
        funct3 = "010";
    else if (inst == "sltiu" || inst == "ld")
        funct3 = "011";

    if (inst == "addi" || inst == "xori" || inst == "ori" || inst == "andi" || inst == "slti" || inst == "sltiu")
        binary = deci_to_bi(stoi(imm), 12) + register_to_bi(rs1, line_counter) + funct3 + register_to_bi(rd, line_counter) + opcode_1;

    if (inst == "slli" || inst == "srli")
    {
        binary = "000000" + deci_to_bi(stoi(imm), 6) + register_to_bi(rs1, line_counter) + funct3 + register_to_bi(rd, line_counter) + opcode_1;
    }
    if (inst == "srai")
    {
        binary = "010000" + deci_to_bi(stoi(imm), 6) + register_to_bi(rs1, line_counter) + funct3 + register_to_bi(rd, line_counter) + opcode_1;
    }

    if (inst == "ld" || inst == "lb" || inst == "lbu" || inst == "lh" || inst == "lhu" || inst == "lw" || inst == "lwu")
        binary = deci_to_bi(stoi(imm), 12) + register_to_bi(rs1, line_counter) + funct3 + register_to_bi(rd, line_counter) + opcode_2;

    if (inst == "jalr")
        binary = deci_to_bi(stoi(imm), 12) + register_to_bi(rs1, line_counter) + funct3 + register_to_bi(rd, line_counter) + opcode_3;

    return decimal_to_hex(binary_to_decimal(binary));
}