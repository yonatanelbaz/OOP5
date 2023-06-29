//
// Created by ofir shapira on 29/06/2023.
//

#ifndef OOP5_MOVEVEHICLE_H
#define OOP5_MOVEVEHICLE_H

#include "CellType.h"
#include "Direction.h"
#include "BoardCell.h"
#include "List.h"

template<CellType cell,Direction dir,int N>
struct Move
{
    static_assert(cell==EMPTY,"Empty cell is not ok!\n");
    static constexpr CellType type = cell;
    static constexpr Direction direction = dir;
    static constexpr int amount = N;
};

template <typename Board,int R,int C>
struct ValidIndex
{

    static_assert(R >=0 && R < Board::width, "Invalid Index");
    static_assert(C >=0 && C < Board::length, "Invalid Index");

    typedef GetAtIndex<R,typename Board::board> row;
    typedef GetAtIndex<C, row> cell;
    static_assert(cell::type == EMPTY, "Invalid Index");

};

template <typename Board,int R,int C>
struct GetLeft{
    typedef
};


//struct get_Left ->
//struct get_right ->
//struct perform move
//struct valid index
//struct get cell


/*
template<typename ,int ,int,Direction,int > - Done
struct MoveVehicle
{
};*/


template <typename Board,int R,int C>
struct GetCellAtIndex
{
private:
    typedef GetAtIndex<R,typename Board::board> row;
public:
    typedef GetAtIndex<C, row> cell;
};


template <typename Board,int R,int C,Direction D,int A>
struct PerformMoves{};


template <typename Board,int R,int C,Direction D>
struct PerformMoves<Board,R,C,D,0>
{
    typedef Board:
};
template<typename Board,int R ,int C,Direction D,int A>
struct MoveVehicle
{
    //do step A times
    static_assert(Board::board::get);/
    //do checking
    //handle cases rows vs
    //make moves <board,edge,direction,amount>

}






#endif //OOP5_MOVEVEHICLE_H
