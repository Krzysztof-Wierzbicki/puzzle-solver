#ifndef SOLVER_H
#define SOLVER_H

#include <vector>
#include "Fifteen.h"
#include "util/ArgParse.h"

struct Solution{
    int length = -1;
    int visited;
    int processed;
    int maxDepth;
    double duration;
    std::vector<Direction> solution;
};

class Solver {
public:
    Solution solveBFS(const Fifteen &root);
    Solution solveDFS(const Fifteen &root);
    Solution solveAStar(const Fifteen &root);
    void setDirections(const std::vector<Direction>& directions);
    void setHeuristic(Util::Heuristic heuristic);
private:
    short manhattan(const Fifteen& fifteen);
    short hamming(const Fifteen& fifteen);// misplaced tiles heuristic
    short mdlc(const Fifteen& fifteen);// manhattan distance + linear conflicts
    std::vector<Direction> m_directions;
    short (Solver::*m_heuristic)(const Fifteen&);
};


#endif //SOLVER_H
