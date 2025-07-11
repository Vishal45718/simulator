#include <iostream>
#include <string>
#include <cmath>
#include "commalgo.hh"

std::string Jconvert(std::string s, int line_counter, struct store_label label_line[])
{
    std::string hex;
    std::string binary, temp, inst, rd, label;
    std::string opcode;
    std::string imm_1 = "";
    std::string imm_2 = "";
    std::string imm_3 = "";
    std::string imm_4 = "";
    int imm_dup = 0;
    unsigned int i = 0, k = 0;

    while (i < s.length())
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
            else if (k == 1)
                rd = temp;
            else if (k == 2)
                label = temp;
            temp = "";
            k++;
        }
    }
    i = 0;
    while (i < label.length())
    {
        if (label[i] > '9' || label[i] < '0')
        {
            if (i == 0 && label[i] != '-')
            {
                imm_dup = 4 * (search_label(label, label_line) - line_counter);
                i = -1;
                break;
            }
            if (i != 0)
            {
                imm_dup = 4 * (search_label(label, label_line) - line_counter);
                i = -1;
                break;
            }
        }
        i++;
    }
    if (!search_label(label, label_line))
    {
        std::cout << "No such label present as '" << label << "' in code to point to" << std::endl;
        return "No such label present";
    }
    if (imm_dup == 0)
    {
        imm_dup = stoi(label);
    }
    if (!(imm_dup < (pow(2, 20) - 1) && imm_dup >= -pow(2, 20)))
    {
        std::cout << "label out of bounds :" << imm_dup << " at line number: " << line_counter << std::endl;
        return "label out of bounds";
    }
    opcode = "1101111";

    label = deci_to_bi(imm_dup, 21);

    imm_1 = label.substr(0, 1);
    imm_2 = label.substr(10, 10);
    imm_3 = label.substr(9, 1);
    imm_4 = label.substr(1, 8);

    binary = imm_1 + imm_2 + imm_3 + imm_4 + register_to_bi(rd, line_counter) + opcode;
    return decimal_to_hex(binary_to_decimal(binary));
}
