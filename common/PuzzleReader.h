#ifndef PUZZLE_READER_H
#define PUZZLE_READER_H

#include <vector>
#include <string>

using Puzzle = std::vector<std::vector<int>>;

static const Puzzle SOLUTION = {{1, 2, 3, 4},
                                {5, 6, 7, 8},
                                {9, 10, 11, 12},
                                {13, 14, 15, 0}};

class PuzzleReader {
public:
    static Puzzle read(const std::string& fileName);
};


#endif //PUZZLE_READER_H
