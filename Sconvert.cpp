#include <string>
#include <iostream>
#include "commalgo.hh"
std::string Sconvert(std::string s, int line_counter)
{
    std::string hex;
    std::string temp, inst, rs2 = " ", rs1 = " ", imm_bin;
    int imm;
    std::string binary, opcode, funct3;
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

            switch (k)
            {
            case 0:
                inst = temp;
                break;
            case 1:
                rs2 = temp;
                break;
            case 2:
                imm = stoi(temp);
                break;
            case 3:
                rs1 = temp;
                break;
            }
            temp = "";
            k++;
        }
    }

    opcode = "0100011";
    if (inst == "sb")
        funct3 = "000";
    else if (inst == "sh")
        funct3 = "001";
    else if (inst == "sw")
        funct3 = "010";
    else if (inst == "sd")
        funct3 = "011";
    imm_bin = deci_to_bi(imm, 12);
    binary = imm_bin.substr(0, 7) + register_to_bi(rs2, line_counter) + register_to_bi(rs1, line_counter) + funct3 + imm_bin.substr(7, 5) + opcode;
    hex = decimal_to_hex(binary_to_decimal(binary));
    return hex;
}
