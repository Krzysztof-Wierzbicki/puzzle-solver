#include "Solver.h"

#include <queue>
#include <stack>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>
#include <map>

#include "util/Timer.h"

static constexpr int MAX_DEPTH = 20;

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
                solution.push_back(Direction::D);
            } else if(y1-y0 == -1){
                solution.push_back(Direction::U);
            }
        }
        std::reverse(solution.begin(), solution.end());
        return solution;
    }
}

void Solver::setDirections(const std::vector<Direction>& directions) {
    m_directions = directions;
}

Solution Solver::solveBFS(const Fifteen &root) {
    Timer timer;

    std::queue<Fifteen> toVisit;
    toVisit.push(root);

    std::unordered_map<uint64_t, uint64_t> visited;//zapisujemy dla każdego odwiedzonego układu układ z którego przyszliśmy
    visited.emplace(root.hash(), 0);

    int processedCount = 0;

    while(!toVisit.empty()){
        ++processedCount;
        const auto& current = toVisit.front();
        if(current.isSolved()){
            auto solution = getSolution(current, visited);
            Solution solutionStats;
            solutionStats.duration = timer.get();
            solutionStats.length = solution.size();
            solutionStats.maxDepth = solution.size();
            solutionStats.solution = std::move(solution);

            solutionStats.visited = visited.size();
            solutionStats.processed = processedCount;
            return solutionStats;
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

    return {-1, static_cast<int>(visited.size()), processedCount, 0, timer.get(), {}};
}

Solution Solver::solveDFS(const Fifteen &root) {
    //LUDR - directions array works backwards
    auto directions = m_directions;
    std::reverse(directions.begin(), directions.end());

    Timer timer;

    std::stack<std::pair<Fifteen, short>> toVisit;
    toVisit.emplace(root, 0);

    std::unordered_map<uint64_t, uint64_t> visited;//zapisujemy dla każdego odwiedzonego układu układ z którego przyszliśmy
    visited.emplace(root.hash(), 0);

    int processedCount = 0, maxdepth = 0;

    while(!toVisit.empty()){
        ++processedCount;
        auto current = std::move(toVisit.top());
        toVisit.pop();
        if(current.first.isSolved()){
            auto solution = getSolution(current.first, visited);
            Solution solutionStats;
            solutionStats.duration = timer.get();
            solutionStats.length = solution.size();
            solutionStats.maxDepth = maxdepth;
            solutionStats.solution = std::move(solution);

            solutionStats.visited = visited.size();
            solutionStats.processed = processedCount;
            return solutionStats;
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

    return {-1, static_cast<int>(visited.size()), processedCount, maxdepth, timer.get(), {}};
}

Solution Solver::solveAStar(const Fifteen &root) {
    Timer timer;

    //we should use priority_queue, but it's doesn't go well with raw pointer objects (it deletes inserted object xD), and map works good enough
    std::multimap<short, Fifteen> toVisit;
    toVisit.emplace(0, root);

    std::unordered_map<uint64_t, uint64_t> visited;//zapisujemy dla każdego odwiedzonego układu układ z którego przyszliśmy
    std::unordered_map<uint64_t, short> cost;//zapisujemy dla każdego odwiedzonego układu długość rozwiązania
    visited.emplace(root.hash(), 0);
    cost.emplace(root.hash(), 0);

    int processedCount = 0;

    while(!toVisit.empty()){
        ++processedCount;
        auto current = *toVisit.begin();
        toVisit.erase(toVisit.begin());
        if(current.second.isSolved()){
            auto solution = getSolution(current.second, visited);
            Solution solutionStats;
            solutionStats.duration = timer.get();
            solutionStats.length = solution.size();
            solutionStats.maxDepth = solution.size();
            solutionStats.solution = std::move(solution);

            solutionStats.visited = visited.size();
            solutionStats.processed = processedCount;
            return solutionStats;
        }

        short nextCost = cost[current.second.hash()] + 1;
        for(Direction d : {Direction::R, Direction::D, Direction::U, Direction::L}){
            if(current.second.canMoveZero(d)){
                auto next = current.second.getMovedZero(d);
                const auto costsIt = cost.find(next.hash());
                if(costsIt == cost.end() or costsIt->second > nextCost){
                    visited.emplace(next.hash(), current.second.hash());
                    cost[next.hash()] = nextCost;
                    short priority = nextCost + (this->*m_heuristic)(next);//c++ stahp :c
                    toVisit.emplace(priority, next);
                }
            };
        }
    }

    return {-1, static_cast<int>(visited.size()), processedCount, 0, timer.get(), {}};
}

void Solver::setHeuristic(Util::Heuristic heuristic) {
    if(heuristic == Util::Heuristic::Manhattan){
        m_heuristic = &Solver::manhattan;
    }else if(heuristic == Util::Heuristic::Hamming){
        m_heuristic = &Solver::hamming;
    }else if(heuristic == Util::Heuristic::MDLC){
        m_heuristic = &Solver::mdlc;
    }
}

short Solver::manhattan(const Fifteen &fifteen) {
    short manhattanDistanceSum = 0;
    for (short x = 0; x < 4; x++) {
        for (short y = 0; y < 4; y++) {
            const short value = fifteen[x][y];
            if (value != 0) { // we don't compute MD for element 0
                short targetX = (value - 1) / 4; // expected x-coordinate
                short targetY = (value - 1) % 4; // expected y-coordinate
                short dx = x - targetX;
                short dy = y - targetY;
                manhattanDistanceSum += abs(dx) + abs(dy);
            }
        }
    }
    return manhattanDistanceSum;
}

//search for "misplaced tiles heuristic"
short Solver::hamming(const Fifteen &fifteen) {
    short misplacedTilesCount = 0;
    short tile = 1;
    for (short x = 0; x < 4; x++) {
        for (short y = 0; y < 4; y++) {
            if (fifteen[x][y] != tile%16){
                ++misplacedTilesCount;
            }
            ++tile;
        }
    }
    return misplacedTilesCount;
}

// manhattan distance with linear conflict
short Solver::mdlc(const Fifteen &fifteen) {
    short manhattanDistanceSum = 0;
    for (short x = 0; x < 4; x++) {
        for (short y = 0; y < 4; y++) {
            const short value = fifteen[x][y];
            if (value != 0) { // we don't compute MD for element 0
                short targetX = (value - 1) / 4; // expected x-coordinate
                short targetY = (value - 1) % 4; // expected y-coordinate
                short dx = x - targetX;
                short dy = y - targetY;
                manhattanDistanceSum += abs(dx) + abs(dy);
                // add 2 per linear conflict
                if (targetX != x) {
                    continue;
                }
                for (short y2 = 0; y2 < y; y2++) {
                    if (fifteen[x][y2] == 0) {
                        continue;
                    }
                    if ((fifteen[x][y2] - 1) / 4 == x and fifteen[x][y] < fifteen[x][y2]) {
                        manhattanDistanceSum += 2;
                    }
                }
            }
        }
    }
    return manhattanDistanceSum;
}
