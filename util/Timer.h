#ifndef TIMER_H
#define TIMER_H

#include <chrono>

class Timer{
public:
    Timer(){
        begin = std::chrono::high_resolution_clock::now();
    }
    double get(){
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> duration = end - begin;
        return duration.count();
    }
private:
    std::chrono::high_resolution_clock::time_point begin;
};

#endif //TIMER_H
