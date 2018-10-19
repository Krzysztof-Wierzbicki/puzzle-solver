#include <iostream>
#include "common/ArgumentsReader.h"
#include "common/PuzzleReader.h"

int main(int argc, char** argv) {
    auto arguments = ArgumentsReader::read(argc, argv);
    auto input = PuzzleReader::read(arguments.inFile);

    //TODO: do everything

    return 0;
}