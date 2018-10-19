#include "ArgumentsReader.h"

#include <stdexcept>
#include <cstring>

Arguments ArgumentsReader::read(int argc, char** argv) {
    Arguments ret;
    if(argc != 6){
        throw std::invalid_argument("ArgumentsReader: Invalid number of arguments");
    }
    if(strcmp(argv[1], "bfs") == 0){
        ret.strategy = Arguments::BFS;
    }else if(strcmp(argv[1], "dfs") == 0){
        ret.strategy = Arguments::DFS;
    }else if(strcmp(argv[1], "astr") == 0){
        ret.strategy = Arguments::AStar;
    }else{
        throw std::invalid_argument("ArgumentsReader: Unrecognized strategy");
    }
    if(ret.strategy == Arguments::AStar){
        if(strcmp(argv[2], "hamm") == 0){
            ret.heuristic = Arguments::Hamming;
        }else if(strcmp(argv[2], "manh") == 0){
            ret.heuristic = Arguments::Manhattan;
        }else{
            throw std::invalid_argument("ArgumentsReader: Unrecognized heuristic");
        }
    }else{
        for(int i=0; i<4; i++){
            if(argv[2][i] == 'R' ||
               argv[2][i] == 'L' ||
               argv[2][i] == 'U' ||
               argv[2][i] == 'D'){
                ret.direction[i] = argv[2][i];
            }else{
                throw std::invalid_argument("ArgumentsReader: Unrecognized direction");
            }
        }
    }
    ret.inFile = std::string(argv[3]);
    ret.outFile = std::string(argv[4]);
    ret.statFile = std::string(argv[5]);
    return ret;
}