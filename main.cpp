#include <iostream>
#include <fstream>
#include <cmath>
#define MAX 1000
#include "commalgo.hh"
#include "struct.hh"
#include "sort_find.hh"

store_label label_line[MAX];

int main()
{
    int i = 0;
    std::string inst;
    unsigned int k = 0;
    std::string line;
    std::ifstream infile("input.s");
    std::ofstream outfile("output.hex", std::ios::out);
    int line_counter = 0;
    while (getline(infile, line))
    {
        i = 0;
        inst = "";
        if (line.empty())
            continue;
        line_counter++;
        while (i < line.length())
        {
            while (i < line.length() && line[i] == ' ')
                i++;
            inst = "";
            while (i < line.length() && line[i] != ' ' && line[i] != ',' && line[i] != ':')
                inst = inst + line[i++];
            if (i < line.length() && line[i] == ':')
            {
                if (search_label(inst, label_line))
                {
                    std::cout << "repeated label at " << line_counter << std::endl;
                    i++;
                    continue;
                }
                label_line[k].label = inst;
                label_line[k].label_line_num = line_counter;
                k++;
                i++;
            }

            while (i < line.length() && (line[i] == ' ' || line[i] == ','))
                i++;
        }
    }

    infile.clear();
    infile.seekg(0, std::ios::beg); // reset to the beginning of the file
    line_counter = 0;
    while (getline(infile, line))
    {

        if (line.empty())
            continue;
        line_counter++;
        outfile << sort(line, line_counter, label_line) << std::endl;
    }

    infile.close();
    return 0;
}