#include <iostream>
#include "RushHour.h"
#include "Printer.h"

typedef GameBoard< List<
        List < BoardCell< EMPTY , RIGHT , 1>, BoardCell< EMPTY , RIGHT , 0>, BoardCell< EMPTY , RIGHT , 0>, BoardCell< EMPTY , RIGHT , 0>, BoardCell< O , DOWN , 2>, BoardCell< EMPTY , RIGHT , 0> >,
        List < BoardCell< EMPTY , RIGHT , 2>, BoardCell< EMPTY , RIGHT , 0>, BoardCell< A , LEFT , 2>, BoardCell< A , LEFT , 2>, BoardCell< O , DOWN , 2>, BoardCell< EMPTY , RIGHT , 0> >,
        List < BoardCell< EMPTY , RIGHT , 3>, BoardCell< EMPTY , RIGHT , 0>, BoardCell< X , LEFT , 2>, BoardCell< X , LEFT  , 2>, BoardCell< EMPTY , DOWN , 2>, BoardCell< EMPTY , RIGHT , 0> >,
        List < BoardCell< EMPTY , RIGHT , 0>, BoardCell< EMPTY , RIGHT , 0>, BoardCell< EMPTY , RIGHT , 0>, BoardCell< EMPTY , RIGHT , 0>, BoardCell< EMPTY , RIGHT , 0>, BoardCell< EMPTY , RIGHT , 0> >,
        List < BoardCell< D , UP , 2>, BoardCell< EMPTY , RIGHT , 0>, BoardCell< EMPTY , UP  , 2>, BoardCell< P , RIGHT , 3>, BoardCell< P , RIGHT , 3>, BoardCell< P , RIGHT , 3> >,
        List < BoardCell< D , UP , 2>, BoardCell< EMPTY , RIGHT , 0>, BoardCell< C , LEFT , 2>, BoardCell< C , RIGHT , 2>, BoardCell< EMPTY, RIGHT , 2>, BoardCell< EMPTY , LEFT , 2> >
> > gameBoard;

typedef List<
        Move < O, DOWN,2>,Move<D,UP,1>
> moves;

int main(){

    static_assert(List<BoardCell< EMPTY , RIGHT , 0>,BoardCell< EMPTY , RIGHT , 0>,BoardCell< EMPTY , RIGHT , 0>>::size == 3, "Fail");
    static_assert(List<>::size == 0, "Fail");
    //typedef MoveVehicle<gameBoard, 2, 3, RIGHT, 2>::board b1; // Valid move
    static_assert(CheckSolution<gameBoard, moves>::result, "Fail"); // Game should be solved

    return 0;
}

