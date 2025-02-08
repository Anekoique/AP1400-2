#ifndef Q2_H
#define Q2_H

#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iostream>

namespace q2 
{
    struct Patient
    {
        std::string name;
        size_t age;
        size_t smokes;
        size_t area_q;
        size_t alkhol;
    };

    std::vector<Patient> read_file(std::string filename);
    void sort(std::vector<Patient>& vec);
}

bool comparePatient(q2::Patient a, q2::Patient b);

inline std::vector<q2::Patient> q2::read_file(std::string filename)
{
    std::ifstream file;
    file.open(filename, std::ios::in);

    std::vector<Patient> vec;
    std::string line;
    getline(file, line);
    getline(file, line);
    while (getline(file, line))
    {
        std::stringstream ss(line);
        std::string field;
        std::vector<std::string> row;

        while (getline(ss, field, ','))
        {
            row.push_back(field);
        }
        Patient subPatient;
        auto iter = row[0].find(" ");
        if (iter != std::string::npos) {
            row[0].erase(iter, 1);  // 只删除找到的空格字符
        }
        auto iter2 = row[1].find(" ");
        if (iter2 != std::string::npos) {
            row[1].erase(iter2, 1);  // 同样只删除空格字符
        }
        subPatient.name = row[0] + ' ' + row[1];
        subPatient.age = std::stoi(row[2]);
        subPatient.smokes = std::stoi(row[3]);
        subPatient.area_q = std::stoi(row[4]);
        subPatient.alkhol = std::stoi(row[5]);
        vec.push_back(subPatient);
    }

    file.close();
    return vec;
}

inline bool comparePatient(q2::Patient a, q2::Patient b)
{
    return a.age * 3 + a.smokes * 5 + a.area_q * 2 + a.alkhol * 4 > b.age * 3 + b.smokes * 5 + b.area_q * 2 + b.alkhol * 4;
}

inline void q2::sort(std::vector<Patient>& vec)
{
    sort(vec.begin(), vec.end(), comparePatient);
}

#endif
