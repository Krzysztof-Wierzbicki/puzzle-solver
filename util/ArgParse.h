#ifndef ARG_PARSE_H
#define ARG_PARSE_H

#include <string>
#include <vector>
#include "../Direction.h"

namespace Util{
    enum class Algorithm{
        DFS,
        BFS,
        AStar
    };

    enum class Heuristic{
        Hamming,
        Manhattan,
        None
    };

    struct Arguments{
        Algorithm algorithm;
        Heuristic heuristic = Heuristic::None;
        std::vector<Direction> direction;
        std::string inFile;
        std::string outFile;
        std::string statFile;
    };

    Arguments read(int argc, char** argv);
}

#endif //ARG_PARSE_H
