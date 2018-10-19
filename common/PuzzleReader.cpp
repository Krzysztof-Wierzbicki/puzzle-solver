#include "PuzzleReader.h"

#include <fstream>

Puzzle PuzzleReader::read(const std::string& fileName){
    Puzzle ret = SOLUTION;
    std::ifstream file(fileName.c_str());
    std::string line;
    std::getline(file, line);
    if(line != "4 4"){
        throw std::logic_error("PuzzleReader: Not supported puzzle format - " + fileName);
    }
    for(int i=0; i<4; i++){
        std::getline(file, line);
        size_t nextNumber;
        ret[i][0] = std::stoi(line, &nextNumber);
        line = line.substr(nextNumber+1);
        ret[i][1] = std::stoi(line, &nextNumber);
        line = line.substr(nextNumber+1);
        ret[i][2] = std::stoi(line, &nextNumber);
        line = line.substr(nextNumber+1);
        ret[i][3] = std::stoi(line, &nextNumber);

    }
    return ret;
}