//
// Created by ofir shapira on 03/07/2023.
//

#ifndef PART1_SUBJECT_H
#define PART1_SUBJECT_H
#include "Observer.h"
#include <algorithm>
#include <vector>

#include "OOP5EventException.h"
template<typename T>

class Subject
{
public:
    Subject() = default;
    void notify(const T&);
    void addObserver(Observer<T>&);
    void removeObserver(Observer<T>&);

    Subject<T>& operator+=(Observer<T>&);
    Subject<T>& operator-=(Observer<T>&);
    Subject<T>& operator()(const T&);


protected:
    std::vector<Observer<T>*> _observers;
};



template<typename T>
void Subject<T>::removeObserver(Observer<T> & removedObserver) {
    bool found = false;
    for(Observer<T>* observer : _observers)
    {
        if(observer == &removedObserver) {
            found = true;
            break;
        }
    }
    if(!found)
        throw ObserverUnknownToSubject();

    _observers.erase(std::remove(_observers.begin(), _observers.end(),&removedObserver));

}

template<typename T>
void Subject<T>::addObserver(Observer<T> & newObserver)
{
    for(Observer<T>* observer : _observers)
    {
        if(observer == &newObserver) {
            throw ObserverAlreadyKnownToSubject();
        }
    }
    _observers.push_back(&newObserver);
}

template<typename T>
void Subject<T>::notify(const T & value)
{
    for(Observer<T> * o : _observers)
    {
        o->handleEvent(value);
    }
}
template<typename T>
Subject<T> &Subject<T>::operator-=(Observer<T> &removedObserver) {
    this->removeObserver(removedObserver);
    return *this;

}

template<typename T>
Subject<T> &Subject<T>::operator+=(Observer<T> & newObserver) {
    this->addObserver(newObserver);
    return *this;
}

template<typename T>
Subject<T> &Subject<T>::operator()(const T & value) {
    this->notify(value);
    return *this;
}
#endif //PART1_SUBJECT_H
