#include "Solver.h"

#include <queue>
#include <stack>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>

#include "util/Timer.h"

static constexpr int MAX_DEPTH = 20;

struct Node {
    Fifteen value;
    Direction* solution;
    int solutionLen;
};

namespace {
    std::vector<Direction> getSolution(const Fifteen& fifteen, const std::unordered_map<uint64_t, uint64_t>& visited){
        std::vector<Direction> solution;
        auto it = visited.find(fifteen.hash());
        while(it->second != 0){
            const auto [x1, y1] = Fifteen(it->first).getZero();
            it = visited.find(it->second);
            const auto [x0, y0] = Fifteen(it->first).getZero();
            if(x1-x0 == 1){
                solution.push_back(Direction::R);
            } else if(x1-x0 == -1){
                solution.push_back(Direction::L);
            } else if(y1-y0 == 1){
                solution.push_back(Direction::U);
            } else if(y1-y0 == -1){
                solution.push_back(Direction::D);
            }
        }
        std::reverse(solution.begin(), solution.end());
        return std::move(solution);
    }
}

void Solver::setDirections(const std::vector<Direction>& directions) {
    m_directions = directions;
}

Solution Solver::solveBFS2(const Fifteen &root) {
    Solution solutionStats;

    Timer timer;

    std::queue<Fifteen> toVisit;
    toVisit.push(root);

    std::unordered_map<uint64_t, uint64_t> visited;
    visited.emplace(root.hash(), 0);

    int processedCount = 0;

    while(!toVisit.empty()){
        ++processedCount;
        const auto& current = toVisit.front();
        if(current.isSolved()){
            auto solution = getSolution(current, visited);
            solutionStats.duration = timer.get();
            solutionStats.length = solution.size();
            solutionStats.maxDepth = solution.size();
            solutionStats.solution = std::move(solution);

            solutionStats.visited = visited.size();
            solutionStats.processed = processedCount;
            break;
        }

        for(Direction d : m_directions){
            if(current.canMoveZero(d)){
                auto next = current.getMovedZero(d);
                if(visited.find(next.hash()) == visited.end()){
                    visited.emplace(next.hash(), current.hash());
                    toVisit.emplace(std::move(next));
                }
            };
        }
        toVisit.pop();
    }

    return solutionStats;
}

Solution Solver::solveDFS2(const Fifteen &root) {
    //LUDR - directions array works backwards
    auto directions = m_directions;
    std::reverse(directions.begin(), directions.end());
    Solution solutionStats;

    Timer timer;

    std::stack<std::pair<Fifteen, short>> toVisit;
    toVisit.emplace(root, 0);

    std::unordered_map<uint64_t, uint64_t> visited;
    visited.emplace(root.hash(), 0);

    int processedCount = 0, maxdepth = 0;

    while(!toVisit.empty()){
        ++processedCount;
        auto current = std::move(toVisit.top());
        toVisit.pop();
        if(current.first.isSolved()){
            auto solution = getSolution(current.first, visited);
            solutionStats.duration = timer.get();
            solutionStats.length = solution.size();
            solutionStats.maxDepth = maxdepth;
            solutionStats.solution = std::move(solution);

            solutionStats.visited = visited.size();
            solutionStats.processed = processedCount;
            break;
        }
        if(current.second < MAX_DEPTH) {
            for (Direction d : directions) {
                if(current.first.canMoveZero(d)) {
                    auto next = current.first.getMovedZero(d);
                    if(visited.find(next.hash()) == visited.end()) {
                        if(maxdepth <= current.second){
                            maxdepth = current.second+1;
                        }
                        visited.emplace(next.hash(), current.first.hash());
                        toVisit.emplace(std::move(next), current.second+1);
                    }
                }
            }
        }
    }

    return solutionStats;
}