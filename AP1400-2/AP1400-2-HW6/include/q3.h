#ifndef Q3_H
#define Q3_H

#include <string>
#include <queue>
#include <sstream>
#include <fstream>
#include <iostream>

namespace q3 
{
   struct Flight
   {
       std::string flight_number;
       size_t duration;
       size_t connections;
       size_t connection_times;
       size_t price;
   }; 

   std::priority_queue<Flight> gather_flghts(std::string filename);
}

inline std::priority_queue<q3::Flight> q3::gather_flghts(std::string filename)
{
    std::ifstream file;
    std::priority_queue<Flight> que;
    file.open(filename, std::ios::in);
    std::string line;

    while (getline(file, line))
    {
        std::stringstream
    }
}
#endif //Q3_H
