#ifndef DIRECTION_H
#define DIRECTION_H

#include <iostream>

/*
 * up: U -> 0b0011 -> 0x3
 * down: D -> 0b1100 -> 0xC
 * left: L -> 0b0110 -> 0x6
 * right: R -> 0b1001 -> 0x9
 *
 * then U&D = 0, L&R = 0, all other are non m_zero
 * using this not to go back to previous step
 */
enum class Direction : char {
    U = 0x3,
    L = 0x6,
    R = 0x9,
    D = 0xC,
    None = 0xF
};

bool operator&(Direction lhs, Direction rhs);
std::ostream& operator<<(std::ostream& out, const Direction& direction);
std::istream& operator>>(std::istream& in, Direction& direction);

template<typename T> T fromChar(char c);
template<> Direction fromChar<Direction>(char c);

#endif //DIRECTION_H
