#include "ArgParse.h"

#include <stdexcept>
#include <cstring>

namespace Util {
    Arguments read(int argc, char **argv) {
        Arguments ret;
        if (argc != 6) {
            throw std::invalid_argument("ArgParser: Invalid number of arguments");
        }
        if (strcmp(argv[1], "bfs") == 0) {
            ret.algorithm = Algorithm::BFS;
        } else if (strcmp(argv[1], "dfs") == 0) {
            ret.algorithm = Algorithm::DFS;
        } else if (strcmp(argv[1], "astr") == 0) {
            ret.algorithm = Algorithm::AStar;
        } else {
            throw std::invalid_argument("ArgParser: Unrecognized algorithm");
        }
        if (ret.algorithm == Algorithm::AStar) {
            if (strcmp(argv[2], "hamm") == 0) {
                ret.heuristic = Heuristic::Hamming;
            } else if (strcmp(argv[2], "manh") == 0) {
                ret.heuristic = Heuristic::Manhattan;
            } else {
                throw std::invalid_argument("ArgParser: Unrecognized heuristic");
            }
        } else {
            for (int i = 0; i < 4; i++) {
                ret.direction.push_back(fromChar<Direction>(argv[2][i]));
            }
        }
        ret.inFile = std::string(argv[3]);
        ret.outFile = std::string(argv[4]);
        ret.statFile = std::string(argv[5]);
        return ret;
    }
}