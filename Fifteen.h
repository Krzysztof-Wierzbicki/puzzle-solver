#ifndef FIFTEEN_H
#define FIFTEEN_H

#include <cstdint>
#include <iostream>
#include <vector>
#include "Direction.h"

class Fifteen{
public:
    Fifteen();
    Fifteen(const Fifteen& other);
    Fifteen(Fifteen&& other) noexcept;
    Fifteen& operator=(const Fifteen& other) noexcept;
    Fifteen& operator=(Fifteen&& other) noexcept;
    explicit Fifteen(uint64_t hash);
    ~Fifteen();

    // last move data is lost here
    uint64_t hash() const;
    bool canMoveZero(Direction direction) const;
    void moveZero(Direction direction);
    Fifteen getMovedZero(Direction direction) const;
    bool isSolved() const;
    uint8_t* operator[](int index);
    const uint8_t* operator[](int index) const;
    std::pair<short, short> getZero() const;
    void print(std::ostream& out) const;
    void read(std::istream& in);

private:
    uint8_t **m_value;
    struct{
        short x;
        short y;
    } m_zero;
};

std::istream& operator>>(std::istream& in, Fifteen& fifteen);
std::ostream& operator<<(std::ostream& out, const Fifteen& fifteen);

#endif //FIFTEEN_H
