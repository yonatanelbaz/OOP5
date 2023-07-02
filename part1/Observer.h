//
// Created by ofir shapira on 03/07/2023.
//

#ifndef PART1_OBSERVER_H
#define PART1_OBSERVER_H
template<typename T>
class Observer
{
public:
    virtual void handleEvent(const T& event) = 0;
};
#endif //PART1_OBSERVER_H
