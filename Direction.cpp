#include "Direction.h"

bool operator&(Direction lhs, Direction rhs){
    return static_cast<char>(lhs) & static_cast<char>(rhs);
}

std::ostream& operator<<(std::ostream& out, const Direction& direction){
    switch(direction){
        case Direction::U :
            out << 'U';
            break;
        case Direction::D :
            out << 'D';
            break;
        case Direction::L :
            out << 'L';
            break;
        case Direction::R :
            out << 'R';
            break;
        case Direction::None:
            out << "None";
            break;
    }
    return out;
}

std::istream& operator>>(std::istream& in, Direction& direction){
    char dir;
    in >> dir;
    switch(dir){
        case 'U':
            direction = Direction::U;
            break;
        case 'D':
            direction = Direction::D;
            break;
        case 'L':
            direction = Direction::L;
            break;
        case 'R':
            direction = Direction::R;
            break;
        case 'N':
            direction = Direction::None;
            in >> dir;
            in >> dir;
            in >> dir;
            break;
        default:
            throw std::invalid_argument("Invalid direction");
    }
    return in;
}

template<> Direction fromChar<Direction>(char c){
    switch(c){
        case 'U':
            return Direction::U;
        case 'D':
            return Direction::D;
        case 'L':
            return Direction::L;
        case 'R':
            return Direction::R;
        case 'N':
            return Direction::None;
        default:
            throw std::invalid_argument("Invalid direction");
    }
}