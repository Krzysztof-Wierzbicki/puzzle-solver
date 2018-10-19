#ifndef SOLVER_H
#define SOLVER_H

#include <vector>
#include "Fifteen.h"

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
    void setDirections(const std::vector<Direction>& directions);
    Solution solveBFS(const Fifteen& root);
    Solution solveBFS2(const Fifteen& root);
    Solution solveDFS(const Fifteen& root);
    Solution solveDFS2(const Fifteen& root);
private:
    std::vector<Direction> m_directions;
};


#endif //SOLVER_H
