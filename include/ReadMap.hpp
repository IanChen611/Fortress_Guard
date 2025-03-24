#ifndef READMAP_HPP
#define READMAP_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>


#include "Util/Logger.hpp"


class ReadMap{
public:
    ReadMap(int level);
    ~ReadMap();

    std::string GiveTileName(int i, int j) {return map[i][j];}

private:
    std::ifstream file;
    std::vector<std::vector<std::string>> map;
};

#endif