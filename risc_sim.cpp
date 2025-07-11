#include <iostream>
#include <fstream>
#include <string>
#include <stack>
#include <vector>
#include <cstdint>
#include <iomanip>
#include <algorithm>

#define MAX 1000
using namespace std;

struct mem
{
    string mem_value;
};

struct mem memory[0x50000];
//made a global variable fro memory as can be accessed globally

struct regs
{
    int64_t reg_value;
    std::string reg_name;
};
struct stack_label
{

    string function_label;
    int line_number;

    stack_label(std::string label, int line) : function_label(label), line_number(line) {}//constructor
};
// regs x[32];

#include "struct.hh"
#include "commalgo.hh"
#include "sort_find.hh"
#include "risc_sim.hh"
void check_inst(vector<pair<string, string>> instruction_line, struct regs *x, int *pc , int line_number , stack<stack_label> *show_func , struct store_label *label_line , int data_length)
{

    string instruction = instruction_line[*pc].first;
    string binary_code = instruction_line[*pc].second;
    int substr_len = instruction.find(' ');
    string inst = instruction.substr(0, substr_len);
    // cout << inst << endl;
    if (inst == "add" || inst == "sub" || inst == "xor" || inst == "or" || inst == "and" || inst == "sll" || inst == "srl" || inst == "sra" || inst == "slt" || inst == "sltu")
    {
        string rs2_str = binary_code.substr(7, 5);
        string rs1_str = binary_code.substr(12, 5);
        string rd_str = binary_code.substr(20, 5);

        int rd = binary_to_decimal(rd_str);
        int rs1 = binary_to_decimal(rs1_str);
        int rs2 = binary_to_decimal(rs2_str);

        if (inst == "add")
        {
            x[rd].reg_value = x[rs1].reg_value + x[rs2].reg_value;
            // cout << x[rd].reg_value << endl;
            // cout << x[rs1].reg_value << endl;
            // cout << x[rs2].reg_value << endl;
        }
        else if (inst == "sub")
        {
            x[rd].reg_value = x[rs1].reg_value - x[rs2].reg_value;
        }
        else if (inst == "xor")
        {
            x[rd].reg_value = x[rs1].reg_value ^ x[rs2].reg_value;
        }
        else if (inst == "or")
        {
            x[rd].reg_value = x[rs1].reg_value | x[rs2].reg_value;
        }
        else if (inst == "and")
        {
            x[rd].reg_value = x[rs1].reg_value & x[rs2].reg_value;
        }
        else if (inst == "sll")
        {
            x[rd].reg_value = x[rs1].reg_value << x[rs2].reg_value;
        }
        else if (inst == "srl")
        {
            x[rd].reg_value = (unsigned int)x[rs1].reg_value >> x[rs2].reg_value;
        }
        else if (inst == "sra")
        {
            x[rd].reg_value = x[rs1].reg_value >> x[rs2].reg_value;
        }
        else if (inst == "slt")
        {
            x[rd].reg_value = (x[rs1].reg_value < x[rs2].reg_value) ? 1 : 0;
        }
        else if (inst == "sltu")
        {
            x[rd].reg_value = ((unsigned int)x[rs1].reg_value < (unsigned int)x[rs2].reg_value) ? 1 : 0;
        }
        string label = show_func->top().function_label;
        show_func->pop();
        show_func->push({label, *pc + 1});//we push in pc of previous line number

        *pc = *pc + 1;
    }

    else if (inst == "addi" || inst == "xori" || inst == "ori" || inst == "andi" || inst == "slli" || inst == "srli" || inst == "srai" || inst == "slti" || inst == "sltiu")
    {
        string rd_str = binary_code.substr(20, 5);
        string rs1_str = binary_code.substr(12, 5);
        string imm_str = binary_code.substr(0, 12);

        int rd = binary_to_decimal(rd_str);
        int rs1 = binary_to_decimal(rs1_str);
        int imm = stoi(bi_to_signed_decimal(imm_str));
        // cout<<imm<<endl;
        // cout<<rd<<rs1<<x[rd].reg_value<<x[rs1].reg_value<<endl;
        if (inst == "addi")
        {
            // cout<<x[rs1].reg_value<<endl;
            // cout<<imm<<endl;
            // cout<<x[rd].reg_value<<endl;
            x[rd].reg_value = x[rs1].reg_value + imm;
            // cout<<x[rs1].reg_value<<endl;
            // cout<<x[rd].reg_value<<endl;
        }
        else if (inst == "xori")
        {
            x[rd].reg_value = x[rs1].reg_value ^ imm;
        }
        else if (inst == "ori")
        {
            x[rd].reg_value = x[rs1].reg_value | imm;
        }
        else if (inst == "andi")
        {
            x[rd].reg_value = x[rs1].reg_value & imm;
        }
        else if (inst == "slli")
        {
            x[rd].reg_value = x[rs1].reg_value << imm;
        }
        else if (inst == "srli")
        {
            x[rd].reg_value = (unsigned int)x[rs1].reg_value >> imm;
        }
        else if (inst == "srai")
        {
            x[rd].reg_value = x[rs1].reg_value >> imm;
        }
        else if (inst == "slti")
        {
            x[rd].reg_value = (x[rs1].reg_value < imm) ? 1 : 0;
        }
        else if (inst == "sltiu")
        {
            x[rd].reg_value = ((unsigned int)x[rs1].reg_value < (unsigned int)imm) ? 1 : 0;
        }
        string label = show_func->top().function_label;
        show_func->pop();
        show_func->push({label, *pc + 1});//we push in pc of executed line's line_number

        *pc = *pc + 1;

    }
    else if (inst == "jalr")
    {
        string rd_str = binary_code.substr(20, 5);
        string rs1_str = binary_code.substr(12, 5);
        string imm_str = binary_code.substr(0, 12);

        int rd = binary_to_decimal(rd_str);
        int rs1 = binary_to_decimal(rs1_str);
        int imm = stoi(bi_to_signed_decimal(imm_str));
        
        show_func->pop();
        x[rd].reg_value = *pc + 1;
        *pc = x[rs1].reg_value/4 + imm;
    }

    else if (inst == "lb" || inst == "lh" || inst == "lw" || inst == "ld" || inst == "lbu" || inst == "lhu" || inst == "lwu")
    {
        string rd_str = binary_code.substr(20, 5);
        string rs1_str = binary_code.substr(12, 5);
        string imm_str = binary_code.substr(0, 12);

        int rd = binary_to_decimal(rd_str);
        int rs1 = binary_to_decimal(rs1_str);
        int imm = binary_to_decimal(imm_str);
        string temp_hex = "";
        if (inst == "lb")
        {
            temp_hex = memory[x[rs1].reg_value + imm].mem_value;

            // Perform sign extension for byte (8 bits)
            if (temp_hex.length() == 2 && (temp_hex[0] >= '8')) // Check if MSB is 1
            {
                temp_hex = string(14, 'F') + temp_hex; // Sign-extend to 16 hex digits
            }

            x[rd].reg_value = hex_to_deci_64(temp_hex);
        }
        else if (inst == "lh")
        {
            for (int i = 0; i < 2; i++)
            {
                temp_hex = memory[x[rs1].reg_value + imm + i].mem_value + temp_hex;
            }

            // Perform sign extension for halfword (16 bits)
            if (temp_hex.length() == 4 && (temp_hex[0] >= '8')) // Check if MSB is 1
            {
                temp_hex = string(12, 'F') + temp_hex; // Sign-extend to 16 hex digits
            }

            x[rd].reg_value = hex_to_deci_64(temp_hex);
        }
        else if (inst == "lw")
        {
            for (int i = 0; i < 4; i++)
            {
                temp_hex = memory[x[rs1].reg_value + imm + i].mem_value + temp_hex;
            }

            // Perform sign extension for word (32 bits)
            if (temp_hex.length() == 8 && (temp_hex[0] >= '8')) // Check if MSB is 1
            {
                temp_hex = string(8, 'F') + temp_hex; // Sign-extend to 16 hex digits
            }

            x[rd].reg_value = hex_to_deci_64(temp_hex);
        }
        else if (inst == "ld")
        {
            for (int i = 0; i < 8; i++)
            {
                temp_hex = memory[x[rs1].reg_value + imm + i].mem_value + temp_hex;
            }
            // cout<<temp_hex<<endl;
            // `ld` loads a doubleword (64 bits), so no additional sign extension is needed
            x[rd].reg_value = hex_to_deci_64(temp_hex);
        }
        else if (inst == "lbu")
        {
            temp_hex = memory[x[rs1].reg_value + imm].mem_value;
            x[rd].reg_value = hex_to_deci_64_unsigned(temp_hex); // Assume hex_to_deci_64_unsigned handles unsigned interpretation.
        }
        else if (inst == "lhu")
        {
            for (int i = 0; i < 2; i++)
            {
                temp_hex = memory[x[rs1].reg_value + imm + i].mem_value + temp_hex;
            }
            x[rd].reg_value = hex_to_deci_64_unsigned(temp_hex);
        }
        else if (inst == "lwu")
        {
            for (int i = 0; i < 4; i++)
            {
                temp_hex = memory[x[rs1].reg_value + imm + i].mem_value + temp_hex;
            }
            x[rd].reg_value = hex_to_deci_64_unsigned(temp_hex);
        }
        string label = show_func->top().function_label;
        show_func->pop();
        show_func->push({label, *pc + 1});//we push in pc of executed line's line_number

        *pc = *pc + 1;
    }

    else if (inst == "sb" || inst == "sh" || inst == "sw" || inst == "sd")
    {
        string rs2_str = binary_code.substr(7, 5);
        string rs1_str = binary_code.substr(12, 5);
        string imm1_str = binary_code.substr(0, 7);
        string imm2_str = binary_code.substr(20, 5);

        string imm = imm1_str + imm2_str;

        int imm_int = binary_to_decimal(imm);
        int rs2 = binary_to_decimal(rs2_str);
        int rs1 = binary_to_decimal(rs1_str);
        string temp_hex = signed_decimal_to_hex_no(x[rs2].reg_value, 16);
        if (inst == "sb")
        {
            memory[x[rs1].reg_value + imm_int].mem_value = temp_hex.substr(14, 2);
        }
        if (inst == "sh")
        {
            for (int i = 0; i < 2; i++)
            {
                memory[x[rs1].reg_value + imm_int + i].mem_value = temp_hex.substr(14 - i * 2, 2);
            }
        }
        if (inst == "sw")
        {
            for (int i = 0; i < 4; i++)
            {
                memory[x[rs1].reg_value + imm_int + i].mem_value = temp_hex.substr(14 - i * 2, 2);
            }
        }
        if (inst == "sd")
        {
            for (int i = 0; i < 8; i++)
            {
                memory[x[rs1].reg_value + imm_int + i].mem_value = temp_hex.substr(14 - i * 2, 2);
            }
        }
        
        string label = show_func->top().function_label;
        show_func->pop();
        show_func->push({label, *pc + 1});//we push in executed line's line_number

        *pc = *pc + 1;
    }
    else if (inst == "beq" || inst == "bne" || inst == "blt" || inst == "bge" || inst == "bltu" || inst == "bgeu")
    {
        string imm_str = binary_code.substr(0, 1) + binary_code.substr(24, 1) + binary_code.substr(1, 6) + binary_code.substr(20, 4) + "0";
        string rs1_str = binary_code.substr(12, 5);
        string rs2_str = binary_code.substr(7, 5);

        int rs1 = binary_to_decimal(rs1_str);
        int rs2 = binary_to_decimal(rs2_str);
        int imm = stoi(bi_to_signed_decimal(imm_str));

        string label = show_func->top().function_label;
        show_func->pop();
        show_func->push({label, *pc + 1});//we push in executed line's line_number

        if (inst == "beq")
        {
            if (x[rs1].reg_value == x[rs2].reg_value)
            {
                *pc = *pc + imm / 4;
            }
            else
            {
                *pc = *pc + 1;
            }
        }
        else if (inst == "bne")
        {
            if (x[rs1].reg_value != x[rs2].reg_value)
            {
                *pc = *pc + imm / 4;
            }
            else
            {
                *pc = *pc + 1;
            }
        }
        else if (inst == "blt")
        {
            if (x[rs1].reg_value < x[rs2].reg_value)
            {
                *pc = *pc + imm / 4;
            }
            else
            {
                *pc = *pc + 1;
            }
        }
        else if (inst == "bge")
        {
            if (x[rs1].reg_value >= x[rs2].reg_value)
            {
                *pc = *pc + imm / 4;
            }
            else
            {
                *pc = *pc + 1;
            }
        }
        else if (inst == "bltu")
        {
            if ((unsigned int)x[rs1].reg_value < (unsigned int)x[rs2].reg_value)
            {
                *pc = *pc + imm / 4;
            }
            else
            {
                *pc = *pc + 1;
            }
        }
        else if (inst == "bgeu")
        {
            if ((unsigned long int)x[rs1].reg_value >= (unsigned long int)x[rs2].reg_value)
            {
                *pc = *pc + imm / 4;
            }
            else
            {
                *pc = *pc + 1;
            }
        }
    }
    else if (inst == "jal")
    {
        string imm_str = binary_code.substr(0, 1) + binary_code.substr(12, 8) + binary_code.substr(11, 1) + binary_code.substr(1, 10) + '0';
        string rd_str = binary_code.substr(20, 5);

        int rd = binary_to_decimal(rd_str);
        int imm = stoi(bi_to_signed_decimal(imm_str));


        string label = show_func->top().function_label;
        show_func->pop();
        show_func->push({label, *pc + 1});//we push in executed line's line_number

        
        x[rd].reg_value = (*pc + 1)*4;
        *pc = *pc + imm / 4;
        int i = 0;
        for(i = 0;i<1000;i++)
        {
            if(label_line[i].label_line_num == *pc + data_length)
            {
                break;
            }
        }
        if (i < 1000)
        {
            show_func->push({label_line[i].label, *pc +1});
        }
    
    }

    else if (inst == "lui")
    {
        string imm_str = binary_code.substr(0, 20);
        string rd_str = binary_code.substr(20, 5);
        // cout<<binary_code<<"  "<<imm_str<<"  "<<rd_str<<endl;
        int rd = binary_to_decimal(rd_str);
        long long int imm = binary_to_decimal(imm_str);

        if (inst == "lui")
        {
            // imm = imm << 12;
            x[rd].reg_value = imm << 12;
            // cout<<imm<<endl;
            // cout<<x[rd].reg_value<<endl;
        }
        string label = show_func->top().function_label;
        show_func->pop();
        show_func->push({label, *pc + 1});//we push in executed line's line_number

        *pc = *pc + 1;
    }
}

void run(vector<pair<string, string>> instruction_lines, struct regs *x, int *pc, int *breakpoint , stack<stack_label> *show_func , struct store_label *label_line , int data_length)
{
    unsigned long long int line_number = 0;
    
    // Sort breakpoints to ensure the lowest breakpoint is always first
    std::sort(breakpoint, breakpoint + 5);

    if (*pc < 0 || *pc >= instruction_lines.size())
    {
        if(*pc>=instruction_lines.size())
        {
            if(!show_func->empty())
                show_func->pop();
        }
        cout << "Nothing to run" << endl;
        return;
    }

    while (*pc < instruction_lines.size())
    {
        line_number = *pc;
        x[0].reg_value = 0;
        // Check if the current PC matches any of the breakpoints
        if ( (std::find(breakpoint, breakpoint + 5, *pc)) != (breakpoint + 5) )
        {
            cout<<"Execution stopped at breakpoint"<<endl;
            break;
        }
        else
        {
            check_inst(instruction_lines, x, pc , line_number , show_func , label_line , data_length);
        }

        string pc_hex = decimal_to_hex_no(line_number * 4, 8);
        cout << "Executed " << instruction_lines[line_number].first << "; PC=0x" << pc_hex << endl;
    }
    if(*pc>=instruction_lines.size())
    {
        if(!show_func->empty())
            show_func->pop();
    }
}
void step(vector<pair<string, string>> instruction_lines, struct regs *x, int *pc, int *breakpoint , stack<stack_label> *show_func , struct store_label *label_line , int data_length)
{
    unsigned long long int line_number = *pc;
    x[0].reg_value = 0;
    if (*pc < 0 || *pc >= instruction_lines.size())
    {
        if(*pc>=instruction_lines.size())
        {
            if(!show_func->empty())
                show_func->pop();
        }
        cout << "Nothing to step" << endl;
        return;
    }
    check_inst(instruction_lines, x, pc , line_number , show_func , label_line , data_length);
    string pc_hex = decimal_to_hex_no(line_number * 4, 8);
    cout << "Executed " << instruction_lines[line_number].first << " ; PC=0x" << pc_hex << endl;
}

void store_in_mem(string int_value, int *mem_adrr, int bytes)
{

    if (*mem_adrr >= 0x50000)
    {
        cerr << "Memory limit exceeded!" << endl;
        return;
    }

    // we convert decimal to its positive number if is negative and then convert it to its corresponding hex
    string hex = signed_decimal_to_hex_no(stoll(int_value), 16);
    // cout<<stoll(int_value)<<endl;
    // cout<<hex<<endl;

    for (int i = 0; i < bytes; i++)
    {
        // we take last 4 digits in 2 2 digit format of little endian
        memory[*mem_adrr].mem_value = hex.substr(14 - 2 * i, 2);
        // cout<<"hi"<<endl;
        memory[*mem_adrr].mem_value = memory[*mem_adrr].mem_value;
        // cout<<memory[*mem_adrr].mem_value<<endl;
        *mem_adrr = *mem_adrr + 1;
    }
}

void storing_label(string filename, struct store_label *label_line)
{
    string assembly_instruction; // stores line by line assemble instruction
    int label_index = 0;
    int line_index = 0;
    int i = 0;
    ifstream infile(filename);
    while (getline(infile, assembly_instruction))
    {
        i = 0;
        while (i < assembly_instruction.length())
        {
            if (assembly_instruction[i] == ':')
            {
                label_line[label_index].label = assembly_instruction.substr(0, i);
                label_line[label_index].label_line_num = line_index;
                // cout << label_line[label_index].label << " " << label_line[label_index].label_line_num << endl;
                label_index = label_index + 1;
            }
            i++;
        }
        line_index = line_index + 1;
    }
    infile.clear();
    infile.seekg(0, std::ios::beg);
}
// function to remove the label from the assembly instruction and return the instruction with label removed
string remove_label(string assembly_instruction, int index,struct store_label *label_line)
{
    int i = 0;
    // if assembly code contains a label we remove it and send it to storage
    while (i < assembly_instruction.length())
    {
        if (assembly_instruction[i] == ':')
        {
            while (i < assembly_instruction.length() && (assembly_instruction[i] == ' ' || assembly_instruction[i] == ':' || assembly_instruction[i] == '\t'))
                i++;
            assembly_instruction = assembly_instruction.substr(i);
            break;
        }
        i++;
    }
    return assembly_instruction;
}
string remove_leading_blanks(string assembly_instruction)
{
    int i = 0;
    while (i < assembly_instruction.length() && (assembly_instruction[i] == ' ' || assembly_instruction[i] == '\t'))
    {
        i++;
    }
    return assembly_instruction.substr(i);
}

// fucntion which would take in the load instruction and return a vector containing all strings and their respective binaries as a vector
vector<pair<string, string>> parse(string filename, struct store_label *label_line, int *data_length)
{
    string assembly_instruction;             // stores line by line assemble instruction
    string binary;                           // stores the binary convertes value of the assembly_instruction
    vector<pair<string, string>> inst_lines; // here we store the assembly instruction and the binary
    int k = 0;                               // to check weather we have gone into a .data format instruction or weather it has finished
    // if k = 0 then we can start with the parsing of instructions
    int type = 0;
    int label_size;         // to know what is the size of array right now and where next label is to be inserted
    int mem_adrr = 0x10000; // initializes poisition where i have to store data for second or third load
    // type 1 for .dword
    // type 2 for .word
    // type 3 for .half
    // type 4 for .byte
    int index = 0; // gives us the line number being parsed at that moment
    ifstream infile(filename);
    while (getline(infile, assembly_instruction))
    {
        // if the line is a .data then ignore that line and store the values in the array called memory
        int i = 0;
        string temp = "";

        while (assembly_instruction[i] == ' ')
            i++;
        if (i < assembly_instruction.length() && assembly_instruction[i] == '.')
        {
            // cout<<index<<"FFFF"<<assembly_instruction<<endl;
            i++;
            while (i < assembly_instruction.length() && assembly_instruction[i] != ' ' && assembly_instruction[i] != ',' && assembly_instruction[i] != '\n')
            {
                temp = temp + assembly_instruction[i++];
            }
            if (temp == "data")
            {
                k = 1; // when text is called we start to store instructions in vector by making k 0
                // cout<<index<<"FFFF"<<assembly_instruction<<endl;
                index++;
                (*data_length)++;
                // cout<<data_length<<endl;
                continue;
            }
            if (temp == "text")
            {
                k = 0;
                // cout<<"camein"<<index<<endl;
                // cout<<index<<"FFFF"<<assembly_instruction<<endl;
                index++;
                (*data_length)++;
                // cout<<data_length<<endl;
                continue;
            }
            if (k == 1 && temp == "dword")
                type = 1;
            if (k == 1 && temp == "word")
                type = 2;
            if (k == 1 && temp == "half")
                type = 3;
            if (k == 1 && temp == "byte")
                type = 4;
        }
        if (k == 1)
        {
            if (assembly_instruction[i] == '\n')
            {
                index++;
                (*data_length)++;
                continue;
            }
            if (type == 0)
                continue;

            while (i < assembly_instruction.length() && assembly_instruction[i] != '\n')
            {
                while (i < assembly_instruction.length() && (assembly_instruction[i] == ' ' || assembly_instruction[i] == ',' || assembly_instruction[i] == '\t' || assembly_instruction[i] == '\n'))
                    i++;
                temp = "";
                while (i < assembly_instruction.length() && (assembly_instruction[i] != ',' && assembly_instruction[i] != ' ' && assembly_instruction[i] != '\t' && assembly_instruction[i] != '\n'))
                {
                    temp = temp + assembly_instruction[i++];
                    // cout<<temp<<endl;
                }
                // cout<<temp<<endl;
                switch (type)
                {
                case 1:
                    store_in_mem(temp, &mem_adrr, 8);
                    break;
                case 2:
                    store_in_mem(temp, &mem_adrr, 4);
                    break;
                case 3:
                    store_in_mem(temp, &mem_adrr, 2);
                    break;
                case 4:
                    store_in_mem(temp, &mem_adrr, 1);
                    break;
                }
            }
            (*data_length)++;
            // cout<<data_length<<endl;
        }

        if (k == 0)
        {
            // if label is present it gets removed and stored at in the array of structs
            assembly_instruction = remove_leading_blanks(remove_label(assembly_instruction, index, label_line));

            // we get the binary repesentation of the string
            binary = hex_to_bi(sort(assembly_instruction, index, label_line));
            // cout<<assembly_instruction<<endl;
            // cout<<sort(assembly_instruction, index, label_line)<<endl;
            // cout<<binary<<endl;

            // we store the assembly_instruction and the binary in the vector
            inst_lines.push_back(make_pair(assembly_instruction, binary));
        }

        index++;
    }
    return inst_lines;
}

void print_stack(stack<stack_label> show_func)
{
    vector<stack_label> tempVec;

    // Transfer the elements to a vector for easy access in the correct order
    while (!show_func.empty()) {
        tempVec.push_back(show_func.top());
        show_func.pop();
    }

    // Print the elements from the beginning of the vector
    for (auto it = tempVec.rbegin(); it != tempVec.rend(); ++it) {
        cout <<it->function_label <<":"<< it->line_number<<endl;
    }

}
void print_mem(int address, int length)
{
    for (int i = 0; i < length; i++)
    {
        if (address + i < 0x50000)
        { // Ensure we are within bounds
            cout << "Memory[0x" << hex << setw(5) << setfill('0') << (address + i) << "] = 0x"
                 << remove_starting_zeros(memory[address + i].mem_value) << endl;
        }
        else
        {
            cout << "Address out of bounds: 0x" << hex << setw(5) << setfill('0') << (address + i) << endl;
        }
    }
}
void initialize_mem(void)
{
    for (int i = 0; i < 0x50000; i++)
    {
        // Print an error message if the address is out of bounds
        memory[i].mem_value = "0";
    }
}
void initialize_stack(stack<stack_label> *show_func)
{
    while(!(show_func)->empty())
        (show_func)->pop();
    show_func->push(stack_label("main", 0));
}
void initialize_regs(struct regs *x)
{
    for (int i = 0; i < 32; i++)
    {
        x[i].reg_value = 0;
        x[i].reg_name = "x" + to_string(i);
    }
}
void print_regs(struct regs *x)
{
        // Set the value to 0
    cout << x[0].reg_name << " = 0x0" << endl;
        // Set the name to "x" followed by the number of the register
    for (int i = 1; i < 32; i++)
    {
        string reg_hex = remove_starting_zeros(signed_decimal_to_hex_no(x[i].reg_value, 8));
        cout << x[i].reg_name << " = 0x" << reg_hex << endl;
    }
}

int main()
{

    string instruction;                      // reads the instruction given by the user
    int pc = 0x00000000;                     // program counter to tell which line to be executed next
    store_label label_line[MAX];             // contains line index which contain a label
    regs x[32];                             // 32 registers containing the respective register values
    stack<stack_label> show_func;                  //stacck containing the respective line number and function label    
    show_func.push(stack_label("main",0));
    vector<pair<string, string>> inst_lines; // stores all the instructions and their binary representation
    int data_length = 0;                     // stores number of lines present in .data section
    int breakpoint[5];                       // stores the line number at which breakpoint is present
    for (int i = 0; i < 5; i++)
    {
        breakpoint[i] = -1;
    }
    // initializes breakpoints as -1 i.e no breakpoint in it
    int break_number = 0; // stores which numberth breakpoint it is

    while (true)
    {
        getline(cin, instruction);
        string temp; // reads the first word of the instruction given and performs respective operation
        int i = 0;   // used to iterate through the string
        while (i < instruction.length() && instruction[i] != ' ' && instruction[i] != ',' && instruction[i] != '\n')
        {
            temp = temp + instruction[i++];
        }
        if (temp == "load")
        {
            temp = "";          // reinitializes temp for finding filename
            initialize_regs(x); // initializes all the registers to 0
            initialize_mem();   // initializes all the memory to 0
            initialize_stack(&show_func);                //when called again initializes the stac
            data_length = 0;    // stores number of lines present in .data section
            for (int i = 0; i < 5; i++)
            {
                breakpoint[i] = -1;
            }
            pc = 0;
            // skips the spaces
            while (i < instruction.length() && instruction[i] == ' ')
                i++;
            // reads the filename
            while (i < instruction.length() && instruction[i] != ' ' && instruction[i] != '\n')
            {
                temp = temp + instruction[i++];
            }
            // reads the line number
            storing_label(temp, label_line);
            inst_lines = parse(temp, label_line, &data_length);
            // cout << data_length << endl;
            // for(int i = 0 ; i < inst_lines.size() ; i++)
            // {
            //     cout<<inst_lines[i].first<<" "<<inst_lines[i].second<<endl;
            // }
            // print_mem(0x10000,16);
        }
        if (temp == "run")
        {
            run(inst_lines, x, &pc, breakpoint,&show_func,label_line , data_length);
            // x[2].reg_value = -1;
        }
        if (temp == "regs")
        {
            cout << "Registers :" << endl;
            print_regs(x);
        }
        if (temp == "mem")
        {
            while (i < instruction.length() && instruction[i] == ' ')
                i++;

            string address_str = "";
            string length_str = "";

            while (i < instruction.length() && instruction[i] != ' ' && instruction[i] != '\n')
            {
                address_str += instruction[i++];
            }

            int address;
            if (address_str.substr(0, 2) == "0x")
            {

                address = hex_to_deci(address_str.substr(2));
            }
            else
            {

                address = stoi(address_str);
            }

            while (i < instruction.length() && instruction[i] == ' ')
                i++;

            while (i < instruction.length() && instruction[i] != ' ' && instruction[i] != '\n')
            {
                length_str += instruction[i++];
            }

            int length = stoi(length_str);

            print_mem(address, length);
        }
        if (temp == "exit")
        {
            cout << "Exited the simulator" << endl;
            break;
        }
        if (temp == "step")
        {
            step(inst_lines, x, &pc, breakpoint,&show_func,label_line , data_length);
        }
        if (temp == "break")
        {
            while (i < instruction.length() && instruction[i] == ' ')
                i++;
            string break_str = "";
            while (i < instruction.length() && instruction[i] != '\n')
            {
                break_str += instruction[i++];
                // cout << break_str << endl;
            }
            breakpoint[break_number] = stoi(break_str) - data_length - 1;
            cout << "Breakpoint set at line " << break_str << endl;
            break_number++;
        }
        if (temp == "del")
        {
            // Skip the spaces
            while (i < instruction.length() && instruction[i] == ' ')
                i++;

            string sub_command = "";
            // Read the next word
            while (i < instruction.length() && instruction[i] != ' ' && instruction[i] != '\n')
            {
                sub_command += instruction[i++];
            }

            if (sub_command == "break")
            {
                while (i < instruction.length() && instruction[i] == ' ')
                    i++;
                string break_str = "";
                while (i < instruction.length() && instruction[i] != '\n')
                {
                    break_str += instruction[i++];
                }
                for (int i = 0; i < break_number ; i++)
                {
                    if (breakpoint[i] == stoi(break_str) - data_length - 1)
                    {
                        for (int j = i; j < break_number - 1 ; j++)
                        {
                            breakpoint[j] = breakpoint[j + 1];
                        }
                        breakpoint[break_number - 1] = -1;
                        break_number--;
                        cout << "Breakpoint cleared at line " << break_str << endl;
                        break;
                    }
                }
            }
        }
        if(temp == "show-stack")
        {
            if(show_func.empty())
            {
                cout<<"Empty Call Stack: Execution complete"<<endl;
                cout<<"Exited the simulator"<<endl;
                break;
            }

            cout<<"Call Stack"<<endl;
            print_stack(show_func);
        }
    }
}
