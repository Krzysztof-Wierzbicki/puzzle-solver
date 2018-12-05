#include <iostream>
#include <fstream>
#include "util/ArgParse.h"
#include "Fifteen.h"
#include "Solver.h"

int main(int argc, char** argv) {
    std::ios_base::sync_with_stdio(false);

    auto arguments = Util::read(argc, argv);

    std::ifstream inFile(arguments.inFile);
    Fifteen fifteen;
    int size;
    inFile >> size >> size;
    inFile >> fifteen;
    inFile.close();

    Solver solver;
    Solution solution;
    if(arguments.algorithm == Util::Algorithm::BFS){
        solver.setDirections(arguments.direction);
        solution = solver.solveBFS(fifteen);
    } else if(arguments.algorithm == Util::Algorithm::DFS){
        solver.setDirections(arguments.direction);
        solution = solver.solveDFS(fifteen);
    } else if(arguments.algorithm == Util::Algorithm::AStar){
        solver.setHeuristic(arguments.heuristic);
        solution = solver.solveAStar(fifteen);
    }

    std::ofstream outFile(arguments.outFile);
    outFile << solution.length;
    if(solution.length != -1){
        outFile << '\n';
        for(const auto& d : solution.solution){
            outFile << d;
        }
    }
    outFile.close();

    std::ofstream statFile(arguments.statFile);
    statFile << solution.length << '\n'
             << solution.visited << '\n'
             << solution.processed << '\n'
             << solution.maxDepth << '\n'
             << solution.duration;
    statFile.close();

    return 0;
}