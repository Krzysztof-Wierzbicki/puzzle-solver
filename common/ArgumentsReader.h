#ifndef ARGUMENTS_READER_H
#define ARGUMENTS_READER_H

#include <string>

struct Arguments{
    enum {DFS, BFS, AStar} strategy;
    enum {Hamming, Manhattan, None} heuristic = None;
    char direction[4] = {0, 0, 0, 0};
    std::string inFile;
    std::string outFile;
    std::string statFile;
};

class ArgumentsReader {
public:
    static Arguments read(int argc, char** argv);
};


#endif //ARGUMENTS_READER_H
