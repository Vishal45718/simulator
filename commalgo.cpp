#include<iostream>
#include<string>
#include<cmath>
#include<limits>
#include"struct.hh"
#include"commalgo.hh"

using namespace std;
int search_label(std::string label , struct store_label label_line[])
{
    for (int i = 0; i < 1000; i++)
    {
        if (label_line[i].label == label)
        {
            return label_line[i].label_line_num;
        }
    }
    return 0;
}
std::string remove_starting_zeros(std::string s){

    while ( !s.empty() && s[0] == '0')
    {
        s.erase(0,1);
    }
    if(s.empty())
    return "0";
    return s;
}
unsigned int binary_to_decimal(std::string s){

       int decimal =0;
       int length = s.length(); 
        
       for (int i = 0; i < length; i++) {
            if(s[i] != '0' && s[i] != '1') {
                return -1;
            }

            if (s[i] == '1') {
               decimal += pow(2,length - (i + 1));
           }
       }
     
       return decimal;
}


std::string decimal_to_hex(unsigned int decimal){
    std::string hex = "";
   if (decimal == 0) {
       hex = "0";
   }
   else {
    
       while (decimal > 0) {
           int remainder = decimal % 16;
           if (remainder < 10) {
               hex = (char)(remainder + 48) + hex;
           }
           else {
               hex = (char)(remainder + 87) + hex;
           }
           decimal /= 16;
       }
   }
   if(hex.length() < 8){
       hex.insert(0 , 8-hex.length() , '0');
   }
    return hex;
}
std::string decimal_to_hex_no(unsigned long long decimal, int no_digits) 
{
    std::string hex = "";
    
    // Handle zero case
    if (decimal == 0) {
        hex = "0";
    } else {
        // Convert to hexadecimal
        while (decimal > 0) {
            int remainder = decimal % 16;
            if (remainder < 10) {
                hex = (char)(remainder + 48) + hex; // 0-9
            } else {
                hex = (char)(remainder + 87) + hex; // a-f
            }
            decimal /= 16;
        }
    }
        while (hex.length() < no_digits) {
        hex.insert(0, "0");
    }
    
       return hex;
}

std::string signed_decimal_to_hex_no(long long decimal, int no_digits) {
    std::string hex = "";

    if (decimal == 0) {
        hex = "0";
    }
    else if (decimal < 0) {
        
        unsigned long long twoComplement = (1 << (no_digits * 4)) + decimal -1; 
        hex = decimal_to_hex_no(twoComplement, no_digits);
    } else {
        hex = decimal_to_hex_no(decimal, no_digits);
    }
    while (hex.length() < no_digits) {
        hex.insert(0, "0");
    }

    return hex;
}

int hex_to_deci(std::string s){

    int decimal = 0;
    int length = s.length();
    for (int i = 0; i < length; i++) {
        if ((s[i] < '0' || s[i] > '9') && (s[i] < 'a' || s[i] > 'f')) {
            return -1;
        }

        else{
            if(s[i]>='0' && s[i]<='9'){
                decimal = decimal + pow(16,length-i-1)*(s[i] - '0');
            }
            else if(s[i]>='a' && s[i]<='f'){
                decimal = decimal + pow(16,length-i-1)*(s[i] - 'a' + 10);
            }
        }
    }
    return decimal;
}


std::string hex_to_bi(std::string s){

    std::string binary = "";
    for (int i = 0; i < s.length(); i++)
    {
        switch (s[i]) {
            case '0':
                binary += "0000";
                break;
            case '1':
                binary += "0001";
                break;
            case '2':
                binary += "0010";
                break;
            case '3':
                binary += "0011";
                break;
            case '4':
                binary += "0100";
                break;
            case '5':
                binary += "0101";
                break;
            case '6':
                binary += "0110";
                break;
            case '7':
                binary += "0111";
                break;
            case '8':
                binary += "1000";
                break;
            case '9':
                binary += "1001";
                break;
            case 'A':  case 'a':
                binary += "1010";
                break;
           
                
            case 'B': case 'b':
                binary += "1011";
                break;
            

            case 'C': case 'c':
                binary += "1100";
                break;
            case 'D': case 'd':
                binary += "1101";
                break;
            case 'E':  case 'e':
                binary += "1110";
                break;
            case 'F':  case 'f':
                binary += "1111";
                break;
            default:
                return "";
        }
    }
    return binary;
}
std::string bi_to_signed_decimal(const std::string& s) {
    long long decimal = 0;
   

    for (int i = 0; i < s.length(); i++) {
        if (s[i] == '1') {
            decimal += 1;
        }
        if (i < s.length() - 1) {
            decimal <<= 1;
        }
    }

    if ( (s[0] == '1')) {
        decimal -= (1 << s.length());
    }

    return std::to_string(decimal);
}
long long int hex_to_deci_64(const std::string& s) {
    long long int decimal = 0;
    int length = s.length();
    
    for (int i = 0; i < length; i++) {
        char c = s[i];

        int digit;
        if (c >= '0' && c <= '9') {
            digit = c - '0';
        } else if (c >= 'a' && c <= 'f') {
            digit = c - 'a' + 10;
        } else {
            digit = c - 'A' + 10;
        }

        decimal = decimal * 16 + digit;
    }
    
    return decimal;
}
unsigned long long int hex_to_deci_64_unsigned(const std::string& s) {
    unsigned long long int decimal = 0;
    int length = s.length();

    for (int i = 0; i < length; i++) {
        char c = s[i];

        int digit;
        if (c >= '0' && c <= '9') {
            digit = c - '0';
        } else if (c >= 'a' && c <= 'f') {
            digit = c - 'a' + 10;
        } else if (c >= 'A' && c <= 'F') {
            digit = c - 'A' + 10;
        } else {
            throw std::invalid_argument("Invalid character in hexadecimal string");
        }

        decimal = decimal * 16 + digit;
    }

    return decimal;
}

std::string deci_to_bi(int x, int no_of_bits){
    std::string stri="";
    if(x >0){
    
    while( x!=0){
        int y=x;
        y = y%2;
        x = x/2;
        stri = std::to_string(y) +stri;    
        
    }
    while(stri.length() < no_of_bits){
            stri = "0" + stri;

        }
    }
    else if( x<-1)
    {
    
        x = 0-x;
        
        x--;
        while( x!=0){
            int y=x;
            y = y%2;
            if(y == 0){
                y = 1;
            }
            else{
                y = 0;
            }
           
            x = x/2 ;

            stri = std::to_string(y) + stri;
            

        }
        while(stri.length() < no_of_bits){
            stri = "1" + stri;

        }
    }
    else if(x == 0){
        while(stri.length() < no_of_bits){
            stri = "0" + stri;

        }
    }
    else if (x == -1){  
        while(stri.length() < no_of_bits){
            stri = "1" + stri;

        }
    }
    return stri;

}
std::string register_to_bi(std::string s,int line_counter){

    int length = s.length();
    std::string result = "";
    if(s[0] == 'x'){
    for (int i = 1; i < length; i++) {
        result += s[i];
    }
    
    int x = stoi(result);
    if(x>31 || x<0){
        std::cout<<"invalid_register : "<<s<<" at line "<<line_counter<<""<<std::endl;
        return("00000");
    }
    return(deci_to_bi(x,5));
    }
    else{
       if( s == "zero"){ return(deci_to_bi(0,5)); }
       else if( s == "ra") { return(deci_to_bi(1,5)); }
       else if( s == "sp") { return(deci_to_bi(2,5)); }
       else if ( s == "gp") { return(deci_to_bi(3,5)); }
       else if ( s == "tp") { return(deci_to_bi(4,5)); } 
       else if ( s == "t0") { return(deci_to_bi(5,5)); }
       else if ( s == "t1") { return(deci_to_bi(6,5)); }
       else if ( s == "t2") { return(deci_to_bi(7,5)); }
       else if ( s == "s0") { return(deci_to_bi(8,5)); }
       else if ( s == "fp") { return(deci_to_bi(8,5)); }
       else if ( s == "s1") { return(deci_to_bi(9,5)); }
       else if ( s == "a0") { return(deci_to_bi(10,5)); }
       else if ( s == "a1") { return(deci_to_bi(11,5)); }
       else if ( s == "a2") { return(deci_to_bi(12,5)); }
       else if ( s == "a3") { return(deci_to_bi(13,5)); }
       else if ( s == "a4") { return(deci_to_bi(14,5)); }
       else if ( s == "a5") { return(deci_to_bi(15,5)); }
       else if ( s == "a6") { return(deci_to_bi(16,5)); }
       else if ( s == "a7") { return(deci_to_bi(17,5)); }
       else if ( s == "s2") { return(deci_to_bi(18,5)); }
       else if ( s == "s3") { return(deci_to_bi(19,5)); }
       else if ( s == "s4") { return(deci_to_bi(20,5)); }
       else if ( s == "s5") { return(deci_to_bi(21,5)); }
       else if ( s == "s6") { return(deci_to_bi(22,5)); }
       else if ( s == "s7") { return(deci_to_bi(23,5)); }
       else if ( s == "s8") { return(deci_to_bi(24,5)); }
       else if ( s == "s9") { return(deci_to_bi(25,5)); }
       else if ( s == "s10") { return(deci_to_bi(26,5)); }
       else if ( s == "s11") { return(deci_to_bi(27,5)); }
       else if ( s == "t3") { return(deci_to_bi(28,5)); }
       else if ( s == "t4") { return(deci_to_bi(29,5)); }
       else if ( s == "t5") { return(deci_to_bi(30,5)); }
       else if ( s == "t6") { return(deci_to_bi(31,5)); }
       else{
           std::cout<<"invalid_register : "<<s<<" at line "<<line_counter<<""<<std::endl;
            return("00000");
       }

    }

}

