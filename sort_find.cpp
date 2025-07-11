#include<string>
#include<iostream>
#include"Rconvert.hh"
#include"Sconvert.hh"
#include"Bconvert.hh"
#include"Iconvert.hh"
#include"Uconvert.hh"
#include"Jconvert.hh"
#include"sort_find.hh"
std::string sort (std::string s, int line_counter,struct store_label label_line[]) {

    std::string inst;
    unsigned int i = 0;
    while(s[i] == ' ') i++;
    while(s[i] != ' ' && s[i] != ',' && s[i] != ':')inst = inst + s[i++];
    

    
    if(s[i] == ':'){
    s = s.substr(i+1,s.length()-1);
    inst = "";
    i = 0;
    while(s[i] == ' ') i++;
    
    while(s[i] != ' ' && s[i] != ',' && s[i] != ':')inst = inst + s[i++];
    
    }
    
    // std::cout<<inst<<std::endl;
    if(inst == "add" || inst == "sub" || inst == "xor" || inst == "or" || inst == "and" || inst == "sll" || inst == "srl" || inst == "sra" || inst == "slt" || inst == "sltu"){
      return Rconvert(s,line_counter);  
}
    else if(inst == "addi" || inst == "xori" || inst == "ori" || inst == "andi" || inst == "slli" || inst == "srli" || inst == "srai" || inst == "slti" || inst == "sltiu" || inst == "lb" || inst == "lbu" || inst == "lh" || inst == "lhu" || inst == "lw" || inst == "ld" || inst == "lwu" || inst == "jalr"){
        return Iconvert(s,line_counter);
    }
    else if(inst == "sb" || inst == "sh" || inst == "sw" || inst == "sd"){
        return Sconvert(s,line_counter);
    }
    else if(inst == "beq" || inst == "bne" || inst == "blt" || inst == "bge" || inst == "bltu" || inst == "bgeu"){
        return Bconvert(s,line_counter,label_line);
    }
    else if(inst == "lui" || inst == "auipc"){
        return Uconvert(s,line_counter);
    }
    else if(inst == "jal"){
        return Jconvert(s,line_counter,label_line);
    }
    std::cout<<"error invalid instruction at line "<<line_counter<<std::endl;
    return "error invalid instruction";
}