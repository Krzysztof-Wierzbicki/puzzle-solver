#include "Fifteen.h"
#include <stdexcept>

#define self (*this)

Fifteen::Fifteen(){
    m_value = new uint8_t* [4];
    for(int i=0; i<4; i++){
        m_value[i] = new uint8_t [4];
    }
}

Fifteen::Fifteen(const Fifteen &other) : Fifteen() {
    for(int i=0; i<4; i++){
        for(int j=0; j<4; j++){
            self.m_value[i][j] = other.m_value[i][j];
        }
    }
    self.m_zero = other.m_zero;
}

Fifteen::Fifteen(Fifteen &&other) noexcept : Fifteen() {
    auto tmp = other.m_value;
    other.m_value = self.m_value;
    self.m_value = tmp;
    self.m_zero = other.m_zero;
}

Fifteen &Fifteen::operator=(const Fifteen &other) noexcept {
    for(int i=0; i<4; i++){
        for(int j=0; j<4; j++){
            self.m_value[i][j] = other.m_value[i][j];
        }
    }
    self.m_zero = other.m_zero;
    return *this;
}

Fifteen &Fifteen::operator=(Fifteen &&other) noexcept {
    auto tmp = other.m_value;
    other.m_value = self.m_value;
    self.m_value = tmp;
    self.m_zero = other.m_zero;
    return *this;
}

Fifteen::Fifteen(uint64_t hash) : Fifteen() {
    for(short i=0; i<4; i++){
        for(short j=0; j<4; j++){
            m_value[i][j] = hash & 0xF;
            if(m_value[i][j] == 0){
                m_zero = {j, i};
            }
            hash >>= 4;
        }
    }
}

Fifteen::~Fifteen(){
    for(int i=0; i<4; i++){
        delete [] m_value[i];
    }
    delete [] m_value;
}

uint64_t Fifteen::hash() const {
    uint64_t hash = 0;
    for(int i=0; i<4; i++){
        for(int j=0; j<4; j++){
            hash |= static_cast<uint64_t>(m_value[i][j]) << ((4*i+j)*4);
        }
    }
    return hash;
}

bool Fifteen::canMoveZero(Direction direction) const {
    switch(direction){
        case Direction::U :
            if(m_zero.y == 0){ return false; }
            break;
        case Direction::D :
            if(m_zero.y == 3){ return false; }
            break;
        case Direction::L :
            if(m_zero.x == 0){ return false; }
            break;
        case Direction::R :
            if(m_zero.x == 3){ return false; }
            break;
        default:
            throw std::invalid_argument("Cannot move None");
    }
    return true;
}

void Fifteen::moveZero(Direction direction){
    switch(direction){
        case Direction::U :
            std::swap(m_value[m_zero.y][m_zero.x], m_value[m_zero.y-1][m_zero.x]);
            --m_zero.y;
            break;
        case Direction::D :
            std::swap(m_value[m_zero.y][m_zero.x], m_value[m_zero.y+1][m_zero.x]);
            ++m_zero.y;
            break;
        case Direction::L :
            std::swap(m_value[m_zero.y][m_zero.x], m_value[m_zero.y][m_zero.x-1]);
            --m_zero.x;
            break;
        case Direction::R :
            std::swap(m_value[m_zero.y][m_zero.x], m_value[m_zero.y][m_zero.x+1]);
            ++m_zero.x;
            break;
        default:
            throw std::invalid_argument("Cannot move None");
    }
}

Fifteen Fifteen::getMovedZero(Direction direction) const {
    Fifteen res(self);
    res.moveZero(direction);
    return res;
}

bool Fifteen::isSolved() const {
    for(int i=0; i<4; i++){
        for(int j=0; j<4; j++){
            if(m_value[i][j] != ((4*i+j+1)%16)){
                return false;
            }
        }
    }
    return true;
}

uint8_t *Fifteen::operator[](int index) {
    return m_value[index];
}

const uint8_t *Fifteen::operator[](int index) const {
    return m_value[index];
}

void Fifteen::print(std::ostream &out) const {
    for(int i=0; i<4; i++){
        for(int j=0; j<4; j++){
            out.width(2);
            out << static_cast<unsigned>(m_value[i][j]) << ' ';
        }
        if(i != 3){
            out << '\n';
        }
    }
}

void Fifteen::read(std::istream &in) {
    for(short i=0; i<4; i++){
        for(short j=0; j<4; j++){
            unsigned tmp;
            in >> tmp;
            m_value[i][j] = tmp;
            if(tmp == 0){
                m_zero = {j, i};
            }
        }
    }
}

std::pair<short, short> Fifteen::getZero() const {
    return {m_zero.x, m_zero.y};
}

std::ostream& operator<<(std::ostream& out, const Fifteen& fifteen){
    fifteen.print(out);
    return out;
}

std::istream& operator>>(std::istream& in, Fifteen& fifteen){
    fifteen.read(in);
    return in;
}
